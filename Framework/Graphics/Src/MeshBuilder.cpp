#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace ML_Engine;
using namespace ML_Engine::Graphics;

namespace {
    Color GetNextColor(int& index)
    {
        constexpr Color colorTable[] = {
            Colors::AliceBlue,
            Colors::AntiqueWhite,
            Colors::Beige,
            Colors::Bisque,
            Colors::BlanchedAlmond,
            Colors::LightPink,
            Colors::Lavender
        };

        index = (index + 1) % std::size(colorTable);
		return colorTable[index];
    }

    void CreateCubeIndices(std::vector<uint32_t>& indices) 
    {
        indices = {
            // front
            0, 1, 2,
            0, 2, 3,
            // back
            7, 5, 4,
            7, 6, 5,
            // right
            3, 2, 6,
            3, 6, 7,
            // left
            4, 5, 1,
            4, 1, 0,
            // top
            1, 5, 6,
            1, 6, 2,
            // bottom
            0, 3, 7,
            0, 7, 4
        };
    }

    void CreatePlaneIndices(std::vector<uint32_t>& indices, int numRows, int numColumns)
    {
        for(int r = 0; r < numRows; ++r)
		{
			for (int c = 0; c < numColumns; ++c)
			{
                int i = (r * (numColumns + 1)) + c;

				// triangle 0
				indices.push_back(i);
				indices.push_back(i + numColumns + 1);
				indices.push_back(i + numColumns + 2);

                // triangle 1
				indices.push_back(i);
				indices.push_back(i + numColumns + 2);
				indices.push_back(i + 1);
			}
		}
    }

    void CreateCapIndices(std::vector<uint32_t>& indices, int slices, int topIndex, int bottomIndex)
    {
        for (int s = 0; s < slices; ++s)
        {
            // bottom triangle
			indices.push_back(bottomIndex);
			indices.push_back(s);
			indices.push_back(s + 1);
			// top triangle
            int topRowIndex = topIndex - slices - 1 + s;
			indices.push_back(topIndex);
			indices.push_back(topRowIndex + 1);
			indices.push_back(topRowIndex);
        }
    }
}

MeshPC MeshBuilder::CreateCubePC(float size, const Color& color)
{
    MeshPC mesh;

    const float hs = size * 0.5f;
    // front
    mesh.vertices.push_back({ { -hs, -hs, -hs }, color });
    mesh.vertices.push_back({ { -hs,  hs, -hs }, color });
    mesh.vertices.push_back({ {  hs,  hs, -hs }, color });
    mesh.vertices.push_back({ {  hs, -hs, -hs }, color });
    // back
    mesh.vertices.push_back({ { -hs, -hs,  hs }, color });
    mesh.vertices.push_back({ { -hs,  hs,  hs }, color });
    mesh.vertices.push_back({ {  hs,  hs,  hs }, color });
    mesh.vertices.push_back({ {  hs, -hs,  hs }, color });

    mesh.indices = {
        // front
        0, 1, 2,
        0, 2, 3,
        // back
        7, 5, 4,
        7, 6, 5,
        // right
        3, 2, 6,
        3, 6, 7,
        // left
        4, 5, 1,
        4, 1, 0,
        // top
        1, 5, 6,
        1, 6, 2,
        // bottom
        0, 3, 7,
        0, 7, 4
    };

    return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size)
{
    MeshPC mesh;

    int index = rand() % 100;
    const float hs = size * 0.5f;
    // front
    mesh.vertices.push_back({ { -hs, -hs, -hs }, GetNextColor(index)});
    mesh.vertices.push_back({ { -hs,  hs, -hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs,  hs, -hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs, -hs, -hs }, GetNextColor(index) });
    // back                                      
    mesh.vertices.push_back({ { -hs, -hs,  hs }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hs,  hs,  hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs,  hs,  hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs, -hs,  hs }, GetNextColor(index) });

    mesh.indices = {
        // front
        0, 1, 2,
        0, 2, 3,
        // back
        7, 5, 4,
        7, 6, 5,
        // right
        3, 2, 6,
        3, 6, 7,
        // left
        4, 5, 1,
        4, 1, 0,
        // top
        1, 5, 6,
        1, 6, 2,
        // bottom
        0, 3, 7,
        0, 7, 4
    };

    return mesh;
}

MeshPC ML_Engine::Graphics::MeshBuilder::CreatePyramidPC(float size)
{
    MeshPC mesh;

    int index = rand() % 100;
    const float hs = size * 0.5f;

    mesh.vertices.push_back({ { 0.0f, hs, 0.0f }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hs, -hs, -hs }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hs, -hs,  hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs, -hs,  hs }, GetNextColor(index) });

    mesh.vertices.push_back({ {  hs, -hs, -hs }, GetNextColor(index) });

    // Add indices
    mesh.indices = {
        1, 2, 3,
        1, 3, 4,
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1,
        1, 4, 3,
        1, 3, 2
    };

    return mesh;
}

MeshPC ML_Engine::Graphics::MeshBuilder::CreateRectanglePC(float width, float height, float depth)
{
    MeshPC mesh;

    int index = rand() % 100;
    const float hw = width * 0.5f;
    const float hh = height * 0.5f;
    const float hd = depth * 0.5f;

    mesh.vertices.push_back({ { -hw, -hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hw,  hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw,  hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw, -hh, -hd }, GetNextColor(index) });

    mesh.vertices.push_back({ { -hw, -hh,  hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hw,  hh,  hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw,  hh,  hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw, -hh,  hd }, GetNextColor(index) });

    // Add indices
    mesh.indices = {
        // front face
        0, 1, 2,
        0, 2, 3,
        // back face
        7, 5, 4,
        7, 6, 5,
        // right face
        3, 2, 6,
        3, 6, 7,
        // left face
        4, 5, 1,
        4, 1, 0,
        // top face
        1, 5, 6,
        1, 6, 2,
        // bottom face
        0, 3, 7,
        0, 7, 4
    };

    return mesh;
}

MeshPC MeshBuilder::CreatePlanePC(int numRows, int numColums, float spacing, bool horizontal)
{
    MeshPC mesh;
    int index = rand() % 100;
    const float hpw = static_cast<float>(numColums) * spacing * 0.5f;
    const float hph = static_cast<float>(numRows) * spacing * 0.5f;

    float w = -hpw;
    float h = -hph;

    for (int r = 0; r <= numRows; ++r)
    {
		for (int c = 0; c <= numColums; ++c)
		{
			Math::Vector3 pos = (horizontal) ? Math::Vector3(w, 0.0f, h) : Math::Vector3(w, h, 0.0f);
            mesh.vertices.push_back({ pos, GetNextColor(index) });
            w += spacing;
		}
        w = -hpw;
		h += spacing;
    }

    CreatePlaneIndices(mesh.indices, numRows, numColums);

    return mesh;
}

MeshPC ML_Engine::Graphics::MeshBuilder::CreateCylinderPC(int slices, int rings)
{
    MeshPC mesh;
    int index = rand() % 100;
    
    const float hh = static_cast<float>(rings) * 0.5f;
    const float fSlices = static_cast<float>(slices);

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        for (int s = 0; s <= slices; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / fSlices) * Math::Constants::TwoPi;

            mesh.vertices.push_back({ {
                    sin(rotation),
                    ring - hh,
                    -cos(rotation)},
                    GetNextColor(index) });
        }
    }

    mesh.vertices.push_back({ {0.0f, hh, 0.0f}, GetNextColor(index) });
    mesh.vertices.push_back({ {0.0f, -hh, 0.0f}, GetNextColor(index) });

    CreatePlaneIndices(mesh.indices, rings, slices);
    CreateCapIndices(mesh.indices, slices, mesh.vertices.size() - 2, mesh.vertices.size() - 1);

    return mesh;
}

MeshPC ML_Engine::Graphics::MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
    MeshPC mesh;
    int index = rand() % 100;

    float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
    float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * vertRotation;
        for (int s = 0; s <= slices; ++s)
        {
            float slice = static_cast<float>(s);
			float rotation = slice * horzRotation;
            mesh.vertices.push_back({ {
                    radius * sin(rotation) * sin(phi),
                    radius * cos(phi),
                    radius * cos(rotation) * sin(phi)},
                    GetNextColor(index) });
        }
    }

    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}

MeshPX MeshBuilder::CreateCubePX(float size)
{
    MeshPX mesh;
    

    return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
{
    MeshPX mesh;



    float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
    float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));

    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * vertRotation;
        for (int s = 0; s <= slices; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = slice * horzRotation;

            float u = uStep * slice;
            float v = vStep * ring;
            mesh.vertices.push_back({ {
                    radius * sin(rotation) * sin(phi),
                    radius * cos(phi),
                    radius * cos(rotation) * sin(phi)},
                    { u, v } });
        }
    }

    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}

MeshPX MeshBuilder::CreatePlanePX(int numRows, int numColums, float spacing, bool horizontal)
{
    MeshPX mesh;

    const float hpw = static_cast<float>(numColums) * spacing * 0.5f;
    const float hph = static_cast<float>(numRows) * spacing * 0.5f;
    const float uInc = 1.0f / static_cast<float>(numColums);
    const float vInc = -1.0f / static_cast<float>(numRows);

    float w = -hpw;
    float h = -hph;
    float u = 0.0f;
	float v = 1.0f;

    for (int r = 0; r <= numRows; ++r)
    {
        for (int c = 0; c <= numColums; ++c)
        {
            Math::Vector3 pos = (horizontal) ? Math::Vector3(w, 0.0f, h) : Math::Vector3(w, h, 0.0f);
            mesh.vertices.push_back({ pos, { u, v } });
            w += spacing;
            u += uInc;
        }
        w = -hpw;
        h += spacing;
        u = 0.0f;
        v += vInc;
    }

    CreatePlaneIndices(mesh.indices, numRows, numColums);

    return mesh;
}

MeshPX ML_Engine::Graphics::MeshBuilder::CreateSkySpherePX(int slices, int rings, float radius)
{
    MeshPX mesh;



    float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
    float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));

    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * vertRotation;
        for (int s = 0; s <= slices; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = slice * horzRotation;

            float u = uStep * slice;
            float v = vStep * ring;
            mesh.vertices.push_back({ {
                    radius * cos(rotation) * sin(phi),
                    radius * cos(phi),
                    radius * sin(rotation) * sin(phi) },
                    { u, v } });
        }
    }

    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}
