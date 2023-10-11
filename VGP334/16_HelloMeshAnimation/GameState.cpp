#include "GameState.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Input;
using namespace PenguinEngine::Math;
using namespace PenguinEngine::Graphics::AnimationUtil;

enum class AnimationState : int
{
	TPos,
	Pose,
	Idle,		// 0
	Walk_F,		// 1
	Walk_L,		// 2
	Walk_R,		// 3
	Walk_B		// 4
};

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 3.0f, -5.0f });
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
	auto mm = ModelManager::Get();

	mJolleenModelID = mm->LoadModel("../../Assets/Models/Jolleen/Ch34_nonPBR.model");
	mm->AddAnimation(mJolleenModelID, "../../Assets/Models/Jolleen/standing_idle_01.model");
	mm->AddAnimation(mJolleenModelID, "../../Assets/Models/Jolleen/standing_run_forward.model");
	mm->AddAnimation(mJolleenModelID, "../../Assets/Models/Jolleen/standing_run_left.model");
	mm->AddAnimation(mJolleenModelID, "../../Assets/Models/Jolleen/standing_run_right.model");
	mm->AddAnimation(mJolleenModelID, "../../Assets/Models/Jolleen/standing_run_back.model");
	mJolleen = CreateRenderGroup(mJolleenModelID, &mJolleenAnimator);
	mJolleenAnimator.Initialize(mJolleenModelID);
	mJolleenAnimator.PlayAnimation((int)AnimationState::Idle, true);

	mGroundRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGroundRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGroundRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGroundRenderObject.material.power = 10.0f;
	mGroundRenderObject.diffuseMapId = tm->LoadTexture(L"Images/misc/concrete.jpg");
	mGroundRenderObject.meshBuffer.Initialize(MeshBuilder::CreatePlane(50, 50, 1.0f));
}

void GameState::Terminate()
{
	CleanUpRenderGroup(mJolleen);
	mGroundRenderObject.Terminate();

	mShadowEffect.Terminate();
	mStandardEffect.Terminate();
}

int animationIndex = 0;
void GameState::Update(float deltaTime)
{
	CameraControl(deltaTime);
	mJolleenAnimator.Update(deltaTime);

	mFPS = 1.0f / deltaTime;

	InputSystem* inputSystem = InputSystem::Get();

	if (inputSystem->IsKeyPressed(KeyCode::SPACE))
	{
		mPause = !mPause;
	}

	if (inputSystem->IsKeyPressed(KeyCode::UP))
	{
		mJolleenAnimator.PlayAnimation((int)AnimationState::Walk_F, true, 2.0f);
	}
	else if (inputSystem->IsKeyPressed(KeyCode::DOWN))
	{
		mJolleenAnimator.PlayAnimation((int)AnimationState::Walk_B, true, 2.0f);
	}
	else if (inputSystem->IsKeyPressed(KeyCode::LEFT))
	{
		mJolleenAnimator.PlayAnimation((int)AnimationState::Walk_L, true, 2.0f);
	}
	else if (inputSystem->IsKeyPressed(KeyCode::RIGHT))
	{
		mJolleenAnimator.PlayAnimation((int)AnimationState::Walk_R, true, 2.0f);
	}
	else if (inputSystem->IsKeyPressed(KeyCode::ENTER))
	{
		mJolleenAnimator.PlayAnimation((int)AnimationState::Idle, true, 2.0f);
	}
}

void GameState::Render()
{
	mShadowEffect.Begin();
		DrawRenderGroup(mShadowEffect, mJolleen);
	mShadowEffect.End();

	mStandardEffect.Begin();
		if (mDrawSkeleton)
		{
			BoneTransforms boneTransforms;
			AnimationUtil::ComputeBoneTransform(mJolleenModelID, boneTransforms, &mJolleenAnimator);
			AnimationUtil::DrawSkeleton(mJolleenModelID, boneTransforms);
		}
		else
		{
			DrawRenderGroup(mStandardEffect, mJolleen);
		}
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
	
	if (ImGui::Checkbox("Show Skeleton", &mDrawSkeleton))
	{

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