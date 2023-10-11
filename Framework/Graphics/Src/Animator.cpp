#include "Precompiled.h"
#include "Animator.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;


void BlendNode::PlayAnimation(ModelID id, int clipIndex, bool looping)
{
    mModelID = id;
    mClipIndex = clipIndex;
    mLooping = looping;
    mAnimationTick = 0.0f;
}
void BlendNode::Update(float deltaTime)
{
    auto model = ModelManager::Get()->GetModel(mModelID);
    const auto& animClip = model->animationClips[mClipIndex];
    mAnimationTick += animClip.ticksPerSecond * deltaTime;
    if (mAnimationTick > animClip.tickDuration)
    {
        if (mLooping && animClip.tickDuration > 0.0f)
        {
            while (mAnimationTick > animClip.tickDuration)
            {
                mAnimationTick -= animClip.tickDuration;
            }
        }
        else
        {
            mAnimationTick = animClip.tickDuration;
        }
    }
}

Transform BlendNode::GetToParentTransform(const Bone* bone) const
{
    auto model = ModelManager::Get()->GetModel(mModelID);
    const auto& animClip = model->animationClips[mClipIndex];
    auto& animation = animClip.boneAnimations[bone->index];
    if (animation == nullptr)
    {
        return Transform();
    }

    return animation->GetTransform(mAnimationTick);
}


void Animator::Initialize(ModelID id)
{
    mModelID = id;
}
void Animator::PlayAnimation(int clipIndex, bool looping, float blendDuration)
{
    auto model = ModelManager::Get()->GetModel(mModelID);
    ASSERT(clipIndex < model->animationClips.size(), "Animator -- Invalid clip index");

    auto& animClip = model->animationClips[clipIndex];
    if (blendDuration > 0.0f)
    {
        mNextClipIndex = clipIndex;
        mBlendDuration = blendDuration;
        mBlendTime = 0.0f;
        mNextAnim.PlayAnimation(mModelID, clipIndex, looping);
    }
    else
    {
        mClipIndex = clipIndex;
        mNextClipIndex = -1;
        mBlendDuration = 0.0f;
        mCurrentAnim.PlayAnimation(mModelID, clipIndex, looping);
    }
}

void Animator::Update(float deltaTime)
{
    mCurrentAnim.Update(deltaTime);
    if (mNextClipIndex > -1)
    {
        mNextAnim.Update(deltaTime);

        mBlendTime += deltaTime;
        if (mBlendTime >= mBlendDuration)
        {
            PlayAnimation(mNextClipIndex, mNextAnim.IsLooping());
        }
    }
}

bool Animator::IsFinished()
{
    if (mCurrentAnim.IsLooping())
    {
        return false;
    }

    auto model = ModelManager::Get()->GetModel(mModelID);
    const auto& animClip = model->animationClips[mClipIndex];
    return animClip.tickDuration <= mCurrentAnim.GetAnimationTick();
}
size_t Animator::GetAnimationCount() const
{
    auto model = ModelManager::Get()->GetModel(mModelID);
    return model->animationClips.size();
}
Math::Matrix4 Animator::GetToParentTransform(const Bone* bone) const
{
    auto fromTransform = mCurrentAnim.GetToParentTransform(bone);
    if (mNextClipIndex != -1)
    {
        float t = Math::Clamp(mBlendTime / mBlendDuration, 0.0f, 1.0f);
        auto toTransform = mNextAnim.GetToParentTransform(bone);

        Transform blendedTransform;
        blendedTransform.position = Math::Lerp(fromTransform.position, toTransform.position, t);
        blendedTransform.rotation = Math::Quaternion::Slerp(fromTransform.rotation, toTransform.rotation, t);
        blendedTransform.scale = Math::Lerp(fromTransform.scale, toTransform.scale, t);

        return bone->toParentTransform * blendedTransform.GetMatrix4();
    }
    return bone->toParentTransform * fromTransform.GetMatrix4();
}

const Model* Animator::GetModel() const
{
    return ModelManager::Get()->GetModel(mModelID);
}

const AnimationClip& Animator::GetAnimClip() const 
{
    auto model = ModelManager::Get()->GetModel(mModelID);
    return model->animationClips[mClipIndex];
}