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

    mesh.vertices.push_back({ { -hs, 0.0f, -hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs, 0.0f, -hs }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hs, 0.0f,  hs }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hs, 0.0f,  hs }, GetNextColor(index) });

    mesh.vertices.push_back({ { 0.0f, hs, 0.0f }, GetNextColor(index) });

    // Add indices
    mesh.indices = {
        // front face
        0, 1, 4,
        // right face
        1, 2, 4,
        // back face
        2, 3, 4,
        // left face
        3, 0, 4,
        // base face
        0, 1, 2,
        0, 2, 3
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
    mesh.vertices.push_back({ {  hw, -hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw,  hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hw,  hh, -hd }, GetNextColor(index) });

    mesh.vertices.push_back({ { -hw, -hh,  hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw, -hh,  hd }, GetNextColor(index) });
    mesh.vertices.push_back({ {  hw,  hh,  hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hw,  hh,  hd }, GetNextColor(index) });

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
