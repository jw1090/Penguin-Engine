#pragma once

#include "Component.h"

namespace PenguinEngine
{
    class TransformComponent;

    class ColliderComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::Collider);

        void Initialize() override;
        void Terminate() override;
        void DebugUI() override;

        void SetCenter(const Math::Vector3& center) { mCenter = center; }
        void SetExtend(const Math::Vector3& extend) { mExtend = extend; }

        Math::AABB GetLocalAABB() const;
        Math::AABB GetWorldAABB() const;
    private:
        const TransformComponent* mTransformComponent = nullptr;
        Math::Vector3 mCenter = Math::Vector3::Zero;
        Math::Vector3 mExtend = Math::Vector3::One;
    };
}