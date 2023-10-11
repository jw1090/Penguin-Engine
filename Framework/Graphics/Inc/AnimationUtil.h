#pragma once
#include "Skeleton.h"
#include "Animator.h"

namespace PenguinEngine::Graphics::AnimationUtil
{
    using BoneTransforms = std::vector<Math::Matrix4>;

    void ComputeBoneTransform(ModelID id, BoneTransforms& boneTransforms, const Animator* animator = nullptr);
    void ApplyBoneOffset(ModelID id, BoneTransforms& boneTransforms);
    void DrawSkeleton(ModelID id, const BoneTransforms& boneTransforms);
}