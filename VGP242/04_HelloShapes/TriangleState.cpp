#include "TriangleState.h"

void TriangleState::Initialize()
{
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
	
	mVertices.push_back({ Vector3{  0.0f,  0.5f, 0.0f }, Graphics::Colors::White });
	mVertices.push_back({ Vector3{  0.5f, -0.5f, 0.0f }, Graphics::Colors::White });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, 0.0f }, Graphics::Colors::White });

	mMeshBuffer.Initialize(mVertices);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoSomething.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoSomething.fx");
}

void TriangleState::Terminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void TriangleState::Update(float deltaTime)
{
	auto inputSystem = Input::InputSystem::Get();
	if (inputSystem->IsKeyPressed(Input::KeyCode::TWO))
	{
		MainApp().ChangeState("HeartState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::THREE))
	{
		MainApp().ChangeState("TriforceState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::FOUR))
	{
		MainApp().ChangeState("FoxState");
	}
}

void TriangleState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mMeshBuffer.Render();
}

void TriangleState::DebugUI()
{

}