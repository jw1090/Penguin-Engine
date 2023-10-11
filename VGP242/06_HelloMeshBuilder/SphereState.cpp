#include "SphereState.h"

void SphereState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 3.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	int slices = 100;
	int rings = 100;
	float radius = 1.0f;

	if (isColored)
	{
		mSphereMesh = MeshBuilder::CreateSpherePC(slices, rings, radius);
	}
	else
	{
		mSphereMesh = MeshBuilder::CreateSpherePC(slices, rings, radius, Colors::Orange);
	}

	mMeshBuffer.Initialize(mSphereMesh);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoTransform.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");

	mConstantBuffer.Initialize(sizeof(Matrix4));
}

void SphereState::Terminate()
{
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
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
		MainApp().ChangeState("PlaneState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::THREE))
	{
		MainApp().ChangeState("CylinderState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::C))
	{
		isColored = !isColored;
		Terminate();
		Initialize();
	}
}

void SphereState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	static float rotationX = 0.0f;
	static float rotationY = 0.0f;
	rotationX -= 0.00f;
	rotationY -= 0.03f;

	Matrix4 world;
	world = Matrix4::RotationX(rotationX) * Matrix4::RotationY(rotationY);

	Matrix4 view = mCamera.GetViewMatrix();
	Matrix4 proj = mCamera.GetProjectionMatrix();
	Matrix4 wvp = Transpose(world * view * proj); // HLSL requires matrices to be column-major

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}

void SphereState::DebugUI()
{

}