#include "Precompiled.h"
#include "Animation.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;

Math::Vector3 Animation::GetPosition(float time) const
{
    // TODO find the time interval in mPositionKeys that is < time and stop when you hit a key.time > time
    //      Keyframe a = key.time < time (this will be the key in the list)
    //      Keyframe b = key.time > time (this the next key in the list, they'll be next to each other)
    //  float lerpT = time - a.time / b.time - time  (ratio 0-1)
    //  Vector3 pos = Lerp(a.key, b.key, lerpT)
    if (mPositionKeys.size() == 1)
    {
        return mPositionKeys[0].key;
    }
    for (int i = 0; i < mPositionKeys.size(); ++i)
    {
        if (time < mPositionKeys[i].time)
        {
            if (i > 0)
            {
                float lerpTime = (time - mPositionKeys[i - 1].time) / (mPositionKeys[i].time - mPositionKeys[i - 1].time);
                Math::Vector3 pos = Math::Lerp(mPositionKeys[i - 1].key, mPositionKeys[i].key, lerpTime);
                return pos;
            }
            return mPositionKeys[i].key;
        }
    }
    return Math::Vector3(1.0f);
}

Math::Quaternion Animation::GetRotation(float time) const
{
    if (mRotationKeys.size() == 1)
    {
        return mRotationKeys[0].key;
    }
    for (int i = 0; i < mRotationKeys.size(); ++i)
    {
        if (time < mRotationKeys[i].time)
        {
            if (i > 0)
            {
                float lerpTime = (time - mRotationKeys[i - 1].time) / (mRotationKeys[i].time - mRotationKeys[i - 1].time);
                Math::Quaternion rot = Math::Quaternion::Slerp(mRotationKeys[i - 1].key, mRotationKeys[i].key, lerpTime);
                return rot;
            }
            return mRotationKeys[i].key;
        }
    }
    return Math::Quaternion::Identity;
}

Math::Vector3 Animation::GetScale(float time) const
{
    if (mScaleKeys.size() == 1)
    {
        return mScaleKeys[0].key;
    }
    for (int i = 0; i < mScaleKeys.size(); ++i)
    {
        if (time < mScaleKeys[i].time)
        {
            if (i > 0)
            {
                float lerpTime = (time - mScaleKeys[i - 1].time) / (mScaleKeys[i].time - mScaleKeys[i - 1].time);
                Math::Vector3 pos = Math::Lerp(mScaleKeys[i - 1].key, mScaleKeys[i].key, lerpTime);
                return pos;
            }
            return mScaleKeys[i].key;
        }
    }

    return Math::Vector3(1.0f);
}

Transform Animation::GetTransform(float time) const
{
    Transform t;
    t.position = GetPosition(time);
    t.rotation = GetRotation(time);
    t.scale = GetScale(time);

    return t;
}

float Animation::GetDuration() const
{
    return mDuration;
}