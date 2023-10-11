#include "PlaneState.h"

void PlaneState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 5.0f, -5.0f });
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

	int columns = 4;
	int rows = 3;
	float size = 1.0f;

	if (isColored)
	{
		mPlaneMesh = MeshBuilder::CreatePlanePC(columns, rows, size);
	}
	else
	{
		mPlaneMesh = MeshBuilder::CreatePlanePC(columns, rows, size, Colors::White);
	}
	
	mMeshBuffer.Initialize(mPlaneMesh);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoTransform.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");

	mConstantBuffer.Initialize(sizeof(Matrix4));
}

void PlaneState::Terminate()
{
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void PlaneState::Update(float deltaTime)
{
	auto inputSystem = Input::InputSystem::Get();
	if (inputSystem->IsKeyPressed(Input::KeyCode::ONE))
	{
		MainApp().ChangeState("CubeState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::THREE))
	{
		MainApp().ChangeState("CylinderState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::FOUR))
	{
		MainApp().ChangeState("SphereState");
	}

	if (inputSystem->IsKeyPressed(Input::KeyCode::C))
	{
		isColored = !isColored;
		Terminate();
		Initialize();
	}
}

void PlaneState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	static float rotationX = 0.0f;
	static float rotationY = 0.0f;
	rotationX -= 0.00f;
	rotationY -= 0.00f;

	Matrix4 world;
	world = Matrix4::RotationX(rotationX) * Matrix4::RotationY(rotationY);

	Matrix4 view = mCamera.GetViewMatrix();
	Matrix4 proj = mCamera.GetProjectionMatrix();
	Matrix4 wvp = Transpose(world * view * proj); // HLSL requires matrices to be column-major

	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();
}

void PlaneState::DebugUI()
{

}