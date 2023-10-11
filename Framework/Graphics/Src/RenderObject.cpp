#include "Precompiled.h"
#include "RenderObject.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;

void RenderObject::Terminate()
{
	diffuseMapId = 0;
	specularMapId = 0;
	bumpMapId = 0;
	normalMapId = 0;
	meshBuffer.Terminate();
}

RenderGroup Graphics::CreateRenderGroup(ModelID id, const Animator* animator)
{
	auto model = ModelManager::Get()->GetModel(id);
	return CreateRenderGroup(*model, animator);
}

RenderGroup Graphics::CreateRenderGroup(const Model& model, const Animator* animator)
{
	RenderGroup renderGroup;
	renderGroup.reserve(model.meshData.size());

	auto TryLoadTexture = [](const auto& textureName) -> TextureId
	{
		if (textureName.empty())
			return 0;

		return TextureManager::Get()->LoadTexture(textureName, false);
	};

	for (auto& meshData : model.meshData)
	{
		auto& renderObject = renderGroup.emplace_back();
		auto& materialData = model.materialData[meshData.materialIndex];
		renderObject.material = materialData.material;
		renderObject.diffuseMapId = TryLoadTexture(materialData.diffuseMapName);
		renderObject.specularMapId = TryLoadTexture(materialData.specularMapName);
		renderObject.bumpMapId = TryLoadTexture(materialData.bumpMapName);
		renderObject.normalMapId = TryLoadTexture(materialData.normalMapName);

		renderObject.meshBuffer.Initialize(meshData.mesh);

		//renderObject.modelId = id;
		renderObject.skeleton = model.skeleton.get();
		renderObject.animator = animator;
	}

	return renderGroup;
}

void Graphics::CleanUpRenderGroup(RenderGroup& renderGroup)
{
	for (auto& renderObject : renderGroup)
	{
		renderObject.Terminate();
	}
}