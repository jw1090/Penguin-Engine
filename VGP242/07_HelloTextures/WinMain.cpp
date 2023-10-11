#include "CubeState.h"
#include "SkyBoxState.h"
#include "SphereState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	auto& app = PenguinEngine::MainApp();
	app.AddState<SphereState>("SphereState");
	app.AddState<CubeState>("CubeState");
	app.AddState<SkyBoxState>("SkyBoxState");
	app.Run({ L"Hello Textures", 1280, 720 });
	return 0;
}