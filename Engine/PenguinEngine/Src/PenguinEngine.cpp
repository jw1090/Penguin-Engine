#include "Precompiled.h"
#include "PenguinEngine.h"

PenguinEngine::App& PenguinEngine::MainApp()
{
	static App sApp;
	return sApp;
}