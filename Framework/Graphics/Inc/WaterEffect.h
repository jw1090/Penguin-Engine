#pragma once

#include "ConstantBuffer.h"
#include "LightType.h"
#include "Material.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "BlendState.h"

namespace PenguinEngine::Graphics
{
	class Camera;
	class RenderObject;

	class WaterEffect
	{
	public:
		void Initialize();
		void Terminate();
		
		void Begin();
		void End();
		
		void Render(RenderObject& renderObject);

		void SetCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);
		void SetBumpWeight(float weight);

		void Update(float runningTime, float waterWeight, RenderObject& renderObject);

		void DebugUI(RenderObject& waterRenderObject);
		void DebugUI(std::string name, RenderObject& waterRenderObject);

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

		struct SettingsData
		{
			int useDiffuseMap = 1;
			int useSpecularMap = 1;
			int useBumpMap = 1;
			int useNormalMap = 1;
		};

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		BlendState mBlendState;

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using LightBuffer = TypedConstantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedConstantBuffer<Material>;
		using SettingsBuffer = TypedConstantBuffer<SettingsData>;

		const Camera* mCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;

		TransformBuffer mTransformBuffer;
		LightBuffer mLightBuffer;
		MaterialBuffer mMaterialBuffer;
		SettingsBuffer mSettingsBuffer;

		Sampler mSampler;

		SettingsData mSettingsData;
		float mBumpWeight = 0.0f;

		float mWaterHeight = 0.0f;
		bool mWaterSway = true;
	};
}