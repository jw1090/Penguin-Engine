#include "GameState.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Input;
using namespace PenguinEngine::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 2.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(mDirectionalLight);

	auto tm = TextureManager::Get();

	Model characterModel;
	ModelIO::LoadModel("../../Assets/Models/character.model", characterModel);
	ModelIO::LoadMaterial("../../Assets/Models/character.model", characterModel);
	ModelIO::LoadSkeleton("../../Assets/Models/character.model", characterModel);

	mCharacter = CreateRenderGroup(characterModel);

	mGroundRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGroundRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGroundRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGroundRenderObject.material.power = 10.0f;
	mGroundRenderObject.diffuseMapId = tm->LoadTexture(L"Images/misc/concrete.jpg");
	mGroundRenderObject.meshBuffer.Initialize(MeshBuilder::CreatePlane(50, 50, 1.0f));
}

void GameState::Terminate()
{
	CleanUpRenderGroup(mCharacter);
	mGroundRenderObject.Terminate();

	mShadowEffect.Terminate();
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
}

void GameState::Render()
{
	mShadowEffect.Begin();
		DrawRenderGroup(mShadowEffect, mCharacter);
	mShadowEffect.End();

	mStandardEffect.Begin();
		DrawRenderGroup(mStandardEffect, mCharacter);
		mStandardEffect.Render(mGroundRenderObject);
	mStandardEffect.End();

	SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::Render(mCamera);
}


void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("fps: %f %s", mFPS, mPause ? "(paused)" : "");
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f))
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}

	mStandardEffect.DebugUI();
	mShadowEffect.DebugUI();

	// button to draw skeleton/mesh

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