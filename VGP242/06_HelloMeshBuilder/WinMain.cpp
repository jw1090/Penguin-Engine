#include "CubeState.h"
#include "PlaneState.h"
#include "CylinderState.h"
#include "SphereState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	auto& app = PenguinEngine::MainApp();
	app.AddState<CubeState>("CubeState");
	app.AddState<PlaneState>("PlaneState");
	app.AddState<CylinderState>("CylinderState");
	app.AddState<SphereState>("SphereState");
	app.Run({ L"Hello Mesh Builder", 1280, 720 });
	return 0;
}