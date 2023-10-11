#include "GameState.h"

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 3.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mInputSystem = InputSystem::Get();
}

void GameState::Terminate()
{
}

void GameState::Update(float deltaTime)
{
	CameraControl(deltaTime);

	if (mInputSystem->IsKeyDown(KeyCode::ONE))
	{
		mCurrentDebug = DebugType::Box;
	}
	if (mInputSystem->IsKeyDown(KeyCode::TWO))
	{
		mCurrentDebug = DebugType::FilledBox;
	}
	if (mInputSystem->IsKeyDown(KeyCode::THREE))
	{
		mCurrentDebug = DebugType::Sphere;
	}
	if (mInputSystem->IsKeyDown(KeyCode::FOUR))
	{
		mCurrentDebug = DebugType::Plane;
	}
	if (mInputSystem->IsKeyDown(KeyCode::FIVE))
	{
		mCurrentDebug = DebugType::Transform;
	}
}

void GameState::Render()
{
	switch (mCurrentDebug)
	{
	case DebugType::Box:
		SimpleDraw::AddAABB( mPosition1, mPosition2, mColor);
		break;
	case DebugType::FilledBox:
		SimpleDraw::AddFilledAABB(mPosition1, mPosition2, mColor);
		break;
	case DebugType::Sphere:
		SimpleDraw::AddSphere(20, 20, 1.0f, mColor);
		break;
	case DebugType::Plane:
		//SimpleDraw::AddPlane(20.0f, mColor);
		break;
	case DebugType::Transform:
		SimpleDraw::AddTransform(Matrix4::Identity);
		break;
	default:
		break;
	}

	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::DragFloat3("Position1", &mPosition1.x, 0.01f);
	ImGui::DragFloat3("Position2", &mPosition2.x, 0.01f);
	ImGui::ColorEdit4("Color", &mColor.r);
	ImGui::End();
}

void GameState::CameraControl(float deltaTime)
{
	const float moveSpeed = mInputSystem->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (mInputSystem->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	if (mInputSystem->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (mInputSystem->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	if (mInputSystem->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (mInputSystem->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	if (mInputSystem->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (mInputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(mInputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(mInputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}