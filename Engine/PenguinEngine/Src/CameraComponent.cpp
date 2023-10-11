#include "Precompiled.h"
#include "CameraComponent.h"
#include "CameraService.h"
#include "GameWorld.h"

using namespace PenguinEngine;

void CameraComponent::Initialize()
{
    auto cameraService = GetOwner().GetWorld().GetService<CameraService>();
    cameraService->Register(this);
}

void CameraComponent::Terminate()
{
    auto cameraService = GetOwner().GetWorld().GetService<CameraService>();
    cameraService->Unregister(this);
}