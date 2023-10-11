#pragma once

#include "Component.h"

namespace PenguinEngine
{
    class ColliderComponent;

    class RigidBodyComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::RigidBody);

        void Initialize();
        void Terminate();

        void SetMass(float mass);
        bool IsDynamic() const;

        btRigidBody* GetRigidBody();

    private:
        ColliderComponent* mColliderComponent = nullptr;
        btRigidBody* mRigidBody = nullptr;

        float mMass = 0.0f;
    };
}