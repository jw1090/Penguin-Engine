#include "SphereState.h"

void SphereState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mSphereMesh = MeshBuilder::CreateSpherePX(10, 10, 1.0f);
	mSphereMeshBuffer.Initialize(mSphereMesh);

	mVertexShader.Initialize<VertexPX>(L"../../Assets/Shaders/DoTexturing.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");

	mEarthTexture.Initialize(L"../../Assets/Images/planets/earth/earth.jpg");
	mSunTexture.Initialize(L"../../Assets/Images/planets/sun.jpg");

	mConstantBuffer.Initialize(sizeof(Matrix4));

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

}

void SphereState::Terminate()
{
	mConstantBuffer.Terminate();
	mSampler.Terminate();
	mSunTexture.Terminate();
	mEarthTexture.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mSphereMeshBuffer.Terminate();
}

void SphereState::Update(float deltaTime)
{
	auto inputSystem = Input::InputSystem::Get();
	if (inputSystem->IsKeyPressed(Input::KeyCode::ONE))
	{
		MainApp().ChangeState("CubeState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::TWO))
	{
		MainApp().ChangeState("SkyBoxState");
	}

	mRotation1 += 0.005f;
	mRotation2 += 0.001f;
}

void SphereState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mConstantBuffer.BindVS(0);

	Matrix4 view = mCamera.GetViewMatrix();
	Matrix4 proj = mCamera.GetProjectionMatrix();

	Matrix4 planetWorldMatrix =
	{
		Matrix4::Scaling(1.0f) *
		Matrix4::RotationY(mRotation1)
	};
	Matrix4 planetWVP = Transpose(planetWorldMatrix * view * proj);

	mConstantBuffer.Update(&planetWVP);
	mEarthTexture.BindPS(0);
	mSphereMeshBuffer.Render();

	Matrix4 testPlanetWorldMatrix =
	{
		Matrix4::Scaling(10.0f) *
		Matrix4::RotationY(mRotation2)
	};
	Matrix4 testPlanetWVP = Transpose(testPlanetWorldMatrix * view * proj);

	mConstantBuffer.Update(&testPlanetWVP);
	mSunTexture.BindPS(0);
	mSphereMeshBuffer.Render();
}

void SphereState::DebugUI()
{

}