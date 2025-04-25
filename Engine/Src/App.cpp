#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace ML_Engine;
using namespace ML_Engine::Core;
using namespace ML_Engine::Graphics;

void App::Run(const AppConfig& config)
{
    LOG("App Started");

	// Initialize everything
    Window myWindow;
    myWindow.Initialize(
        GetModuleHandle(nullptr),
        config.appName,
        config.winWidth,
		config.winHeight
    );
    auto handle = myWindow.GetWindowHandle();
    GraphicsSystem::StaticInitialize(handle, false);

    // last step before running
	ASSERT(mCurrentState != nullptr, "App: need an app state to run.");
	mCurrentState->Initialize();

    // Process updates
    mRunning = true;
    while (mRunning)
    {
		myWindow.ProcessMessage();
		if (!myWindow.IsActive())
		{
            Quit();
            continue;
		}

		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
			mNextState = nullptr;
		}

		float deltaTime = TimeUtil::GetDeltaTime();
#if defined(_DEBUG)
        if (deltaTime < 0.5f) // primarily for handling breakpoints
#endif
        {
			mCurrentState->Update(deltaTime);
        }

        GraphicsSystem* gs = GraphicsSystem::Get();
        gs->BeginRender();
            mCurrentState->Render();
        gs->EndRender();
    }

    // Terminate everything
    LOG("App Quit");
	mCurrentState->Terminate();

    GraphicsSystem::StaticTerminate();
    myWindow.Terminate();
}

void ML_Engine::App::Quit()
{
    mRunning = false;
}

void ML_Engine::App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}
	else
	{
		LOG("App: State %s not found", stateName.c_str());
	}
}
