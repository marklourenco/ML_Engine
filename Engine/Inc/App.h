#pragma once

namespace ML_Engine
{
    class App final
    {
    public:
        void Run();
        void Quit();
    private:
        bool mRunning = false;
    };
}