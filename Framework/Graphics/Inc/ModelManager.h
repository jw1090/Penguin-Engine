#pragma once
#include "Model.h"

namespace PenguinEngine::Graphics
{
	using ModelID = size_t;
	class ModelManager final
	{
	public:
		static void StaticInitialize();
		static void StaticTerminate();
		static ModelManager* Get();

	public:
		ModelManager() = default;
		~ModelManager() = default;

		ModelID GetModelID(std::filesystem::path fileName);
		ModelID LoadModel(std::filesystem::path fileName);
		void AddAnimation(ModelID id, std::filesystem::path fileName);
		const Model* GetModel(ModelID id);

	private:
		using ModelCache = std::map< ModelID, std::unique_ptr<Model> >;

		ModelCache mInventory;
	};
}