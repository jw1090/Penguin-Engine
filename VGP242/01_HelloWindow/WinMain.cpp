#include <Core/Inc/Core.h>

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	PenguinEngine::Core::Window myWindow;
	myWindow.Initialize(instance, L"Hello Window", 1280, 720);

	while (true)
	{
		myWindow.ProcessMessage();
		if (!myWindow.IsActive())
		{
			break;
		}
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
	}

	myWindow.Terminate();
	return 0;
}