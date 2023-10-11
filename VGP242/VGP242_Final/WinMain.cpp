#include "SpaceScene.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	auto& app = PenguinEngine::MainApp();
	app.AddState<SpaceScene>("SpaceScene");
	app.Run({ L"Hello Space", 1280, 720 });
	return 0;
}