#include "GameState.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Input;
using namespace PenguinEngine::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 5.0f, -15.0f });
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

	Model duckModel;
	ModelIO::LoadModel("../../Assets/Models/Duck/duck.model", duckModel);
	ModelIO::LoadMaterial("../../Assets/Models/Duck/duck.model", duckModel);
	mBallRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mBallRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mBallRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mBallRenderObject.material.power = 10.0f;
	mBallRenderObject.diffuseMapId = tm->LoadTexture(L"Models/Duck/Duck.png");
	mBallRenderObject.meshBuffer.Initialize(duckModel.meshData[0].mesh);
	//mBallRenderObject.diffuseMapId = tm->LoadTexture(L"Images/basketball.jpg");
	//mBallRenderObject.meshBuffer.Initialize(MeshBuilder::CreateSphere(250, 250, 1.0f));

	mGroundRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGroundRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGroundRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mGroundRenderObject.material.power = 10.0f;
	mGroundRenderObject.diffuseMapId = tm->LoadTexture(L"Images/misc/concrete.jpg");
	mGroundRenderObject.meshBuffer.Initialize(MeshBuilder::CreatePlane(50, 50, 1.0f));

	mBallAnimation = AnimationBuilder()
		.AddPositionKey(Math::Vector3(0.0f), 0.0f)
		.AddPositionKey(Math::Vector3(10.0f, 0.0f, 0.0f), 3.0f)
		.AddPositionKey(Math::Vector3(5.0f, 5.0f, 0.0f), 5.0f)
		.AddPositionKey(Math::Vector3(0.0f), 8.0f)
		.AddRotationKey(Math::Quaternion::Identity, 0.0f)
		.AddRotationKey(Math::Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, -Math::Constants::Pi), 3.0f)
		.AddRotationKey(Math::Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, -Math::Constants::Pi * 1.5f), 5.0f)
		.AddRotationKey(Math::Quaternion::CreateFromAxisAngle(Math::Vector3::XAxis, -Math::Constants::TwoPi), 8.0f)
		.AddScaleKey(Math::Vector3(1.0f), 0.0f)
		.AddScaleKey(Math::Vector3(0.5f), 3.0f)
		.AddScaleKey(Math::Vector3(1.5f), 5.0f)
		.AddScaleKey(Math::Vector3(1.0f), 8.0f)
		.Build();
}

void GameState::Terminate()
{
	mGroundRenderObject.Terminate();
	mBallRenderObject.Terminate();

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

	const float dt = mPause ? 0.0f : deltaTime;
	mRunningTime += dt;

	float height = mBallHeight * abs(cos(mRunningTime * 2.0f)) + 1.0f;
	const float animDuration = mBallAnimation.GetDuration();
	mAnimationTime += deltaTime;
	while (mAnimationTime > animDuration)
	{
		mAnimationTime -= animDuration;
	}
	mBallRenderObject.transform = mBallAnimation.GetTransform(mAnimationTime);
}

void GameState::Render()
{
	mShadowEffect.Begin();
	mShadowEffect.Render(mBallRenderObject);
	mShadowEffect.End();

	mStandardEffect.Begin();
	mStandardEffect.Render(mBallRenderObject);
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

	if (ImGui::CollapsingHeader("Ball", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Ambient##Earth", &mBallRenderObject.material.ambient.r);
		ImGui::ColorEdit4("Diffuse##Earth", &mBallRenderObject.material.diffuse.r);
		ImGui::ColorEdit4("Specular##Earth", &mBallRenderObject.material.specular.r);
		ImGui::DragFloat("Power##Earth", &mBallRenderObject.material.power, 1.0f, 1.0f, 100.0f);
	}

	mStandardEffect.DebugUI();
	mShadowEffect.DebugUI();

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