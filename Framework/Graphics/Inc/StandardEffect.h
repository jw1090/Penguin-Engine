#pragma once

#include "ConstantBuffer.h"
#include "LightType.h"
#include "Material.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace PenguinEngine::Graphics
{
	class Camera;
	class RenderObject;

	class StandardEffect
	{
	public:
		void Initialize();
		void Terminate();
		
		void Begin();
		void End();
		
		void Render(const RenderObject& renderObject);

		void SetCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);
		void SetBumpWeight(float weight) { mBumpWeight = weight; }

		void DebugUI();
		void DebugUI(std::string);

		void UseDiffuseMap(bool use) { mSettingsData.useDiffuseMap = use ? 1 : 0; }
		void UseSpecularMap(bool use) { mSettingsData.useDiffuseMap = use ? 1 : 0; }
		void UseBumpMap(bool use) { mSettingsData.useDiffuseMap = use ? 1 : 0; }
		void UseNormalMap(bool use) { mSettingsData.useDiffuseMap = use ? 1 : 0; }

	private:
		struct TransformData
		{
			Math::Matrix4 world;
			Math::Matrix4 wvp;
			Math::Vector3 viewPosition;
			float bumpWeight = 0.2f;
		};

		struct BoneTransformData
		{
			static constexpr size_t MaxBoneCount = 256;
			Math::Matrix4 boneTransforms[MaxBoneCount];
		};

		struct SettingsData
		{
			int useDiffuseMap = 1;
			int useSpecularMap = 1;
			int useBumpMap = 1;
			int useNormalMap = 1;
			
			int useShadowMap = 1; // bool in HLSL is 4 bytes
			int useSkinning = 0;
			float depthBias = 0.0f;
			float padding = {}; // padding to keep structure in 16 byte
		};

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using BoneTransformBuffer = ConstantBuffer;
		using LightBuffer = TypedConstantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedConstantBuffer<Material>;
		using SettingsBuffer = TypedConstantBuffer<SettingsData>;

		const Camera* mCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;

		TransformBuffer mTransformBuffer;
		BoneTransformBuffer mBoneTransformBuffer;
		LightBuffer mLightBuffer;
		MaterialBuffer mMaterialBuffer;
		SettingsBuffer mSettingsBuffer;

		Sampler mSampler;

		SettingsData mSettingsData;
		float mBumpWeight = 0.0f;
	};
}