#include "TriforceState.h"

void TriforceState::Initialize()
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
	//

#pragma region Triangles

	mVertices.push_back({ Vector3{  0.0f,  0.5f, 0.0f }, Graphics::Colors::Gold });
	mVertices.push_back({ Vector3{  0.1f, 0.25f, 0.0f }, Graphics::Colors::Gold });
	mVertices.push_back({ Vector3{ -0.1f, 0.25f, 0.0f }, Graphics::Colors::Gold });

	mVertices.push_back({ Vector3{ -0.1f, 0.25f, 0.0f }, Graphics::Colors::Gold });
	mVertices.push_back({ Vector3{  0.0f,  0.0f, 0.0f }, Graphics::Colors::Gold });
	mVertices.push_back({ Vector3{ -0.2f,  0.0f, 0.0f }, Graphics::Colors::Gold });

	mVertices.push_back({ Vector3{ 0.1f, 0.25f, 0.0f }, Graphics::Colors::Gold });
	mVertices.push_back({ Vector3{ 0.2f,  0.0f, 0.0f }, Graphics::Colors::Gold });
	mVertices.push_back({ Vector3{  0.0f, 0.0f, 0.0f }, Graphics::Colors::Gold });

#pragma endregion

	mMeshBuffer.Initialize(mVertices);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoSomething.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoSomething.fx");
}

void TriforceState::Terminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void TriforceState::Update(float deltaTime)
{
	auto inputSystem = Input::InputSystem::Get();
	if (inputSystem->IsKeyPressed(Input::KeyCode::ONE))
	{
		MainApp().ChangeState("TriangleState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::TWO))
	{
		MainApp().ChangeState("HeartState");
	}
	if (inputSystem->IsKeyPressed(Input::KeyCode::FOUR))
	{
		MainApp().ChangeState("FoxState");
	}

}

void TriforceState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mMeshBuffer.Render();
}

void TriforceState::DebugUI()
{

}