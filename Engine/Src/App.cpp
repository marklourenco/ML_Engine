#include "Precompiled.h"
#include "App.h"

using namespace ML_Engine;
using namespace ML_Engine::Core;

void ML_Engine::App::Run()
{
    LOG("App Started");

    mRunning = true;
    while (mRunning)
    {
        LOG("Running");
    }

    LOG("App Quit");
}

void ML_Engine::App::Quit()
{
    mRunning = false;
}
