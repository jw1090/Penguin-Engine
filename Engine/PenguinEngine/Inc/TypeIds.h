#pragma once

#include "Common.h"

namespace PenguinEngine
{
    enum class ComponentId
    {
        Animator,
        Camera,
        Collider,
        FPSCameraController,
        Model,
        Physics,
        RigidBody,
        Transform,
        Count
    };

    enum class ServiceId
    {
        Camera,
        Render,
        Physics,
        Count
    };
}

#define SET_TYPE_ID(id)\
    static uint32_t StaticGetTypeId() { return static_cast<uint32_t>(id); }\
    uint32_t GetTypeId() const override { return StaticGetTypeId(); }