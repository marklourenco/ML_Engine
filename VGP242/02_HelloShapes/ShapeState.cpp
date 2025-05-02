#include "ShapeState.h"

using namespace ML_Engine;
using namespace ML_Engine::Graphics;
using namespace ML_Engine::Math;

void ShapeState::Initialize()
{
    // creates a shape out of the vertices
    CreateShape();
    mMeshBuffer.Initialize(mVertices.data(), sizeof(VertexPC), mVertices.size());

    std::filesystem::path shaderFilePath = L"../../Assets/Shaders/DoColor.fx";
    mVertexShader.Initialize<VertexPc>(shaderFilePath);
    mPixelShader.Initialize(shaderFilePath);
}

void ShapeState::Terminate()
{
    mVertices.clear();
    mPixelShader.Terminate();
    mVertexShader.Termine();
    mMeshBuffer.Terminate();
}

void ShapeState::Update(float deltaTime)
{
    if (Input::InputSystem::Get()->IsKeyPressed(Input::KeyCode::UP))
    {
        ML_Engine::MainApp().ChangeState("TriangleShapeState");
    }
}

void ShapeState::Render()
{
    // prepare GPU
    mVertexShader.Bind();
    mPixelShader.Bind;


    // draw
    mMeshBuffer.Render();
}

void ShapeState::CreateShape()
{
    mVertices.push_back({ { -0.5f, 0.0f, 0.0f }, Colors::Red });
    mVertices.push_back({ { 0.0f, 0.75f, 0.0f }, Colors::Blue });
    mVertices.push_back({ { 0.5f, 0.0f, 0.0f }, Colors::Green });

    mVertices.push_back({ { -0.5f, 0.0f, 0.0f }, Colors::Red });
    mVertices.push_back({ { 0.5f, 0.0f, 0.0f }, Colors::Blue });
    mVertices.push_back({ { 0.0f, -0.75f, 0.0f }, Colors::Green });
}

void TriangleShapeState::Update(float deltaTime)
{
    if (Input::InputSystem::Get()->IsKeyPressed(Input::KeyCode::DOWN))
    {
        ML_Engine::MainApp().ChangeState("ShapeState");
    }
}

void TriangleShapeState::CreateShape()
{
    mVertices.push_back({ { -0.75f, -0.75f, 0.0f }, Colors::Red });
    mVertices.push_back({ { -0.5f, 0.0f, 0.0f }, Colors::Blue });
    mVertices.push_back({ { -0.25f, -0.75f, 0.0f }, Colors::Green });

    mVertices.push_back({ { -0.5f, 0.0f, 0.0f }, Colors::Red });
    mVertices.push_back({ { 0.0f, 0.75f, 0.0f }, Colors::Blue });
    mVertices.push_back({ { 0.5f, 0.0f, 0.0f }, Colors::Green });

    mVertices.push_back({ { 0.25f, -0.75f, 0.0f }, Colors::Red });
    mVertices.push_back({ { 0.5f, 0.0f, 0.0f }, Colors::Blue });
    mVertices.push_back({ { 0.75f, -0.75f, 0.0f }, Colors::Green });
}