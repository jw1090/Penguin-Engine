#include <Core/Inc/Core.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	LOG("Hello, I am %s. My favourite number is %d.", "Lost", 7);
	Sleep(1500);
	LOG("%f seconds have passed.", 1.5f);

	const int num = 42;
	//ASSERT(num == 7, "42 is not 7.");
	return 0;
}