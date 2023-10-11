#include "CylinderState.h"

void CylinderState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 3.0f, -5.0f });
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

	mCylinderMesh = MeshBuilder::CreateCylinderPC(9, 5);
	mMeshBuffer.Initialize(mCylinderMesh);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoTransform.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");

	mConstantBuffer.Initialize(sizeof(Matrix4));
}

void CylinderState::Terminate()
{
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void CylinderState::Update(float deltaTime)
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
	if (inputSystem->IsKeyPressed(Input::KeyCode::FOUR))
	{
		MainApp().ChangeState("SphereState");
	}
}

void CylinderState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	static float rotationX = 0.0f;
	static float rotationY = 0.0f;
	rotationX -= 0.01f;
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

void CylinderState::DebugUI()
{

}