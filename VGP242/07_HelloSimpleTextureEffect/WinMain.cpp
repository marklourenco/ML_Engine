#include "GameState.h"

using namespace ML_Engine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Simple Texture Effect";
	
	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);

	return 0;
}