#include "Precompiled.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "GameWorld.h"

using namespace PenguinEngine;

void ColliderComponent::Initialize()
{
    mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}

void ColliderComponent::Terminate()
{
    mTransformComponent = nullptr;
}

void ColliderComponent::DebugUI()
{
    const auto& aabb = GetWorldAABB();
    Graphics::SimpleDraw::AddAABB(aabb.Min(), aabb.Max(), Graphics::Colors::HotPink);
}

Math::AABB ColliderComponent::GetLocalAABB() const
{
    return { mCenter, mExtend };
}

Math::AABB ColliderComponent::GetWorldAABB() const
{
    return { mCenter + mTransformComponent->position, mExtend };
}