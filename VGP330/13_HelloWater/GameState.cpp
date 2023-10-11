#include "GameState.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Input;
using namespace PenguinEngine::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ -15.0f, 3.0f, -15.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, -8.0f });

	mDirectionalLight.direction = Math::Normalize({ 0.2f, -0.7f, 0.4f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mStandardEffect.SetBumpWeight(15.0f);

	mWaterEffect.Initialize();
	mWaterEffect.SetCamera(mCamera);
	mWaterEffect.SetDirectionalLight(mDirectionalLight);
	mWaterEffect.SetBumpWeight(mWaterWeight);

	mReflectionEffect.Initialize();
	mReflectionEffect.SetCamera(mCamera);
	mReflectionEffect.SetDirectionalLight(mDirectionalLight);
	mReflectionEffect.SetBumpWeight(mWaterWeight);

	auto tm = TextureManager::Get();

	mSkyboxRenderObject.material.ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	mSkyboxRenderObject.material.diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	mSkyboxRenderObject.material.specular = { 0.0f, 0.0f, 0.0f, 0.0f };
	mSkyboxRenderObject.material.power = 10.0f;
	mSkyboxRenderObject.diffuseMapId = tm->LoadTexture(L"Images/skysphere/sky.jpg");
	mSkyboxRenderObject.meshBuffer.Initialize(MeshBuilder::CreateSkySphere(512, 512, 100.0f));
	mSkyboxRenderObject.transform.rotation.x = 55.0f;

	mGroundRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGroundRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGroundRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGroundRenderObject.material.power = 10.0f;
	mGroundRenderObject.diffuseMapId = tm->LoadTexture(L"Images/mountain/mountain_texture.jpg");
	mGroundRenderObject.normalMapId = tm->LoadTexture(L"Images/mountain/mountain_normal.jpg");
	mGroundRenderObject.specularMapId = tm->LoadTexture(L"Images/mountain/mountain_spec.jpg");
	mGroundRenderObject.bumpMapId = tm->LoadTexture(L"Images/mountain/mountain_height.jpg");
	mGroundRenderObject.meshBuffer.Initialize(MeshBuilder::CreatePlane(512, 512, 0.1f));
	mGroundRenderObject.transform.position.y = -0.5f;

	mWaterRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mWaterRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 0.85f };
	mWaterRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mWaterRenderObject.material.power = 10.0f;
	mWaterRenderObject.diffuseMapId = tm->LoadTexture(L"Images/water/water_texture.jpg");
	mWaterRenderObject.normalMapId = tm->LoadTexture(L"Images/water/water_normal.jpg");
	mWaterRenderObject.specularMapId = tm->LoadTexture(L"Images/water/water_spec.jpg");
	mWaterRenderObject.bumpMapId = tm->LoadTexture(L"Images/water/water_height.jpg");
	mWaterRenderObject.meshBuffer.Initialize(MeshBuilder::CreatePlane(512, 512, 0.1f));

	mReflectionRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mReflectionRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mReflectionRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mReflectionRenderObject.material.power = 10.0f;
	mReflectionRenderObject.diffuseMapId = tm->LoadTexture(L"Images/water/water_texture.jpg");
	mReflectionRenderObject.bumpMapId = tm->LoadTexture(L"Images/water/water_height.jpg");
	mReflectionRenderObject.meshBuffer.Initialize(MeshBuilder::CreatePlane(512, 512, 0.1f));
	mReflectionRenderObject.transform.position.y = -0.5f;

	Model duckModel;
	ModelIO::LoadModel("../../Assets/Models/Duck/duck.model", duckModel);
	mDuckRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mDuckRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDuckRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mDuckRenderObject.material.power = 10.0f;
	mDuckRenderObject.diffuseMapId = tm->LoadTexture(L"Models/Duck/Duck.png");
	mDuckRenderObject.meshBuffer.Initialize(duckModel.meshData[0].mesh);
	mDuckRenderObject.transform.rotation.y = 40.0f;
	mDuckRenderObject.transform.position.x = -6.5f;
	mDuckRenderObject.transform.position.z = -5.0f;
}

void GameState::Terminate()
{
	mReflectionRenderObject.Terminate();
	mWaterEffect.Terminate();
	mGroundRenderObject.Terminate();
	mSkyboxRenderObject.Terminate();

	mReflectionEffect.Terminate();
	mWaterEffect.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	CameraControl(deltaTime);

	mFPS = 1.0f / deltaTime;

	InputSystem* inputSystem = InputSystem::Get();

	if (inputSystem->IsKeyPressed(KeyCode::SPACE))
	{
		mPause = !mPause;
	}

	const float dt = mPause ? 0.0f : deltaTime;
	mRunningTime += dt;

	mWaterEffect.Update(mRunningTime, mWaterWeight, mWaterRenderObject);
	mWaterEffect.Update(mRunningTime, mWaterWeight - 0.5f, mDuckRenderObject);
	//mReflectionEffect.Update(mRunningTime, mWaterWeight, mReflectionRenderObject);

	mDuckRenderObject.transform.rotation.y += deltaTime * 0.2f;
	mSkyboxRenderObject.transform.rotation.y += deltaTime * 0.02f;
	mSkyboxRenderObject.transform.rotation.x += deltaTime * 0.01f;

	float range = 0.5f * cos(mRunningTime * 0.5f);
	mDirectionalLight.direction.z = range;
}

void GameState::Render()
{
	mStandardEffect.Begin();
	{
		mStandardEffect.Render(mSkyboxRenderObject);
		mStandardEffect.Render(mGroundRenderObject);
		mStandardEffect.Render(mDuckRenderObject);
	}
	mStandardEffect.End();

	mWaterEffect.Begin();
	{
		mWaterEffect.Render(mWaterRenderObject);
	}
	mWaterEffect.End();

	SimpleDraw::Render(mCamera);

	mReflectionEffect.Begin();
	{
		mReflectionEffect.Render(mReflectionRenderObject);
	}
	mReflectionEffect.End();
}


void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("fps: %f %s", mFPS, mPause ? "(paused)" : "");
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.01f, -3.0f, 3.0f))
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	mStandardEffect.DebugUI("Mountain Standard Effect");
	mWaterEffect.DebugUI("Water Effect", mWaterRenderObject);
	mReflectionEffect.DebugUI("Reflection Effect", mReflectionRenderObject);

	ImGui::End();
}

void GameState::CameraControl(float deltaTime)
{
	InputSystem* inputSystem = InputSystem::Get();

	const float moveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}