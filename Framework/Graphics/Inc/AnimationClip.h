#pragma once

#include "Animation.h"

namespace PenguinEngine::Graphics
{
    class AnimationClip
    {
    public:
        std::string name;
        float tickDuration = 0.0f;
        float ticksPerSecond = 0.0f;

        std::vector<std::unique_ptr<Animation>> boneAnimations;
    };
}