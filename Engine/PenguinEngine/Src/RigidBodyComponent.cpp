#include "Precompiled.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"

#include "GameObject.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;

void RigidBodyComponent::Initialize()
{
   /* auto colliderComponent = GetOwner().GetComponent<ColliderComponent>();
    auto transformComponent = GetOwner().GetComponent<TransformComponent>();

    auto collisionShape = mColliderComponent->GetCollisionShape();
    btVector3 localIntertia(0.0f, 0.0f, 0.0f);

    if (IsDynamic)
    {
        collisionShape->calculateLocalInertia(mMass, localIntertia);
    }

    btDefaultMotionState* motionState = new btDefaultMotionState(ConvertToBTTransform(*transformComponent));
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mMass, motionState, collisionShape, localIntertia);
    mRigidBody = new btRigidBody(rbInfo);*/
}

void RigidBodyComponent::Terminate()
{
    /*if (mRigidBody->getMotionState())
    {
        delete mRigidBody->getMotionState();
    }

    SafeReleasePhysics(mRigidBody);*/
}

void RigidBodyComponent::SetMass(float mass)
{
    mMass = mass;
}

bool RigidBodyComponent::IsDynamic() const
{
    return mMass > 0.0f;
}

btRigidBody* RigidBodyComponent::GetRigidBody()
{
    return mRigidBody;
}