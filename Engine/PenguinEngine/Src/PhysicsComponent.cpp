#include "Precompiled.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
//#include "RigidBodyComponent.h"
#include "GameWorld.h"

using namespace PenguinEngine;

void PhysicsComponent::Initialize()
{
    mTransformComponent = GetOwner().GetComponent<TransformComponent>();
}

void PhysicsComponent::Terminate()
{
    mTransformComponent = nullptr;
}

void PhysicsComponent::Update(float deltaTime)
{
    /*if (mRigidBodyComponent != nullptr)
    {
        auto& rigidBody = mRigidBodyComponent->GetRigidBody()->getWorldTransform();
        ConvertToTransform(rigidBodyTransform, *mTransformComponent);
    }*/
}

void PhysicsComponent::DebugUI()
{

}