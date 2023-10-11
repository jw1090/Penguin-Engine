#include <PenguinEngine/Inc/PenguinEngine.h>
#include "GameState.h"

using namespace::PenguinEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config = { L"Hello Game World" };
	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);

	return 0;
}