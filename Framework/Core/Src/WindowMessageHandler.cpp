#include "Precompiled.h"
#include "WindowMessageHandler.h"
#include "DebugUtil.h"


using namespace ML_Engine;
using namespace ML_Engine::Core;

void WindowMessageHandler::Hook(HWND window, Callback cb)
{
	mWindow = window;
	mPreviousCallback = (Callback)GetWindowLongPtrA(window, GWLP_WNDPROC);
	SetWindowLongA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}

void WindowMessageHandler::Unhook()
{
	SetWindowLongPtrA(mWindow, GWLP_WNDPROC, (LONG_PTR)mPreviousCallback);
	mWindow = nullptr;
}

LRESULT WindowMessageHandler::ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	ASSERT(mPreviousCallback != nullptr, "WindowMessageHandler:: No callback is hooked.");
	return CallWindowProcA((WNDPROC)mPreviousCallback, window, message, wParam, lParam);
}