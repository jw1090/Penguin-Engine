#pragma once

#include "Material.h"
#include "MeshBuffer.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Skeleton.h"
#include "Animator.h"

namespace PenguinEngine::Graphics
{
	class RenderObject
	{
	public:
		void Terminate();
		
		Transform transform;

		Material material;

		TextureId diffuseMapId = 0;
		TextureId specularMapId = 0;
		TextureId bumpMapId = 0;
		TextureId normalMapId = 0;

		MeshBuffer meshBuffer;

		ModelID modelId = 0;
		const Skeleton* skeleton = nullptr;
		const Animator* animator = nullptr;
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]]RenderGroup CreateRenderGroup(ModelID id, const Animator* animator = nullptr);
	[[nodiscard]]RenderGroup CreateRenderGroup(const Model& model, const Animator* animator = nullptr);
	void CleanUpRenderGroup(RenderGroup& renderGroup);

	template <class Effect>
	void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
	{
		for (auto& renderObject : renderGroup)
		{
			effect.Render(renderObject);
		}
	}
}