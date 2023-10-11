#include "GameState.h"

using namespace PenguinEngine;

void GameState::Initialize()
{
	mGameWorld.AddService<CameraService>();
	mGameWorld.AddService<RenderService>();
	
	mGameWorld.Initialize(100);

	mGameWorld.CreateGameObject("../../Assets/Templates/fps_camera.json");
	mGameWorld.CreateGameObject("../../Assets/Templates/test_player.json");
}

void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
	mGameWorld.Render();
}

void GameState::DebugUI()
{
	mGameWorld.DebugUI();
}