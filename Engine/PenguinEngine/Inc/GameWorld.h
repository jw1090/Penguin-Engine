#pragma once

#include "GameObject.h"
#include "Service.h"

namespace PenguinEngine
{
    class GameWorld final
    {
    public:
        void Initialize(uint32_t capacity);
        void Terminate();

        void Update(float deltaTime);
        void Render();
        void DebugUI();

        template<class ServiceType>
        ServiceType* AddService()
        {
            static_assert(std::is_base_of_v<Service, ServiceType>, "Gameworld -- services must derive from Service");
            ASSERT(!mInitialized, "GameWorld -- cannot add services after gameworld is initialized");
            auto& newService = mServices.emplace_back(std::make_unique<ServiceType>());
            newService->mWorld = this;
            return static_cast<ServiceType*>(newService.get());
        }

        template<class ServiceType>
        ServiceType* GetService()
        {
            auto constThis = static_cast<const GameWorld*>(this);
            return const_cast<ServiceType*>(constThis->GetService<ServiceType>());
        }

        template<class ServiceType>
        const ServiceType* GetService() const
        {
            for (auto& service : mServices)
            {
                if (service->GetTypeId() == ServiceType::StaticGetTypeId())
                {
                    return static_cast<ServiceType*>(service.get());
                }
            }

            return nullptr;
        }

        GameObject* CreateGameObject(const std::filesystem::path& templateFile);
        GameObject* GetGameObject(const GameObjectHandle& handle);
        void DestroyGameObject(const GameObjectHandle& handle);

    private:
        bool IsValid(const GameObjectHandle& handle) const;
        void ProcessDestroyList();

        struct Slot
        {
            std::unique_ptr<GameObject> gameObject;
            uint32_t generation = 0;
        };

        using Services = std::vector<std::unique_ptr<Service>>;
        using GameObjectSlots = std::vector<Slot>;
        using GameObjectPtrs = std::vector<GameObject*>;

        GameObjectSlots mGameObjectSlots;
        std::vector<uint32_t> mFreeSlots;
        std::vector<uint32_t> mToBeDestroyed;

        Services mServices;

        GameObjectPtrs mUpdateList;

        bool mInitialized = false;
        bool mUpdating = false;
    };
}