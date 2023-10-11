#include "Precompiled.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "ModelComponent.h"
#include "CameraComponent.h"
#include "FPSCameraControllerComponent.h"
#include "AnimatorComponent.h"

using namespace PenguinEngine;

namespace rj = rapidjson;

void GameObjectFactory::Make(const std::filesystem::path& templateFile, GameObject& gameObject)
{
    static float shiftX = 0.0f;

    FILE* file = nullptr;
    auto err = fopen_s(&file, templateFile.u8string().c_str(), "r");
    ASSERT(err == 0 && file != nullptr, "GameObjectFactory -- failed to open template file %s", templateFile.u8string().c_str());

    char readBuffer[65536];
    rj::FileReadStream readStream(file, readBuffer, sizeof(readBuffer));

    fclose(file);

    rj::Document doc;
    doc.ParseStream(readStream);

    auto components = doc["Components"].GetObj();
    for (auto& component : components)
    {
        const char* componentName = component.name.GetString();
        if (strcmp(componentName, "AnimatorComponent") == 0)
        {
            auto animatorComponent = gameObject.AddComponent<AnimatorComponent>();
        }
        else if (strcmp(componentName, "CameraComponent") == 0)
        {
            auto cameraComponent = gameObject.AddComponent<CameraComponent>();
            if (component.value.HasMember("Position"))
            {
                const auto& center = component.value["Position"].GetArray();
                const float x = center[0].GetFloat();
                const float y = center[1].GetFloat();
                const float z = center[2].GetFloat();
                cameraComponent->GetCamera().SetPosition({ x, y, z });
            }
            if (component.value.HasMember("LookAt"))
            {
                const auto& center = component.value["LookAt"].GetArray();
                const float x = center[0].GetFloat();
                const float y = center[1].GetFloat();
                const float z = center[2].GetFloat();
                cameraComponent->GetCamera().SetLookAt({ x, y, z });
            }
            if (component.value.HasMember("FOV"))
            {
                const float fov = component.value["FOV"].GetFloat();
                cameraComponent->GetCamera().SetFov(fov);
            }
            if (component.value.HasMember("AspectRatio"))
            {
                const float aspectRatio = component.value["AspectRatio"].GetFloat();
                cameraComponent->GetCamera().SetAspectRatio(aspectRatio);
            }
            if (component.value.HasMember("NearPlane"))
            {
                const float nearPlane = component.value["NearPlane"].GetFloat();
                cameraComponent->GetCamera().SetNearPlane(nearPlane);
            }
            if (component.value.HasMember("FarPlane"))
            {
                const float farPlane = component.value["FarPlane"].GetFloat();
                cameraComponent->GetCamera().SetFarPlane(farPlane);
            }
        }
        else if (strcmp(componentName, "ColliderComponent") == 0)
        {

        }
        else if (strcmp(componentName, "FPSCameraControllerComponent") == 0)
        {
            auto fpsCameraController = gameObject.AddComponent<FPSCameraControllerComponent>();
            if (component.value.HasMember("MoveSpeed"))
            {
                const float moveSpeed = component.value["MoveSpeed"].GetFloat();
                fpsCameraController->SetMoveSpeed(moveSpeed);
            }
            if (component.value.HasMember("TurnSpeed"))
            {
                const float moveSpeed = component.value["TurnSpeed"].GetFloat();
                fpsCameraController->SetTurnSpeed(moveSpeed);
            }
        }
        else if (strcmp(componentName, "ModelComponent") == 0)
        {
            auto modelComponent = gameObject.AddComponent<ModelComponent>();
            if (component.value.HasMember("FileName"))
            {
                const char* fileName = component.value["FileName"].GetString();
                modelComponent->SetFileName(fileName);
            }
            if (component.value.HasMember("Animations"))
            {
                const auto& animationNames = component.value["Animations"].GetArray();
                for (const auto& animationName : animationNames)
                {
                    const char* animation = animationName.GetString();
                    modelComponent->AddAnimation(animation);
                }
            }
        }
        else if (strcmp(componentName, "TransformComponent") == 0)
        {
            auto transformComponent = gameObject.AddComponent<TransformComponent>();
            if (component.value.HasMember("Position"))
            {
                const auto& center = component.value["Position"].GetArray();
                const float x = center[0].GetFloat() + shiftX;
                const float y = center[1].GetFloat();
                const float z = center[2].GetFloat();
                transformComponent->position = { x, y, z };

                shiftX += 2.0f;
            }
            if (component.value.HasMember("Rotation"))
            {
                const auto& rotation = component.value["Rotation"].GetArray();
                const float x = rotation[0].GetFloat();
                const float y = rotation[1].GetFloat();
                const float z = rotation[2].GetFloat();
                const float w = (rotation.Size() > 3) ? rotation[3].GetFloat() : 1.0f;
                transformComponent->rotation = { x, y, z, w };
            }
            if (component.value.HasMember("Scale"))
            {
                const auto& scale = component.value["Scale"].GetArray();
                float x, y, z;
                if (scale.Size() > 1)
                {
                    x = scale[0].GetFloat();
                    y = scale[1].GetFloat();
                    z = scale[2].GetFloat();
                }
                else
                {
                    x = scale[0].GetFloat();
                    y = scale[0].GetFloat();
                    z = scale[0].GetFloat();
                }
                transformComponent->scale = { x, y, z };
            }
        }

        // Add more components...
    }
}