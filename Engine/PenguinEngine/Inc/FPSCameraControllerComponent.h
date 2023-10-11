#pragma once

#include "Component.h"

namespace PenguinEngine
{
    class CameraComponent;

    class FPSCameraControllerComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::FPSCameraController);

        void Initialize() override;
        void Terminate() override;
        void Update(float deltaTime);

        void SetMoveSpeed(float speed) { mMoveSpeed = speed; }
        void SetTurnSpeed(float speed) { mTurnSpeed = speed; }

    private:
        CameraComponent* mCameraComponent = nullptr;
        float mMoveSpeed = 1.0f;
        float mTurnSpeed = 0.1f;
    };
}