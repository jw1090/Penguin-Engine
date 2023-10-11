#pragma once

#include "Service.h"

namespace PenguinEngine
{
    class ColliderComponent;
    class PhysicsComponent;
    class RigidBodyComponent;
    class TransformComponent;

    class PhysicsService : public Service
    {
    public:
        SET_TYPE_ID(ServiceId::Physics);

        void Initialize();
        void Terminate();

        void Update(float deltaTime);
        void DebugUI();

        void SetGravity(float gravity);

    private:
        friend class PhysicsComponent;

        void Register(PhysicsComponent* physicsComponent);
        void Unregister(PhysicsComponent* physicsComponent);

        struct Entry
        {
            ColliderComponent* colliderComponent = nullptr;
            PhysicsComponent* physicsComponent = nullptr;
            RigidBodyComponent* rigidBodyComponent = nullptr;
            TransformComponent* transformComponent = nullptr;
        };

        using PhysicsEntries = std::vector<Entry>;
        PhysicsEntries mPhysicsEntries;

        btBroadphaseInterface* mInterface = nullptr;
        btCollisionDispatcher* mDispatcher = nullptr;
        btDefaultCollisionConfiguration* mCollisionConfiguration = nullptr;
        btDiscreteDynamicsWorld* mDynamicWorld = nullptr;
        btSequentialImpulseConstraintSolver* mSolver = nullptr;

        bool mRenderDebugUI = false;
        float mGravity = -9.81f;
    };
}