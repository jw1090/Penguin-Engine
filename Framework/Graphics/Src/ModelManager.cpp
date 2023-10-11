#include "Precompiled.h"
#include "ModelManager.h"
#include "ModelIO.h"

using namespace PenguinEngine::Graphics;

namespace
{
	std::unique_ptr<ModelManager> sModelManager;
}

void ModelManager::StaticInitialize()
{
	ASSERT(sModelManager == nullptr, "ModelManager -- System already initialized!");
	sModelManager = std::make_unique<ModelManager>();
}

void ModelManager::StaticTerminate()
{
	sModelManager.reset();
}

ModelManager* ModelManager::Get()
{
	ASSERT(sModelManager != nullptr, "ModelManager -- Is not initialized!");
	return sModelManager.get();
}

ModelID ModelManager::GetModelID(std::filesystem::path fileName)
{
	return std::filesystem::hash_value(fileName);
}

ModelID ModelManager::LoadModel(std::filesystem::path fileName)
{
	const auto modelID = GetModelID(fileName);	
	auto [iter, success] = mInventory.insert({ modelID, nullptr });
	if (success)
	{
		auto& modelPtr = iter->second;
		modelPtr = std::make_unique<Model>();
		ModelIO::LoadModel(fileName.c_str(), *modelPtr);
		ModelIO::LoadMaterial(fileName.c_str(), *modelPtr);
		ModelIO::LoadSkeleton(fileName.c_str(), *modelPtr);
		ModelIO::LoadAnimations(fileName.c_str(), *modelPtr);
	}

	return modelID;
}

void ModelManager::AddAnimation(ModelID id, std::filesystem::path fileName)
{
	auto model = mInventory.find(id);
	if (model != mInventory.end())
	{
		ModelIO::LoadAnimations(fileName.c_str(), *model->second);
	}
}

const Model* ModelManager::GetModel(ModelID id)
{
	auto model = mInventory.find(id);

	if (model != mInventory.end())
	{
		return model->second.get();
	}
	return nullptr;
}