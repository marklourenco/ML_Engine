#pragma once

#include "MeshBuffer.h"
#include "Transform.h"

namespace ML_Engine::Graphics
{
	class RenderObject
	{
	public:
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;
	};
}