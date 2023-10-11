#include "Precompiled.h"
#include "GameWorld.h"
#include "GameObjectFactory.h"

using namespace PenguinEngine;

void GameWorld::Initialize(uint32_t capacity)
{
    ASSERT(!mInitialized, "GameWorld is already initialized");
    mInitialized = true;

    for (auto& service : mServices)
    {
        service->Initialize();
    }

    mGameObjectSlots.resize(capacity);
    mFreeSlots.resize(capacity);
    std::iota(mFreeSlots.rbegin(), mFreeSlots.rend(), 0);
}

void GameWorld::Terminate()
{
    ASSERT(!mUpdating, "GameWorld can't terminate while updating");

    if (!mInitialized)
    {
        return;
    }

    for (auto gameObject : mUpdateList)
    {
        DestroyGameObject(gameObject->GetHandle());
    }
    ProcessDestroyList();
    ASSERT(mUpdateList.empty(), "GameWorld failed to clean up all game objects");

    for (auto& service : mServices)
    {
        service->Terminate();
    }

    mInitialized = false;
}

void GameWorld::Update(float deltaTime)
{
    if (Input::InputSystem::Get()->IsKeyPressed(Input::KeyCode::SPACE))
    {
        CreateGameObject("../../Assets/Templates/test_player.json");
    }

    mUpdating = true;
    for (auto& service : mServices)
    {
        service->Update(deltaTime);
    }

    for (size_t i = 0; i < mUpdateList.size(); ++i)
    {
        GameObject* gameObject = mUpdateList[i];
        gameObject->Update(deltaTime);
    }
    mUpdating = false;

    ProcessDestroyList();
}

void GameWorld::Render()
{
    for (auto& service : mServices)
    {
        service->Render();
    }
}

void GameWorld::DebugUI()
{
    ImGui::Begin("Services", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        for (auto& service : mServices)
        {
            service->DebugUI();
        }
    ImGui::End();
}

GameObject* GameWorld::CreateGameObject(const std::filesystem::path& templateFile)
{
    ASSERT(mInitialized, "GameWorld is not initialized");

    if (mFreeSlots.empty())
    {
        ASSERT(false, "GameWorld out of free slots");
        return nullptr;
    }

    const uint32_t freeSlot = mFreeSlots.back();
    mFreeSlots.pop_back();

    auto& slot = mGameObjectSlots[freeSlot];
    auto& newObject = slot.gameObject;
    newObject = std::make_unique<GameObject>();

    // attach components
    GameObjectFactory::Make(templateFile, *newObject);

    GameObjectHandle handle;
    handle.mIndex = freeSlot;
    handle.mGeneration = slot.generation;

    newObject->mWorld = this;
    newObject->mHandle = handle;
    newObject->Initialize();

    mUpdateList.push_back(newObject.get());
    return newObject.get();
}

GameObject* GameWorld::GetGameObject(const GameObjectHandle& handle)
{
    if (!IsValid(handle))
    {
        return nullptr;
    }

    return mGameObjectSlots[handle.mIndex].gameObject.get();
}

void GameWorld::DestroyGameObject(const GameObjectHandle& handle)
{
    if (!IsValid(handle))
    {
        return;
    }

    auto& slot = mGameObjectSlots[handle.mIndex];
    slot.generation++;
    mToBeDestroyed.push_back(handle.mIndex);
}

bool GameWorld::IsValid(const GameObjectHandle& handle) const
{
    if (handle.mIndex < 0 || handle.mIndex >= mGameObjectSlots.size())
    {
        return false;
    }

    if (mGameObjectSlots[handle.mIndex].generation != handle.mGeneration)
    {
        return false;
    }

    return true;
}

void GameWorld::ProcessDestroyList()
{
    ASSERT(!mUpdating, "GameWorld can't destroy when updating objects");

    for (auto index : mToBeDestroyed)
    {
        auto& slot = mGameObjectSlots[index];

        GameObject* gameObject = slot.gameObject.get();
        ASSERT(!IsValid(gameObject->GetHandle()), "Gameworld object is still valid");

        mUpdateList.erase(std::remove(mUpdateList.begin(), mUpdateList.end(), gameObject));

        gameObject->Terminate();

        slot.gameObject.reset();
        mFreeSlots.push_back(index);
    }

    mToBeDestroyed.clear();
}