#include "HeartState.h"

void HeartState::Initialize()
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

	// Top Row
	mVertices.push_back({ Vector3{ -0.18f,  0.5f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.18f, 0.25f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.33f, 0.25f, 0.0f },  Graphics::Colors::DarkRed });
														   
	mVertices.push_back({ Vector3{ -0.16f,  0.5f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  -0.01, 0.25f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.16f, 0.25f, 0.0f },  Graphics::Colors::DarkRed });
														   
	mVertices.push_back({ Vector3{  0.16f,  0.5f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.16f, 0.25f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.01f, 0.25f, 0.0f },  Graphics::Colors::DarkRed });
														   
	mVertices.push_back({ Vector3{  0.18f,  0.5f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.33f, 0.25f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{   0.18, 0.25f, 0.0f },  Graphics::Colors::DarkRed });
														   
	// Second Row - Left Half							   
	mVertices.push_back({ Vector3{ -0.33f, 0.23f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  -0.18f, 0.0f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  -0.33f, 0.0f, 0.0f },  Graphics::Colors::DarkRed });
														   
	mVertices.push_back({ Vector3{ -0.33f, 0.23f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.18f, 0.23f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  -0.18f, 0.0f, 0.0f },  Graphics::Colors::DarkRed });
														   
	mVertices.push_back({ Vector3{ -0.16f, 0.23f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  -0.01f, 0.0f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  -0.16f, 0.0f, 0.0f },  Graphics::Colors::DarkRed });
														   
	mVertices.push_back({ Vector3{ -0.16f, 0.23f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.01f, 0.23f, 0.0f },  Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  -0.01f, 0.0f, 0.0f },  Graphics::Colors::DarkRed });
														   
	// Second Row - Right Half							   
	mVertices.push_back({ Vector3{ 0.16f, 0.23f, 0.0f },   Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.16f, 0.0f, 0.0f },   Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.01f, 0.0f, 0.0f },   Graphics::Colors::DarkRed });
														   
	mVertices.push_back({ Vector3{ 0.16f, 0.23f, 0.0f },   Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.01f, 0.0f, 0.0f },   Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ 0.01f, 0.23f, 0.0f },   Graphics::Colors::DarkRed });
														   
	mVertices.push_back({ Vector3{ 0.33f, 0.23f, 0.0f },   Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.33f, 0.0f, 0.0f },   Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.18f, 0.0f, 0.0f },   Graphics::Colors::DarkRed });
														   
	mVertices.push_back({ Vector3{ 0.33f, 0.23f, 0.0f },   Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.18f, 0.0f, 0.0f },   Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ 0.18f, 0.23f, 0.0f },   Graphics::Colors::DarkRed });

	// Third Row - Left Half
	mVertices.push_back({ Vector3{ -0.33f, -0.02f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.18f, -0.02f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.18f, -0.27f, 0.0f }, Graphics::Colors::DarkRed });

	mVertices.push_back({ Vector3{ -0.16f, -0.02f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.01f, -0.27f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.16f, -0.27f, 0.0f }, Graphics::Colors::DarkRed });

	mVertices.push_back({ Vector3{ -0.16f, -0.02f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.01f, -0.02f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.01f, -0.27f, 0.0f }, Graphics::Colors::DarkRed });

	// Third Row - Right Half							   
	mVertices.push_back({ Vector3{ 0.16f,  -0.02f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.16f, -0.27f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.01f, -0.27f, 0.0f }, Graphics::Colors::DarkRed });

	mVertices.push_back({ Vector3{ 0.16f,  -0.02f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.01f, -0.27f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ 0.01f,  -0.02f, 0.0f }, Graphics::Colors::DarkRed });

	mVertices.push_back({ Vector3{ 0.33f,  -0.02f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.18f, -0.27f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ 0.18f,  -0.02f, 0.0f }, Graphics::Colors::DarkRed });

	// Fourth Row
	mVertices.push_back({ Vector3{ -0.16f, -0.29f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.01f, -0.29f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ -0.01f, -0.54f, 0.0f }, Graphics::Colors::DarkRed });

	mVertices.push_back({ Vector3{ 0.16f,  -0.29f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{  0.01f, -0.54f, 0.0f }, Graphics::Colors::DarkRed });
	mVertices.push_back({ Vector3{ 0.01f,  -0.29f, 0.0f }, Graphics::Colors::DarkRed });

#pragma endregion

	mMeshBuffer.Initialize(mVertices);

	mVertexShader.Initialize<VertexPC>(L"../../Assets/Shaders/DoSomething.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoSomething.fx");
}

void HeartState::Terminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void HeartState::Update(float deltaTime)
{
	auto inputSystem = Input::InputSystem::Get();
	if(inputSystem->IsKeyPressed(Input::KeyCode::ONE))
	{
		MainApp().ChangeState("TriangleState");
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

void HeartState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mMeshBuffer.Render();
}

void HeartState::DebugUI()
{

}