#include "SpaceScene.h"

void SpaceScene::Initialize()
{
	mCamera.SetPosition({ 0.0f, 5.0f, -15.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mSkyBoxMesh = MeshBuilder::CreateSkySphere(100, 100, 1.0f);
	mSkyBoxMeshBuffer.Initialize(mSkyBoxMesh);

	mPlanetMesh = MeshBuilder::CreateSpherePX(100, 100, 1.0f);
	mPlanetMeshBuffer.Initialize(mPlanetMesh);

	mVertexShader.Initialize<VertexPX>(L"../../Assets/Shaders/DoTexturing.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");

	mConstantBuffer.Initialize(sizeof(Matrix4));

	InitializePlanets();

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void SpaceScene::Terminate()
{
	mSampler.Terminate();

	for (auto& planet : planets)
	{
		planet.TerminateTexture();
	}

	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();

	mPlanetMeshBuffer.Terminate();
	mSkyBoxMeshBuffer.Terminate();
}

void SpaceScene::Update(float deltaTime)
{
	for (auto& planet : planets)
	{
		planet.Update(deltaTime);
	}

	CameraControl(deltaTime);
}

void SpaceScene::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mConstantBuffer.BindVS(0);

	RenderPlanets();
}

void SpaceScene::DebugUI()
{

}

void SpaceScene::InitializePlanets()
{
	PlanetInfo SkyBox(mSkyboxTexture.get(), Vector3::Zero, 25.0f, -0.01f, 0);
	SkyBox.InitializeTexture(L"../../Assets/Images/misc/space.jpg");
	SkyBox.SetMeshBuffer(mSkyBoxMeshBuffer);
	planets.push_back(SkyBox);

	PlanetInfo Sun(mSunTexture.get(), Vector3::Zero, 0.45f, 0.15f, 0);
	Sun.InitializeTexture(L"../../Assets/Images/planets/sun.jpg");
	Sun.SetMeshBuffer(mPlanetMeshBuffer);
	planets.push_back(Sun);

	PlanetInfo Mercury(mMercuryTexture.get(), { 0.8f, 0, 0 }, 0.09f, 0.5f, 0.55f);
	Mercury.InitializeTexture(L"../../Assets/Images/planets/mercury.jpg");
	Mercury.SetMeshBuffer(mPlanetMeshBuffer);
	planets.push_back(Mercury);

	PlanetInfo Venus(mVenusTexture.get(), { 1.2f, 0, 0 }, 0.13f, 0.5f, 0.4f);
	Venus.InitializeTexture(L"../../Assets/Images/planets/venus.jpg");
	Venus.SetMeshBuffer(mPlanetMeshBuffer);
	planets.push_back(Venus);

	PlanetInfo Earth(mEarthTexture.get(), { 2.0f, 0, 0 }, 0.15f, 0.5f, 0.3f);
	Earth.InitializeTexture(L"../../Assets/Images/planets/earth/earth.jpg");
	Earth.SetMeshBuffer(mPlanetMeshBuffer);
	planets.push_back(Earth);
	
	PlanetInfo Mars(mMarsTexture.get(), { 3.0f, 0, 0 }, 0.10f, 0.5f, 0.25f);
	Mars.InitializeTexture(L"../../Assets/Images/planets/mars.jpg");
	Mars.SetMeshBuffer(mPlanetMeshBuffer);
	planets.push_back(Mars);

	PlanetInfo Jupiter(mJupiterTexture.get(), { 5.0f, 0, 0 }, 0.38f, 0.5f, 0.2f);
	Jupiter.InitializeTexture(L"../../Assets/Images/planets/jupiter.jpg");
	Jupiter.SetMeshBuffer(mPlanetMeshBuffer);
	planets.push_back(Jupiter);

	PlanetInfo Saturn(mSaturnTexture.get(), { 6.5f, 0, 0 }, 0.3f, 0.5f, 0.15f);
	Saturn.InitializeTexture(L"../../Assets/Images/planets/saturn.jpg");
	Saturn.SetMeshBuffer(mPlanetMeshBuffer);
	planets.push_back(Saturn);

	PlanetInfo Uranus(mUranusTexture.get(), { 9.0f, 0, 0 }, 0.25f, 0.5f, 0.08f);
	Uranus.InitializeTexture(L"../../Assets/Images/planets/uranus.jpg");
	Uranus.SetMeshBuffer(mPlanetMeshBuffer);
	planets.push_back(Uranus);

	PlanetInfo Neptune(mNeptuneTexture.get(), { 11.0f, 0, 0 }, 0.22f, 0.5f, 0.05f);
	Neptune.InitializeTexture(L"../../Assets/Images/planets/neptune.jpg");
	Neptune.SetMeshBuffer(mPlanetMeshBuffer);
	planets.push_back(Neptune);

	PlanetInfo Pluto(mPlutoTexture.get(), { 13.5f, 0, 0 }, 0.1f, 0.5f, 0.03f);
	Pluto.InitializeTexture(L"../../Assets/Images/planets/pluto.jpg");
	Pluto.SetMeshBuffer(mPlanetMeshBuffer);
	planets.push_back(Pluto);
}

void SpaceScene::RenderPlanets()
{
	Matrix4 view = mCamera.GetViewMatrix();
	Matrix4 proj = mCamera.GetProjectionMatrix();

	for (auto& planet : planets)
	{
		Matrix4 planetWorldMatrix =
		{
			Matrix4::Scaling(planet.GetScale()) *
			Matrix4::RotationY(planet.GetRotation()) *
			Matrix4::Translation(planet.GetDistanceFromCenter()) *
			Matrix4::RotationY(planet.GetRevolution())
		};
		Matrix4 planetWVP = Transpose(planetWorldMatrix * view * proj);

		mConstantBuffer.Update(&planetWVP);
		planet.BindPS(0);
		planet.Render();
	}
}

void SpaceScene::CameraControl(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

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
	if (inputSystem->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}