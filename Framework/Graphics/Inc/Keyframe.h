#pragma once
#include "Common.h"
namespace PenguinEngine::Graphics
{
    template<class T>
    struct Keyframe
    {
        Keyframe() = default;
        Keyframe(const T& k, float t)
            : key(k)
            , time(t)
        {

        }

        T key = T();
        float time;
    };

    template<class T>
    using Keyframes = std::vector<Keyframe<T>>;

    using PositionKeys = Keyframes<Math::Vector3>;
    using RotationKeys = Keyframes<Math::Quaternion>;
    using ScaleKeys = Keyframes<Math::Vector3>;
}