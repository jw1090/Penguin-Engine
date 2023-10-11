#include "Precompiled.h"
#include "FPSCameraControllerComponent.h"
#include "GameObject.h"
#include "CameraComponent.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Input;

void FPSCameraControllerComponent::Initialize()
{
    mCameraComponent = GetOwner().GetComponent<CameraComponent>();
}

void FPSCameraControllerComponent::Terminate()
{
    mCameraComponent = nullptr;
}

void FPSCameraControllerComponent::Update(float deltaTime)
{
    auto inputSystem = InputSystem::Get();
    auto& camera = mCameraComponent->GetCamera();

    const float moveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? mMoveSpeed * 10.0f : mMoveSpeed;
    const float turnSpeed = mTurnSpeed;

    if (inputSystem->IsKeyDown(KeyCode::W))
    {
        camera.Walk(moveSpeed * deltaTime);
    }
    if (inputSystem->IsKeyDown(KeyCode::S))
    {
        camera.Walk(-moveSpeed * deltaTime);
    }
    if (inputSystem->IsKeyDown(KeyCode::D))
    {
        camera.Strafe(moveSpeed * deltaTime);
    }
    if (inputSystem->IsKeyDown(KeyCode::A))
    {
        camera.Strafe(-moveSpeed * deltaTime);
    }
    if (inputSystem->IsKeyDown(KeyCode::E))
    {
        camera.Rise(moveSpeed * deltaTime);
    }
    if (inputSystem->IsKeyDown(KeyCode::Q))
    {
        camera.Rise(-moveSpeed * deltaTime);
    }
    if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
    {
        camera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
        camera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
    }
}