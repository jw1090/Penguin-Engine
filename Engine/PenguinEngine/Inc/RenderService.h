#pragma once

#include "Service.h"

namespace PenguinEngine
{
    class CameraService;
    class ModelComponent;
    class TransformComponent;
    class AnimatorComponent;

    class RenderService final : public Service
    {
    public:
        SET_TYPE_ID(ServiceId::Render);

        void Initialize() override;
        void Terminate() override;

        void Update(float deltaTime) override;
        void Render() override;

        void DebugUI() override;

    private:
        friend class ModelComponent;

        void Register(const ModelComponent* modelComponent);
        void Unregister(const ModelComponent* modelComponent);

        struct Entry
        {
            const AnimatorComponent* animatorComponent = nullptr;
            const ModelComponent* modelComponent = nullptr;
            const TransformComponent* transformComponent = nullptr;
            Graphics::RenderGroup renderGroup;
        };

        using RenderEntries = std::vector<Entry>;
        RenderEntries mRenderEntries;

        const CameraService* mCameraService = nullptr;

        Graphics::DirectionalLight mDirectionalLight;
        Graphics::StandardEffect mStandardEffect;
        Graphics::ShadowEffect mShadowEffect;

        float mFPS = 0.0f;
    };
}