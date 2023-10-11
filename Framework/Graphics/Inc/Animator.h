#pragma once

#include "ModelManager.h"
#include "Bone.h"

namespace PenguinEngine::Graphics
{
    class BlendNode
    {
    public:
        void PlayAnimation(ModelID id, int clipIndex, bool looping);
        void Update(float deltaTime);
        Transform GetToParentTransform(const Bone* bone) const;
        float GetAnimationTick() const { return mAnimationTick; }
        bool IsLooping() const { return mLooping; }
        
    private:
        ModelID mModelID = 0;
        int mClipIndex = 0;
        float mAnimationTick = 0.0f;
        bool mLooping = false;
    };

    class Animator
    {
    public:
        void Initialize(ModelID id);

        void PlayAnimation(int clipIndex, bool looping, float blendDuration = 0.0f);
        void Update(float deltaTime);
        bool IsFinished();

        size_t GetAnimationCount() const;
        Math::Matrix4 GetToParentTransform(const Bone* bone) const;
    private:
        const Model* GetModel() const;
        const AnimationClip& GetAnimClip() const;

        ModelID mModelID = 0;
        int mClipIndex = 0;
        int mNextClipIndex = -1;

        float mBlendDuration = -1.0f;
        float mBlendTime = -1.0f;

        BlendNode mCurrentAnim;
        BlendNode mNextAnim;
    };
}