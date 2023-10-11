#include "GameState.h"

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -2.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mInputSystem = InputSystem::Get();

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mStandardEffect.SetBumpWeight(0.35f);

	mMesh = MeshBuilder::CreateSphere(1024, 512, 1.0f);

	auto tm = TextureManager::Get();
	mEarthRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mEarthRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mEarthRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mEarthRenderObject.material.power = 10.0f;
	mEarthRenderObject.diffuseMapId = tm->LoadTexture(L"Images/earth.jpg");
	mEarthRenderObject.specularMapId = tm->LoadTexture(L"Images/earth_spec.jpg");
	mEarthRenderObject.bumpMapId = tm->LoadTexture(L"Images/earth_bump.jpg");
	mEarthRenderObject.normalMapId = tm->LoadTexture(L"Images/earth_normal.jpg");
	mEarthRenderObject.meshBuffer.Initialize(mMesh);
}

void GameState::Terminate()
{
	mEarthRenderObject.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	CameraControl(deltaTime);

	if (mAutoRotate)
	{
		mRotation.y += mRotationAmount;
	}

	mFPS = 1.0f / deltaTime;
}

void GameState::Render()
{
	mStandardEffect.Begin();

	mStandardEffect.Render(mEarthRenderObject);

	ShowNormals();

	SimpleDraw::AddPlane(10.0f, Colors::White);
	SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::Render(mCamera);

	mStandardEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("fps: %f", mFPS);
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

	if (ImGui::CollapsingHeader("Earth", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Ambient##Earth", &mEarthRenderObject.material.ambient.r);
		ImGui::ColorEdit4("Diffuse##Earth", &mEarthRenderObject.material.diffuse.r);
		ImGui::ColorEdit4("Specular##Earth", &mEarthRenderObject.material.specular.r);
		ImGui::DragFloat("Power##Earth", &mEarthRenderObject.material.power, 1.0f, 1.0f, 100.0f);

		ImGui::DragFloat3("Position", &mPosition.x, 0.01f);
		ImGui::DragFloat3("Rotation", &mRotation.x, 0.01f);
	}

	ImGui::Separator();
	ImGui::DragFloat("Rotation Amount", &mRotationAmount, 0.001f, 0.0f, 0.2f);
	ImGui::Checkbox("Auto Rotate", &mAutoRotate);

	mStandardEffect.DebugUI();

	ImGui::Separator();
	ImGui::Checkbox("Draw Normals", &mShowNormals);

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

void GameState::ShowNormals()
{
	if (mShowNormals)
	{
		for (const auto& v : mMesh.vertices)
		{
			SimpleDraw::AddLine(v.position, v.position + v.normal, Colors::Cyan);
		}
	}
}