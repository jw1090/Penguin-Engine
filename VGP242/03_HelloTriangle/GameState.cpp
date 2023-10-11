#include "GameState.h"

void GameState::Initialize()
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

	mVertices.push_back({ Vector3{  0.0f,  0.5f, 0.0f } });
	mVertices.push_back({ Vector3{  0.5f, -0.5f, 0.0f } });
	mVertices.push_back({ Vector3{ -0.5f, -0.5f, 0.0f } });

	mMeshBuffer.Initialize(mVertices);

	mVertexShader.Initialize<VertexP>(L"../../Assets/Shaders/DoNothing.fx");
	mPixelShader.Initialize(L"../../Assets/Shaders/DoNothing.fx");
}

void GameState::Terminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{

}

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mMeshBuffer.Render();
}

void GameState::DebugUI()
{

}