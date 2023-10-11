#include "Precompiled.h"
#include "PhysicsService.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
//#include "RigidBodyComponent.h"

#include "GameWorld.h"
#include "GameObject.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Math;

template <class T>
void SafeReleasePhysics(T*& ptr)
{
    if (ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

void PhysicsService::Initialize()
{
    mCollisionConfiguration = new btDefaultCollisionConfiguration();
    mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
    mInterface = new btDbvtBroadphase();
    mSolver = new btSequentialImpulseConstraintSolver;
    mDynamicWorld = new btDiscreteDynamicsWorld(mDispatcher, mInterface, mSolver, mCollisionConfiguration);

    mDynamicWorld->setGravity(btVector3(0, mGravity, 0));
}

void PhysicsService::Terminate()
{
    SafeReleasePhysics(mDynamicWorld);
    SafeReleasePhysics(mSolver);
    SafeReleasePhysics(mInterface);
    SafeReleasePhysics(mDispatcher);
    SafeReleasePhysics(mCollisionConfiguration);
}

void PhysicsService::Update(float deltaTime)
{

}

void PhysicsService::DebugUI()
{
    if (ImGui::Checkbox("RenderPhsyics", &mRenderDebugUI))
    {

    }
    if (mRenderDebugUI)
    {
        for (auto& entry : mPhysicsEntries)
        {
            entry.physicsComponent->DebugUI();
            //entry.colliderComponent->DebugUI();
            //entry.rigidBodyComponent->DebugUI();
        }
    }
}

void PhysicsService::SetGravity(float gravity)
{
    mGravity = gravity;
    if (mDynamicWorld != nullptr)
    {
        mDynamicWorld->setGravity(btVector3(0, mGravity, 0));
    }
}

void PhysicsService::Register(PhysicsComponent* physicsComponent)
{
    Entry& entry = mPhysicsEntries.emplace_back();

    auto& gameObject = physicsComponent->GetOwner();
    entry.physicsComponent = physicsComponent;
    entry.transformComponent = gameObject.GetComponent<TransformComponent>();
    //entry.colliderComponent = gameObject.GetComponent<ColliderComponent>();
    //entry.rigidBodyComponent = gameObject.GetComponent<RigidBodyComponent>();

    //if (entry.rigidBodyComponent != nullptr)
    //{
    //    mDynamicWorld->addRigidBody(entry.rigidBodyComponent->GetRigidBody());
    //}
}

void PhysicsService::Unregister(PhysicsComponent* physicsComponent)
{

}