#pragma once

#include "MeshBuffer.h"
#include "Transform.h"
#include "Material.h"
#include "TextureManager.h"

namespace ML_Engine::Graphics
{
	class RenderObject
	{
	public:
		void Terminate();

		Transform transform;      // location
		MeshBuffer meshBuffer;    // shape
		Material material;        // light data
		TextureId diffuseMapId;   // diffuse texture for an object
		TextureId specMapId;
		TextureId normalMapId;
		TextureId bumpMapId;
	};
}