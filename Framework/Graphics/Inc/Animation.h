#pragma once
#include "Keyframe.h"
#include "Transform.h"

namespace PenguinEngine::Graphics
{
    class Animation
    {
    public:
        Math::Vector3 GetPosition(float time) const;
        Math::Quaternion GetRotation(float time) const;
        Math::Vector3 GetScale(float time) const;

        Transform GetTransform(float time) const;

        float GetDuration() const;

    private:
        friend class AnimationIO;
        friend class AnimationBuilder;

        PositionKeys mPositionKeys;
        RotationKeys mRotationKeys;
        ScaleKeys mScaleKeys;
        float mDuration;
    };
}