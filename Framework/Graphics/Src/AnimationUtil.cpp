#include "Precompiled.h"
#include "AnimationUtil.h"
#include "Colors.h"
#include "SimpleDraw.h"
#include "ModelManager.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Graphics::AnimationUtil;

namespace
{
	void ComputeBoneTransformRecursive(Bone* bone, BoneTransforms& boneTransforms, const Animator* animator)
	{
		if (bone != nullptr)
		{
			if (bone->parent != nullptr)
			{
				if (animator != nullptr)
				{
					boneTransforms[bone->index] = animator->GetToParentTransform(bone) * boneTransforms[bone->parentIndex];
				}
				else
				{
					boneTransforms[bone->index] = bone->toParentTransform * boneTransforms[bone->parentIndex];
				}
			}

			for (auto child : bone->children)
			{
				ComputeBoneTransformRecursive(child, boneTransforms, animator);
			}
		}
	}
}

void AnimationUtil::ComputeBoneTransform(ModelID id, BoneTransforms& boneTransforms, const Animator* animator)
{
	auto model = ModelManager::Get()->GetModel(id);
    boneTransforms.resize(model->skeleton->bones.size(), Math::Matrix4::Identity);

    ComputeBoneTransformRecursive(model->skeleton->root, boneTransforms, animator);
}
void AnimationUtil::ApplyBoneOffset(ModelID id, BoneTransforms& boneTransforms)
{
	auto model = ModelManager::Get()->GetModel(id);
	for (auto& bone : model->skeleton->bones)
	{
		boneTransforms[bone->index] = bone->offsetTransform * boneTransforms[bone->index];
	}
}
void AnimationUtil::DrawSkeleton(ModelID id, const BoneTransforms& boneTransforms)
{
	auto model = ModelManager::Get()->GetModel(id);
	const size_t numBones = model->skeleton->bones.size();
	for (size_t i = 0; i < numBones; ++i)
	{
		const auto posA = Math::GetTranslation(boneTransforms[i]);
		if (model->skeleton->bones[i]->parent != nullptr)
		{
			const auto posB = Math::GetTranslation(boneTransforms[model->skeleton->bones[i]->parentIndex]);
			SimpleDraw::AddLine(posA, posB, Colors::AliceBlue);
		}
	}
}