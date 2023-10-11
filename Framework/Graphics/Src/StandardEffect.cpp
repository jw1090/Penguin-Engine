#include "Precompiled.h"
#include "StandardEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "AnimationUtil.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;

void StandardEffect::Initialize()
{
	mVertexShader.Initialize<Vertex>(L"../../Assets/Shaders/Standard.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/Standard.fx");

	mTransformBuffer.Initialize();
	mBoneTransformBuffer.Initialize(256 * sizeof(Math::Matrix4));
	mLightBuffer.Initialize();
	mMaterialBuffer.Initialize();
	mSettingsBuffer.Initialize();

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void StandardEffect::Terminate()
{
	mSampler.Terminate();

	mSettingsBuffer.Terminate();
	mMaterialBuffer.Terminate();
	mLightBuffer.Terminate();
	mBoneTransformBuffer.Terminate();
	mTransformBuffer.Terminate();

	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void StandardEffect::Begin()
{
	ASSERT(mCamera != nullptr, "StandardEffect - no camera set!");
	ASSERT(mDirectionalLight != nullptr, "StandardEffect - no light set!");

	mVertexShader.Bind();
	mPixelShader.Bind();

	mTransformBuffer.BindVS(0);

	mBoneTransformBuffer.BindVS(1);

	mLightBuffer.BindVS(2);
	mLightBuffer.BindPS(2);

	mMaterialBuffer.BindPS(3);

	mSettingsBuffer.BindPS(4);
	mSettingsBuffer.BindVS(4);

	mSampler.BindPS(0);
	mSampler.BindVS(0);
}

void StandardEffect::End()
{

}

void StandardEffect::Render(const RenderObject& renderObject)
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

	/*if (renderObject.skeleton != nullptr)
	{
		AnimationUtil::BoneTransforms boneTransforms;
		AnimationUtil::ComputeBoneTransform(renderObject.modelId, boneTransforms, renderObject.animator);
		AnimationUtil::ApplyBoneOffset(renderObject.modelId, boneTransforms);
		for (auto& transform : boneTransforms)
		{
			transform = Math::Transpose(transform);
		}

		boneTransforms.resize(256);
		mBoneTransformBuffer.Update(boneTransforms.data());
	}*/

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
	//settingsData.useSkinning = (renderObject.skeleton != nullptr);
	mSettingsBuffer.Update(settingsData);

	auto tm = TextureManager::Get();
	tm->BindPS(renderObject.diffuseMapId, 0);
	tm->BindPS(renderObject.specularMapId, 1);
	tm->BindVS(renderObject.bumpMapId, 2);
	tm->BindPS(renderObject.normalMapId, 3);

	renderObject.meshBuffer.Render();
}

void StandardEffect::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}

void StandardEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	mDirectionalLight = &directionalLight;
}

void StandardEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("StandardEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{
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
	}
}

void StandardEffect::DebugUI(std::string name)
{
	const char* headerName = name.c_str();

	if (ImGui::CollapsingHeader(headerName, ImGuiTreeNodeFlags_DefaultOpen))
	{
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
	}
}