#include "Precompiled.h"
#include "ModelIO.h"

#include "Model.h"
#include "AnimationBuilder.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;


void AnimationIO::Write(FILE* file, const Animation& animation)
{
	uint32_t count = animation.mPositionKeys.size();
	fprintf_s(file, "PositionKeysCount: %d\n", count);
	for (auto& k : animation.mPositionKeys)
	{
		fprintf_s(file, "%f %f %f %f\n", k.time, k.key.x, k.key.y, k.key.z);
	}
	count = animation.mRotationKeys.size();
	fprintf_s(file, "RotationKeysCount: %d\n", count);
	for (auto& k : animation.mRotationKeys)
	{
		fprintf_s(file, "%f %f %f %f %f\n", k.time, k.key.x, k.key.y, k.key.z, k.key.w);
	}
	count = animation.mScaleKeys.size();
	fprintf_s(file, "ScaleKeysCount: %d\n", count);
	for (auto& k : animation.mScaleKeys)
	{
		fprintf_s(file, "%f %f %f %f\n", k.time, k.key.x, k.key.y, k.key.z);
	}

}

void AnimationIO::Read(FILE* file, Animation& animation)
{
	AnimationBuilder builder;
	uint32_t numPositionKeys, numRotationKeys, numScaleKeys;
	fscanf_s(file, "PositionKeysCount: %d\n", &numPositionKeys);
	for (uint32_t k = 0; k < numPositionKeys; ++k)
	{
		float time = 0.0f;
		Math::Vector3 pos;
		fscanf_s(file, "%f %f %f %f\n", &time, &pos.x, &pos.y, &pos.z);
		builder.AddPositionKey(pos, time);
	}
	fscanf_s(file, "RotationKeysCount: %d\n", &numRotationKeys);
	for (uint32_t k = 0; k < numRotationKeys; ++k)
	{
		float time = 0.0f;
		Math::Quaternion rot;
		fscanf_s(file, "%f %f %f %f %f\n", &time, &rot.x, &rot.y, &rot.z, &rot.w);
		builder.AddRotationKey(rot, time);
	}
	fscanf_s(file, "ScaleKeysCount: %d\n", &numScaleKeys);
	for (uint32_t k = 0; k < numScaleKeys; ++k)
	{
		float time = 0.0f;
		Math::Vector3 scale;
		fscanf_s(file, "%f %f %f %f\n", &time, &scale.x, &scale.y, &scale.z);
		builder.AddScaleKey(scale, time);
	}

	animation = builder.Build();
}

void ModelIO::SaveModel(std::filesystem::path filePath, const Model& model)
{
	if (model.meshData.empty())
		return;

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (file == nullptr)
		return;

	const uint32_t meshCount = static_cast<uint32_t>(model.meshData.size());
	fprintf_s(file, "MeshCount: %d\n", meshCount);
	for (uint32_t i = 0; i < meshCount; ++i)
	{
		const auto& meshData = model.meshData[i];
		fprintf_s(file, "MaterialIndex: %d\n", meshData.materialIndex);

		const auto& mesh = meshData.mesh;
		const uint32_t vertexCount = static_cast<uint32_t>(mesh.vertices.size());
		fprintf_s(file, "VertexCount: %d\n", vertexCount);

		for (auto& vertex : mesh.vertices)
		{
			// 4 indices
			// 4 weights
			fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d %d\n",
				vertex.position.x, vertex.position.y, vertex.position.z,
				vertex.normal.x, vertex.normal.y, vertex.normal.z,
				vertex.tangent.x, vertex.tangent.y, vertex.tangent.z,
				vertex.uvCoord.x, vertex.uvCoord.y,
				vertex.boneWeights[0], vertex.boneWeights[1], vertex.boneWeights[2], vertex.boneWeights[3],
				vertex.boneIndices[0], vertex.boneIndices[1], vertex.boneIndices[2], vertex.boneIndices[3]
			);
		}

		const uint32_t indexCount = static_cast<uint32_t>(mesh.indices.size());
		fprintf_s(file, "IndexCount: %d\n", indexCount);

		for (size_t i = 0; i < indexCount; i += 3)
		{
			fprintf_s(file, "%d %d %d\n",
				mesh.indices[i],
				mesh.indices[i + 1u],
				mesh.indices[i + 2u]);
		}
	}

	fclose(file);
}


void ModelIO::LoadModel(std::filesystem::path filePath, Model& model)
{
	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (file == nullptr)
		return;

	uint32_t meshCount = 0;
	fscanf_s(file, "MeshCount: %d\n", &meshCount);

	model.meshData.resize(meshCount);
	for (uint32_t i = 0; i < meshCount; ++i)
	{
		auto& meshData = model.meshData[i];
		fscanf_s(file, "MaterialIndex: %d\n", &meshData.materialIndex);

		auto& mesh = meshData.mesh;

		uint32_t vertexCount = 0;
		fscanf_s(file, "VertexCount: %d\n", &vertexCount);
		mesh.vertices.resize(vertexCount);

		for (auto& vertex : mesh.vertices)
		{
			fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d %d\n",
				&vertex.position.x, &vertex.position.y, &vertex.position.z,
				&vertex.normal.x, &vertex.normal.y, &vertex.normal.z,
				&vertex.tangent.x, &vertex.tangent.y, &vertex.tangent.z,
				&vertex.uvCoord.x, &vertex.uvCoord.y,
				&vertex.boneWeights[0], &vertex.boneWeights[1], &vertex.boneWeights[2], &vertex.boneWeights[3],
				&vertex.boneIndices[0], &vertex.boneIndices[1], &vertex.boneIndices[2], &vertex.boneIndices[3]
			);
		}

		uint32_t indexCount = 0;
		fscanf_s(file, "IndexCount: %d\n", &indexCount);
		mesh.indices.resize(indexCount);

		for (size_t i = 0; i < indexCount; i += 3)
		{
			fscanf_s(file, "%d %d %d\n",
				&mesh.indices[i],
				&mesh.indices[i + 1u],
				&mesh.indices[i + 2u]);
		}
	}

	fclose(file);
}


void ModelIO::SaveMaterial(std::filesystem::path filePath, const Model& model)
{
	if (model.materialData.empty())
	{
		return;
	}
	filePath.replace_extension("material");

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (file == nullptr)
	{
		return;
	}

	uint32_t materialCount = (uint32_t)model.materialData.size();
	fprintf_s(file, "MaterialCount: %d\n", materialCount);
	for (auto& materialData : model.materialData)
	{
		auto& material = materialData.material;
		fprintf_s(file, "%f %f %f %f\n", material.ambient.r, material.ambient.g, material.ambient.b, material.ambient.a);
		fprintf_s(file, "%f %f %f %f\n", material.diffuse.r, material.diffuse.g, material.diffuse.b, material.diffuse.a);
		fprintf_s(file, "%f %f %f %f\n", material.specular.r, material.specular.g, material.specular.b, material.specular.a);
		fprintf_s(file, "%f %f %f %f\n", material.emissive.r, material.emissive.g, material.emissive.b, material.emissive.a);
		fprintf_s(file, "%f\n", material.power);

		fprintf_s(file, "%s\n", materialData.diffuseMapName.empty() ? "none" : materialData.diffuseMapName.c_str());
		fprintf_s(file, "%s\n", materialData.specularMapName.empty() ? "none" : materialData.specularMapName.c_str());
		fprintf_s(file, "%s\n", materialData.bumpMapName.empty() ? "none" : materialData.bumpMapName.c_str());
		fprintf_s(file, "%s\n", materialData.normalMapName.empty() ? "none" : materialData.normalMapName.c_str());
	}

	fclose(file);
}

void ModelIO::LoadMaterial(std::filesystem::path filePath, Model& model)
{
	filePath.replace_extension("material");

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (file == nullptr)
	{
		return;
	}

	uint32_t materialCount = 0;
	fscanf_s(file, "MaterialCount: %d\n", &materialCount);
	
	auto TryReadTextureName = [&](auto& fileName)
	{
		char buffer[MAX_PATH]{};
		fscanf_s(file, "%s\n", buffer, (uint32_t)sizeof(buffer));
		if (strcmp(buffer, "none") != 0)
		{
			fileName = filePath.replace_filename(buffer).string();
		}
	};
	model.materialData.resize(materialCount);
	for (auto& materialData : model.materialData)
	{
		auto& material = materialData.material;
		fscanf_s(file, "%f %f %f %f\n", &material.ambient.r, &material.ambient.g, &material.ambient.b, &material.ambient.a);
		fscanf_s(file, "%f %f %f %f\n", &material.diffuse.r, &material.diffuse.g, &material.diffuse.b, &material.diffuse.a);
		fscanf_s(file, "%f %f %f %f\n", &material.specular.r, &material.specular.g, &material.specular.b, &material.specular.a);
		fscanf_s(file, "%f %f %f %f\n", &material.emissive.r, &material.emissive.g, &material.emissive.b, &material.emissive.a);
		fscanf_s(file, "%f\n", &material.power);

		TryReadTextureName(materialData.diffuseMapName);
		TryReadTextureName(materialData.specularMapName);
		TryReadTextureName(materialData.bumpMapName);
		TryReadTextureName(materialData.normalMapName);
	}

	fclose(file);
}

void ModelIO::SaveSkeleton(std::filesystem::path filePath, const Model& model)
{
	// save the bone list, 
	if (model.skeleton == nullptr)
	{
		return;
	}
	filePath.replace_extension("skeleton");

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (file == nullptr)
	{
		return;
	}

	auto WriteMatrix = [&](auto& m)
	{
		fprintf_s(file, "%f %f %f %f\n", m._11, m._12, m._13, m._14);
		fprintf_s(file, "%f %f %f %f\n", m._21, m._22, m._23, m._24);
		fprintf_s(file, "%f %f %f %f\n", m._31, m._32, m._33, m._34);
		fprintf_s(file, "%f %f %f %f\n", m._41, m._42, m._43, m._44);
	};

	// iterate through the bones and save the list
	uint32_t boneCount = model.skeleton->bones.size();
	fprintf_s(file, "RootBone: %d\n", model.skeleton->root->index);
	fprintf_s(file, "BoneCount: %d\n", boneCount);
	for (uint32_t i = 0; i < boneCount; ++i)
	{
		auto& boneData = model.skeleton->bones[i];
		fprintf_s(file, "BoneName: %s\n", boneData->name.c_str());
		fprintf_s(file, "BoneIndex: %d\n", boneData->index);
		fprintf_s(file, "BoneParentIndex: %d\n", boneData->parentIndex);

		uint32_t childCount = boneData->childrenIndicies.size();
		fprintf_s(file, "BoneChildrenCount: %d\n", childCount);
		for (uint32_t b = 0; b < childCount; ++b)
		{
			fprintf_s(file, "%d\n", boneData->childrenIndicies[b]);
		}

		WriteMatrix(boneData->toParentTransform);
		WriteMatrix(boneData->offsetTransform);
	}

	fclose(file);
}

void ModelIO::LoadSkeleton(std::filesystem::path filePath, Model& model)
{
	filePath.replace_extension("skeleton");

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (file == nullptr)
	{
		return;
	}

	auto ReadMatrix = [&](auto& m)
	{
		fscanf_s(file, "%f %f %f %f\n", &m._11, &m._12, &m._13, &m._14);
		fscanf_s(file, "%f %f %f %f\n", &m._21, &m._22, &m._23, &m._24);
		fscanf_s(file, "%f %f %f %f\n", &m._31, &m._32, &m._33, &m._34);
		fscanf_s(file, "%f %f %f %f\n", &m._41, &m._42, &m._43, &m._44);
	};

	// populate the skeleton
	model.skeleton = std::make_unique<Skeleton>();

	// iterate through the bones and save the list
	int boneCount = 0;
	int rootIndex = 0;
	fscanf_s(file, "RootBone: %d\n", &rootIndex);
	fscanf_s(file, "BoneCount: %d\n", &boneCount);
	model.skeleton->bones.resize(boneCount);
	for (uint32_t i = 0; i < boneCount; ++i)
	{
		model.skeleton->bones[i] = std::make_unique<Bone>();
	}
	model.skeleton->root = model.skeleton->bones[rootIndex].get();
	for (uint32_t i = 0; i < boneCount; ++i)
	{
		uint32_t boneIndex = 0;
		char boneName[MAX_PATH]{};
		fscanf_s(file, "BoneName: %s\n", boneName, (uint32_t)sizeof(boneName));
		fscanf_s(file, "BoneIndex: %d\n", &boneIndex);

		auto& bone = model.skeleton->bones[boneIndex];
		bone->name = std::move(boneName);
		bone->index = boneIndex;
		fscanf_s(file, "BoneParentIndex: %d\n", &bone->parentIndex);
		if (bone->parentIndex > -1)
		{
			bone->parent = model.skeleton->bones[bone->parentIndex].get();
		}

		uint32_t childCount = 0;
		fscanf_s(file, "BoneChildrenCount: %d\n", &childCount);
		if (childCount > 0)
		{
			bone->children.resize(childCount);
			bone->childrenIndicies.resize(childCount);
			for (uint32_t b = 0; b < childCount; ++b)
			{
				uint32_t index = 0;
				fscanf_s(file, "%d\n", &index);
				bone->childrenIndicies[b] = index;
				bone->children[b] = model.skeleton->bones[index].get();
			}
		}

		ReadMatrix(bone->toParentTransform);
		ReadMatrix(bone->offsetTransform);
	}

	fclose(file);
}

void ModelIO::SaveAnimations(std::filesystem::path filePath, const Model& model)
{
	// save the bone list, 
	if (model.skeleton == nullptr)
	{
		return;
	}
	filePath.replace_extension("animset");

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (file == nullptr)
	{
		return;
	}

	uint32_t animClipCount = model.animationClips.size();
	fprintf_s(file, "AnimClipCount: %d\n", animClipCount);
	for (uint32_t i = 0; i < animClipCount; ++i)
	{
		auto& animClipData = model.animationClips[i];
		fprintf_s(file, "AnimClipName: %s\n", animClipData.name.c_str());
		fprintf_s(file, "TickDuration %f\n", animClipData.tickDuration);
		fprintf_s(file, "TicksPerSecond %f\n", animClipData.ticksPerSecond);

		uint32_t boneAnimCount = animClipData.boneAnimations.size();
		fprintf_s(file, "BoneAnimCount: %d\n", boneAnimCount);
		for (uint32_t b = 0; b < boneAnimCount; ++b)
		{
			auto boneAnim = animClipData.boneAnimations[b].get();
			if (boneAnim == nullptr)
			{
				fprintf_s(file, "[EMPTY]\n");
				continue;
			}

			fprintf_s(file, "[ANIMATION]\n");
			AnimationIO::Write(file, *boneAnim);
		}
	}

	fclose(file);
}

void ModelIO::LoadAnimations(std::filesystem::path filePath, Model& model)
{
	filePath.replace_extension("animset");

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (file == nullptr)
	{
		return;
	}

	uint32_t animClipCount = 0;
	fscanf_s(file, "AnimClipCount: %d\n", &animClipCount);
	for (uint32_t i = 0; i < animClipCount; ++i)
	{
		auto& animClipData = model.animationClips.emplace_back();
		char animClipName[MAX_PATH]{};
		fscanf_s(file, "AnimClipName: %s\n", animClipName, (uint32_t)sizeof(animClipName));
		animClipData.name = std::move(animClipName);

		fscanf_s(file, "TickDuration %f\n", &animClipData.tickDuration);
		fscanf_s(file, "TicksPerSecond %f\n", &animClipData.ticksPerSecond);

		uint32_t boneAnimCount = 0;
		fscanf_s(file, "BoneAnimCount: %d\n", &boneAnimCount);
		animClipData.boneAnimations.resize(boneAnimCount);
		for (uint32_t b = 0; b < boneAnimCount; ++b)
		{
			char label[128]{};
			fscanf_s(file, "%s\n", label, (uint32_t)sizeof(label));
			if (strcmp(label, "[ANIMATION]") == 0)
			{
				animClipData.boneAnimations[b] = std::make_unique<Animation>();
				AnimationIO::Read(file, *animClipData.boneAnimations[b]);
			}
		}
	}

	fclose(file);
}