#include <Inc/ML_Engine.h>

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	ML_Engine::App myApp;
	myApp.Run();

	return 0;
}