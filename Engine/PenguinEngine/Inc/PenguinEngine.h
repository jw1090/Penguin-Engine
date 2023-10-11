#pragma once

#include "Common.h"

// App headers
#include "App.h"
#include "AppState.h"

// Component headers
#include "Component.h"
#include "AnimatorComponent.h"
#include "ColliderComponent.h"
#include "CameraComponent.h"
#include "FPSCameraControllerComponent.h"
#include "ModelComponent.h"
#include "PhysicsComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"

// Service headers
#include "Service.h"
#include "CameraService.h"
#include "RenderService.h"
#include "PhysicsService.h"

// World headers
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameWorld.h"
#include "TypeIds.h"

namespace PenguinEngine
{
    App& MainApp();
}