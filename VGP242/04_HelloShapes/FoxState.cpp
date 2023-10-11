#include "FoxState.h"

void FoxState::Initialize()
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

	// Front
	mVertices.push_back({ Vector3{ -0.05f,  0.1f, 0.0f }, Graphics::Colors::SaddleBrown });
	mVertices.push_back({ Vector3{  0.05f,  0.1f, 0.0f }, Graphics::Colors::SaddleBrown });
	mVertices.push_back({ Vector3{  0.0f,   0.0f, 0.0f }, Graphics::Colors::SaddleBrown });

	mVertices.push_back({ Vector3{ -0.10f,  0.2f, 0.0f }, Graphics::Colors::LightSalmon });
	mVertices.push_back({ Vector3{  0.10f,  0.2f, 0.0f }, Graphics::Colors::LightSalmon });
	mVertices.push_back({ Vector3{  0.0f,   0.0f, 0.0f }, Graphics::Colors::LightSalmon });

	mVertices.push_back({ Vector3{ -0.25f,  0.5f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.25f,  0.5f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.0f,   0.0f, 0.0f }, Graphics::Colors::DarkRed });

	// Sides
	mVertices.push_back({ Vector3{  0.25f,  0.5f, 0.0f }, Graphics::Colors::DarkOrange });
	mVertices.push_back({ Vector3{  0.32f, 0.22f, 0.0f }, Graphics::Colors::DarkOrange });
	mVertices.push_back({ Vector3{  0.10f,  0.2f, 0.0f }, Graphics::Colors::DarkOrange });

	mVertices.push_back({ Vector3{ -0.25f,  0.5f, 0.0f }, Graphics::Colors::DarkOrange });
	mVertices.push_back({ Vector3{ -0.10f,  0.2f, 0.0f }, Graphics::Colors::DarkOrange });
	mVertices.push_back({ Vector3{ -0.32f, 0.22f, 0.0f }, Graphics::Colors::DarkOrange });

	// Bottom
	mVertices.push_back({ Vector3{ -0.32f, 0.22f, 0.0f }, Graphics::Colors::White });
	mVertices.push_back({ Vector3{  0.0f,  0.22f, 0.0f }, Graphics::Colors::White });
	mVertices.push_back({ Vector3{  0.0f, -0.02f, 0.0f }, Graphics::Colors::White });

	mVertices.push_back({ Vector3{  0.32f, 0.22f, 0.0f }, Graphics::Colors::White });
	mVertices.push_back({ Vector3{  0.0f, -0.02f, 0.0f }, Graphics::Colors::White });
	mVertices.push_back({ Vector3{  0.0f,  0.22f, 0.0f }, Graphics::Colors::White });

	// Ears
	mVertices.push_back({ Vector3{ -0.175f, 0.625f, 0.0f }, Graphics::Colors::SaddleBrown });
	mVertices.push_back({ Vector3{ -0.14f,    0.5f, 0.0f }, Graphics::Colors::SaddleBrown });
	mVertices.push_back({ Vector3{ -0.21f,    0.5f, 0.0f }, Graphics::Colors::SaddleBrown });

	mVertices.push_back({ Vector3{ -0.175f, 0.75f, 0.0f }, Graphics::Colors::White });
	mVertices.push_back({ Vector3{ -0.1f,    0.5f, 0.0f }, Graphics::Colors::White });
	mVertices.push_back({ Vector3{ -0.25f,   0.5f, 0.0f }, Graphics::Colors::White });

	mVertices.push_back({ Vector3{  0.175f, 0.625f, 0.0f }, Graphics::Colors::SaddleBrown });
	mVertices.push_back({ Vector3{  0.21f,    0.5f, 0.0f }, Graphics::Colors::SaddleBrown });
	mVertices.push_back({ Vector3{  0.14f,    0.5f, 0.0f }, Graphics::Colors::SaddleBrown });

	mVertices.push_back({ Vector3{  0.175f, 0.75f, 0.0f }, Graphics::Colors::White });
	mVertices.push_back({ Vector3{  0.25f,   0.5f, 0.0f }, Graphics::Colors::White });
	mVertices.push_back({ Vector3{  0.1f,    0.5f, 0.0f }, Graphics::Colors::White });

#pragma endregion

	mMeshBuffer.Initialize(mVertices);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoSomething.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoSomething.fx");
}

void FoxState::Terminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void FoxState::Update(float deltaTime)
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
	if (inputSystem->IsKeyPressed(Input::KeyCode::THREE))
	{
		MainApp().ChangeState("TriforceState");
	}
}

void FoxState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mMeshBuffer.Render();
}

void FoxState::DebugUI()
{

}