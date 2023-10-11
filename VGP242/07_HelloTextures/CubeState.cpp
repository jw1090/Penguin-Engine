#include "CubeState.h"

void CubeState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mCubeMesh = MeshBuilder::CreateCubePX(1.0f);
	mMeshBuffer.Initialize(mCubeMesh);

	mVertexShader.Initialize<VertexPX>(L"../../Assets/Shaders/DoTexturing.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");

	mDiffuseMap.Initialize(L"../../Assets/Images/space.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	mConstantBuffer.Initialize(sizeof(Matrix4));
}

void CubeState::Terminate()
{
	mConstantBuffer.Terminate();
	mSampler.Terminate();
	mDiffuseMap.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void CubeState::Update(float deltaTime)
{
	auto inputSystem = Input::InputSystem::Get();
	if (inputSystem->IsKeyPressed(Input::KeyCode::TWO))
	{
		MainApp().ChangeState("SkyBoxState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::THREE))
	{
		MainApp().ChangeState("SphereState");
	}
}

void CubeState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mDiffuseMap.BindVS(0);
	mDiffuseMap.BindPS(0);
	mSampler.BindVS(0);
	mSampler.BindPS(0);

	static float rotationX = 0.0f;
	static float rotationY = 0.0f;
	rotationX -= 0.03f;
	rotationY -= 0.01f;

	Matrix4 world;
	world = Matrix4::RotationX(rotationX) * Matrix4::RotationY(rotationY);

	Matrix4 view = mCamera.GetViewMatrix();
	Matrix4 proj = mCamera.GetProjectionMatrix();
	Matrix4 wvp = Transpose(world * view * proj); // HLSL requires matrices to be column-major

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}

void CubeState::DebugUI()
{

}