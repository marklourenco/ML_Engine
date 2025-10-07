#include "Precompiled.h"
#include "RenderObject.h"

using namespace ML_Engine;
using namespace ML_Engine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();
}