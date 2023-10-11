#include "Precompiled.h"
#include "WaterEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;

void WaterEffect::Initialize()
{
	mVertexShader.Initialize<Vertex>(L"../../Assets/Shaders/Water.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/Water.fx");

	mBlendState.Initialize(BlendState::Mode::AlphaBlend);

	mTransformBuffer.Initialize();
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingsBuffer.Initialize();

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void WaterEffect::Terminate()
{
	mSampler.Terminate();

	mSettingsBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mTransformBuffer.Terminate();

	mBlendState.Terminate();

	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void WaterEffect::Begin()
{
	ASSERT(mCamera != nullptr, "WaterEffect - no camera set!");
	ASSERT(mDirectionalLight != nullptr, "WaterEffect - no light set!");

	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);

	mLightBuffer.BindVS(1);
	mLightBuffer.BindPS(1);

	mMaterialBuffer.BindPS(2);

	mSettingsBuffer.BindPS(3);
	mSettingsBuffer.BindVS(3);

	mSampler.BindPS(0);
	mSampler.BindVS(0);
}

void WaterEffect::End()
{

}

void WaterEffect::Render(RenderObject& renderObject)
{
	const auto& matWorld = renderObject.transform.GetMatrix4();
	const auto& matView = mCamera->GetViewMatrix();
	const auto& matProj = mCamera->GetProjectionMatrix();

	TransformData transformData;
	transformData.world = Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	transformData.viewPosition = mCamera->GetPosition();
	transformData.bumpWeight = mBumpWeight;
	mTransformBuffer.Update(transformData);

	mLightBuffer.Update(*mDirectionalLight);
	mMaterialBuffer.Update(renderObject.material);

	SettingsData settingsData;
	if (mSettingsData.useDiffuseMap == 0 || renderObject.diffuseMapId == 0)
	{
		settingsData.useDiffuseMap = 0;
	}
	if (mSettingsData.useSpecularMap == 0 || renderObject.specularMapId == 0)
	{
		settingsData.useSpecularMap = 0;
	}
	if (mSettingsData.useBumpMap == 0 || renderObject.bumpMapId == 0)
	{
		settingsData.useBumpMap = 0;
	}
	if (mSettingsData.useNormalMap == 0 || renderObject.normalMapId == 0)
	{
		settingsData.useNormalMap = 0;
	}
	mSettingsBuffer.Update(settingsData);

	auto tm = TextureManager::Get();
	tm->BindPS(renderObject.diffuseMapId, 0);
	tm->BindPS(renderObject.specularMapId, 1);
	tm->BindVS(renderObject.bumpMapId, 2);
	tm->BindPS(renderObject.normalMapId, 3);

	mBlendState.Set();
	renderObject.meshBuffer.Render();
	BlendState::ClearState();
}

void WaterEffect::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}

void WaterEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	mDirectionalLight = &directionalLight;
}

void WaterEffect::SetBumpWeight(float weight)
{
	mBumpWeight = weight;
	mWaterHeight = 1.4f * mBumpWeight;
}

void WaterEffect::Update(float runningTime, float waterWeight, RenderObject& renderobject)
{
	if (mWaterSway == true)
	{
		float height = mWaterHeight * abs(cos(runningTime * 0.5f) * 0.2f);
		float sway = mWaterHeight * abs(sin(runningTime * 0.3f) * 0.2f);
		renderobject.transform.position.y = height;
		mBumpWeight = sway + waterWeight;
	}
}

void WaterEffect::DebugUI(RenderObject& waterRenderObject)
{
	if (ImGui::CollapsingHeader("WaterEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat("Opacity", &waterRenderObject.material.diffuse.a, 0.005f, 0.0f, 1.0f))
		{
			waterRenderObject.material.diffuse.a = waterRenderObject.material.diffuse.a;
		}

		ImGui::DragFloat("Bump Weight", &mBumpWeight, 0.1f);

		bool useDiffuseMap = (mSettingsData.useDiffuseMap == 1);
		ImGui::Checkbox("Use Diffuse Map", &useDiffuseMap);
		mSettingsData.useDiffuseMap = useDiffuseMap ? 1 : 0;

		bool useSpecularMap = (mSettingsData.useSpecularMap == 1);
		ImGui::Checkbox("Use Specular Map", &useSpecularMap);
		mSettingsData.useSpecularMap = useSpecularMap ? 1 : 0;

		bool useBumpMap = (mSettingsData.useBumpMap == 1);
		ImGui::Checkbox("Use Bump Map", &useBumpMap);
		mSettingsData.useBumpMap = useBumpMap ? 1 : 0;

		bool useNormalMap = (mSettingsData.useNormalMap == 1);
		ImGui::Checkbox("Use Normal Map", &useNormalMap);
		mSettingsData.useNormalMap = useNormalMap ? 1 : 0;

		bool useWaterSway = (mWaterSway == 1);
		ImGui::Checkbox("Use Water Sway", &useWaterSway);
		mWaterSway = useWaterSway ? 1 : 0;
	}
}

void WaterEffect::DebugUI(std::string name, RenderObject& waterRenderObject)
{
	const char* headerName = name.c_str();

	if (ImGui::CollapsingHeader(headerName, ImGuiTreeNodeFlags_DefaultOpen))
	{
		std::string opactiyString = "Opacity##" + name;
		const char* opacityName = opactiyString.c_str();
		if (ImGui::DragFloat(opacityName, &waterRenderObject.material.diffuse.a, 0.005f, 0.0f, 1.0f))
		{
			waterRenderObject.material.diffuse.a = waterRenderObject.material.diffuse.a;
		}

		std::string bumpWeightString = "BumpWeight##" + name;
		const char* bumpWeightName = bumpWeightString.c_str();
		ImGui::DragFloat(bumpWeightName, &mBumpWeight, 0.1f);

		std::string diffuseString = "Use Diffuse Map##" + name;
		const char* diffuseName = diffuseString.c_str();
		bool useDiffuseMap = (mSettingsData.useDiffuseMap == 1);
		ImGui::Checkbox(diffuseName, &useDiffuseMap);
		mSettingsData.useDiffuseMap = useDiffuseMap ? 1 : 0;

		std::string specString = "Use Specular Map##" + name;
		const char* specName = specString.c_str();
		bool useSpecularMap = (mSettingsData.useSpecularMap == 1);
		ImGui::Checkbox(specName, &useSpecularMap);
		mSettingsData.useSpecularMap = useSpecularMap ? 1 : 0;

		std::string bumpString = "Use Bump Map##" + name;
		const char* bumpName = bumpString.c_str();
		bool useBumpMap = (mSettingsData.useBumpMap == 1);
		ImGui::Checkbox(bumpName, &useBumpMap);
		mSettingsData.useBumpMap = useBumpMap ? 1 : 0;

		std::string normalString = "Use Normal Map##" + name;
		const char* normalName = normalString.c_str();
		bool useNormalMap = (mSettingsData.useNormalMap == 1);
		ImGui::Checkbox(normalName, &useNormalMap);
		mSettingsData.useNormalMap = useNormalMap ? 1 : 0;

		std::string swayString = "Use Water Sway##" + name;
		const char* swayName = swayString.c_str();
		bool useWaterSway = (mWaterSway == 1);
		ImGui::Checkbox("Use Water Sway", &useWaterSway);
		mWaterSway = useWaterSway ? 1 : 0;
	}
}