#pragma once

namespace PenguinEngine
{
    class GameObject;

    namespace GameObjectFactory
    {
        void Make(const std::filesystem::path& templateFile, GameObject& gameObject);
    }
}