#pragma once

#include "Component.h"

namespace PenguinEngine
{
    class TransformComponent;
    //class RigidBodyComponent;

    class PhysicsComponent : public  Component
    {
    public:
        SET_TYPE_ID(ComponentId::Physics);

        void Initialize() override;
        void Terminate() override;
        void Update(float deltaTime) override;
        void DebugUI() override;

    private:
        const TransformComponent* mTransformComponent = nullptr;
        //const btRigidBody* mRigidBodyComponent = nullptr;
    };
}