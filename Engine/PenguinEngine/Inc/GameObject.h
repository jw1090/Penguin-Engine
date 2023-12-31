#pragma once

#include "Component.h"
#include "GameObjectHandle.h"

namespace PenguinEngine
{
    class GameWorld;

    class GameObject final
    {
    public:
        GameObject() = default;

        void Initialize();
        void Terminate();

        void Update(float deltaTime);
        void DebugUI();

        template<class ComponentType>
        ComponentType* AddComponent()
        {
            ASSERT(!mInitialized, "GameObject -- cannot add a component when the GameObject after it is initialized!");
            auto& newComponent = mComponents.emplace_back(std::make_unique<ComponentType>());
            newComponent->mOwner = this;
            return static_cast<ComponentType*>(newComponent.get());
        }

        template<class ComponentType>
        ComponentType* GetComponent()
        {
            auto constThis = static_cast<const GameObject*>(this);
            return const_cast<ComponentType*>(constThis->GetComponent<ComponentType>());
        }

        template<class ComponentType>
        const ComponentType* GetComponent() const
        {
            for (auto& component : mComponents)
            {
                if (component->GetTypeId() == ComponentType::StaticGetTypeId())
                {
                    return static_cast<ComponentType*>(component.get());
                }
            }

            return nullptr;
        }

        void SetName(const char* name) { mName = name; }
        const std::string& GetName() const { return mName; }

        GameWorld& GetWorld() { return *mWorld; }
        const GameWorld& GetWorld() const { return *mWorld; }

        const GameObjectHandle& GetHandle() const { return mHandle; }

    private:
        friend class GameWorld;
        using Components = std::vector<std::unique_ptr<Component>>;

        GameWorld* mWorld = nullptr;
        GameObjectHandle mHandle;

        Components mComponents;
        std::string mName = "Empty";
        bool mInitialized = false;
    };
}