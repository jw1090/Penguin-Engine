#include "CubeState.h"

void CubeState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	// NDC - Normalized Device Coordinate
	//
	//          +-----------------+
	//         /                 /|
	//   1.0  +-----------------+ |
	//	      |        ^        | |
	//	      |        |        | |
	//	      | <------+------> | |
	//	      |        |        | | 1.0
	//	      |        v        |/
	//	-1.0  +-----------------+ 0.0
	//      -1.0               1.0


	mCubeMesh = MeshBuilder::CreateCubePC(1.0f);
	mMeshBuffer.Initialize(mCubeMesh);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoTransform.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");

	mConstantBuffer.Initialize(sizeof(Matrix4));
}

void CubeState::Terminate()
{
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void CubeState::Update(float deltaTime)
{
	auto inputSystem = Input::InputSystem::Get();
	if (inputSystem->IsKeyPressed(Input::KeyCode::TWO))
	{
		MainApp().ChangeState("PlaneState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::THREE))
	{
		MainApp().ChangeState("CylinderState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::FOUR))
	{
		MainApp().ChangeState("SphereState");
	}
}

void CubeState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

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