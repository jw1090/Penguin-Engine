#include "TriangleState.h"
#include "HeartState.h"
#include "TriforceState.h"
#include "FoxState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	auto& app = PenguinEngine::MainApp();
	app.AddState<TriangleState>("TriangleState");
	app.AddState<HeartState>("HeartState");
	app.AddState<TriforceState>("TriforceState");
	app.AddState<FoxState>("FoxState");
	app.Run({ L"Hello Shapes", 1280, 720 });
	return 0;
}