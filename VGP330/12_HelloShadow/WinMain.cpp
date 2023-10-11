#include "GameState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	auto& app = PenguinEngine::MainApp();
	app.AddState<GameState>("GameState");
	app.Run({ L"Hello Shadows", 1280, 720 });
	return 0;
}