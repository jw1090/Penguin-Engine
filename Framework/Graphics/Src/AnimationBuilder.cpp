#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;

namespace
{
    template <class T>
    inline void PushKey(Keyframes<T>& keyframes, const T& value, float time)
    {
        ASSERT(keyframes.empty() || keyframes.back().time < time, "AnimationBuilder -- Cannot add keyframe back in time.");
        keyframes.emplace_back(value, time);
    }
}

AnimationBuilder& AnimationBuilder::AddPositionKey(const Math::Vector3& position, float time)
{
    PushKey(mWorkingCopy.mPositionKeys, position, time);
    mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
    return *this;
}

AnimationBuilder& AnimationBuilder::AddRotationKey(const Math::Quaternion& rotation, float time)
{
    PushKey(mWorkingCopy.mRotationKeys, rotation, time);
    mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
    return *this;
}

AnimationBuilder& AnimationBuilder::AddScaleKey(const Math::Vector3& scale, float time)
{
    PushKey(mWorkingCopy.mScaleKeys, scale, time);
    mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
    return *this;
}

Animation AnimationBuilder::Build()
{
    ASSERT(!mWorkingCopy.mPositionKeys.empty() || !mWorkingCopy.mRotationKeys.empty() || !mWorkingCopy.mScaleKeys.empty(), "AnimationBuilder -- Animation has no keys.");
    //ASSERT(mWorkingCopy.mDuration > 0.0f, "AnimationBuilder -- Animation has no duration.");
    if (mWorkingCopy.mPositionKeys.size() == 0)
    {
        PushKey(mWorkingCopy.mPositionKeys, Math::Vector3::Zero, 0.0f);
        PushKey(mWorkingCopy.mPositionKeys, Math::Vector3::Zero, mWorkingCopy.mDuration);
    }
    if (mWorkingCopy.mRotationKeys.size() == 0)
    {
        PushKey(mWorkingCopy.mRotationKeys, Math::Quaternion::Zero, 0.0f);
        PushKey(mWorkingCopy.mRotationKeys, Math::Quaternion::Zero, mWorkingCopy.mDuration);
    }
    if (mWorkingCopy.mScaleKeys.size() == 0)
    {
        PushKey(mWorkingCopy.mScaleKeys, Math::Vector3::One, 0.0f);
        PushKey(mWorkingCopy.mScaleKeys, Math::Vector3::One, mWorkingCopy.mDuration);
    }

    return std::move(mWorkingCopy);
}