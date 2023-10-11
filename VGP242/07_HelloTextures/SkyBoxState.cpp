#include "SkyBoxState.h"

void SkyBoxState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mSkyBoxMesh = MeshBuilder::CreateSkyBox(1000.0f);
	mMeshBuffer.Initialize(mSkyBoxMesh);

	mVertexShader.Initialize<VertexPX>(L"../../Assets/Shaders/DoTexturing.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");

	mDiffuseMap.Initialize(L"../../Assets/Images/skybox_texture.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	mConstantBuffer.Initialize(sizeof(Matrix4));
}

void SkyBoxState::Terminate()
{
	mConstantBuffer.Terminate();
	mSampler.Terminate();
	mDiffuseMap.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void SkyBoxState::Update(float deltaTime)
{
	auto inputSystem = Input::InputSystem::Get();
	if (inputSystem->IsKeyPressed(Input::KeyCode::ONE))
	{
		MainApp().ChangeState("CubeState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::THREE))
	{
		MainApp().ChangeState("SphereState");
	}
}

void SkyBoxState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mDiffuseMap.BindVS(0);
	mDiffuseMap.BindPS(0);
	mSampler.BindVS(0);
	mSampler.BindPS(0);

	static float rotationX = 0.0f;
	static float rotationY = 0.0f;
	rotationX -= 0.00f;
	rotationY -= 0.0001f;

	Matrix4 world;
	world = Matrix4::RotationX(rotationX) * Matrix4::RotationY(rotationY);

	Matrix4 view = mCamera.GetViewMatrix();
	Matrix4 proj = mCamera.GetProjectionMatrix();
	Matrix4 wvp = Transpose(world * view * proj); // HLSL requires matrices to be column-major

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}

void SkyBoxState::DebugUI()
{

}