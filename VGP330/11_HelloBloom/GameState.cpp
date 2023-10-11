#include "GameState.h"

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -15.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.0f, 0.0f, 0.0f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

	mStandardEffect.Initialize();
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mStandardEffect.SetBumpWeight(0.35f);

	mGaussianBlurEffect.Initialize();
	mGaussianBlurEffect.SetSourceTexture(mBloomRenderTarget);
	mGaussianBlurEffect.BlurIterations() = 10;
	mGaussianBlurEffect.BlurSaturation() = 1.0f;

	mPostProcessingEffect.Initialize();
	mPostProcessingEffect.SetMode(PostProcessingEffect::Mode::None);
	mPostProcessingEffect.SetTexture(&mBaseRenderTarget, 0);
	mPostProcessingEffect.SetTexture(&mGaussianBlurEffect.GetResultTexture(), 1);

	auto gs = GraphicsSystem::Get();
	const auto screenWidth = gs->GetBackBufferWidth();
	const auto screenHeight = gs->GetBackBufferHeight();
	mBaseRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
	mBloomRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

	auto tm = TextureManager::Get();

	mSunRenderObject.material.emissive = Colors::White;
	mSunRenderObject.material.power = 1.0f;
	mSunRenderObject.diffuseMapId = tm->LoadTexture(L"Images/planets/sun.jpg");
	mSunRenderObject.meshBuffer.Initialize(MeshBuilder::CreateSphere(1024, 512, 5.0f));

	mEarthRenderObject.material.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mEarthRenderObject.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mEarthRenderObject.material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	mEarthRenderObject.material.power = 10.0f;
	mEarthRenderObject.diffuseMapId = tm->LoadTexture(L"Images/planets/earth/earth.jpg");
	mEarthRenderObject.specularMapId = tm->LoadTexture(L"Images/planets/earth/earth_spec.jpg");
	mEarthRenderObject.bumpMapId = tm->LoadTexture(L"Images/planets/earth/earth_bump.jpg");
	mEarthRenderObject.normalMapId = tm->LoadTexture(L"Images/planets/earth/earth_normal.jpg");
	mEarthRenderObject.meshBuffer.Initialize(MeshBuilder::CreateSphere(1024, 512, 1.0f));

	mScreenQuad.meshBuffer.Initialize(MeshBuilder::CreateScreenQuad());
}

void GameState::Terminate()
{
	mScreenQuad.Terminate();
	mEarthRenderObject.Terminate();
	mSunRenderObject.Terminate();

	mBloomRenderTarget.Terminate();
	mBaseRenderTarget.Terminate();

	mPostProcessingEffect.Terminate();
	mGaussianBlurEffect.Terminate();
	mStandardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	CameraControl(deltaTime);

	mFPS = 1.0f / deltaTime;

	Vector3 earthPosition = { 0.0f, 0.0f, -mEarthOffset };
	mEarthRenderObject.transform.position = TransformCoord(earthPosition, Matrix4::RotationY(mEarthRevolution));
	mEarthRenderObject.transform.rotation.y = mEarthRotation;
}

void GameState::Render()
{
	mBaseRenderTarget.BeginRender();
	{
		mStandardEffect.Begin();
		mStandardEffect.Render(mSunRenderObject);
		mStandardEffect.Render(mEarthRenderObject);
		mStandardEffect.End();

		SimpleDraw::AddGroundPlane(20.0f, Colors::White);
		SimpleDraw::AddTransform(Matrix4::Identity);
		SimpleDraw::Render(mCamera);
	}
	mBaseRenderTarget.EndRender();

	mBloomRenderTarget.BeginRender();
	{
		// Swap in blank material
		Material dummyMaterial;
		dummyMaterial.power = 1.0f;
		std::swap(mEarthRenderObject.material, dummyMaterial);

		mStandardEffect.Begin();
		mStandardEffect.Render(mSunRenderObject);
		mStandardEffect.Render(mEarthRenderObject);
		mStandardEffect.End();

		// Restore original material
		std::swap(mEarthRenderObject.material, dummyMaterial);
	}
	mBloomRenderTarget.EndRender();

	mGaussianBlurEffect.Begin();
	mGaussianBlurEffect.Render(mScreenQuad);
	mGaussianBlurEffect.End();

	mPostProcessingEffect.Begin();
	mPostProcessingEffect.Render(mScreenQuad);
	mPostProcessingEffect.End();
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

		ImGui::DragFloat("Offset##Earth", &mEarthOffset, 0.01f);
		ImGui::DragFloat("Rotation##Earth", &mEarthRotation, 0.01f);
		ImGui::DragFloat("Revolution##Earth", &mEarthRevolution, 0.01f);
	}

	mStandardEffect.DebugUI();
	mPostProcessingEffect.DebugUI();

	if (ImGui::CollapsingHeader("Blur", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragInt("Blur Iterations", &mGaussianBlurEffect.BlurIterations(), 1, 1, 100);
		ImGui::DragFloat("Blur Saturation", &mGaussianBlurEffect.BlurSaturation(), 0.001f, 1.0f, 100.0f);
	}

	ImGui::End();

	ImGui::Begin("Render Targets", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Text("Base");
	ImGui::Image(mBaseRenderTarget.GetRawData(), { 256, 144 });
	ImGui::Text("Bloom");
	ImGui::Image(mBloomRenderTarget.GetRawData(), { 256, 144 });
	ImGui::Text("Horizontal Blur");
	ImGui::Image(mGaussianBlurEffect.GetHorizontalBlurTexture().GetRawData(), { 256, 144 });
	ImGui::Text("Vertical Blur");
	ImGui::Image(mGaussianBlurEffect.GetVerticalBlurTexture().GetRawData(), { 256, 144 });
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