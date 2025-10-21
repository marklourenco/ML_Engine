#include "GameState.h"

using namespace ML_Engine;
using namespace ML_Engine::Graphics;
using namespace ML_Engine::Input;

static int currentObject = 0;
const char* objects[] = { "earth", "rocks", "bricks" };

void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
    mDirectionalLight.ambient = { 0.4f, 0.4f, 0.4f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

    Mesh mesh = MeshBuilder::CreateSphere(30, 30, 1.0f);
    mRenderObject.meshBuffer.Initialize(mesh);
    TextureManager* tm = TextureManager::Get();
    mRenderObject.diffuseMapId = tm->LoadTexture("earth.jpg");
    mRenderObject.specMapId = tm->LoadTexture("earth_spec.jpg");
    mRenderObject.normalMapId = tm->LoadTexture("earth_normal.jpg");
    mRenderObject.bumpMapId = tm->LoadTexture("earth_bump.jpg");

    Mesh meshFloor = MeshBuilder::CreatePlane(3, 3, 3);
    mRenderObjectFloor.meshBuffer.Initialize(meshFloor);
    mRenderObjectFloor.diffuseMapId = tm->LoadTexture("bricks.jpg");
    mRenderObjectFloor.specMapId = tm->LoadTexture("bricks_spec.jpg");
    mRenderObjectFloor.normalMapId = tm->LoadTexture("bricks_normal.jpg");
    mRenderObjectFloor.bumpMapId = tm->LoadTexture("bricks_bump.jpg");

    Mesh meshRock = MeshBuilder::CreateSphere(30, 30, 1.0f);
    mRenderObjectRock.meshBuffer.Initialize(meshRock);
    mRenderObjectRock.diffuseMapId = tm->LoadTexture("rock.jpg");
    mRenderObjectRock.specMapId = tm->LoadTexture("rock_spec.jpg");
    mRenderObjectRock.normalMapId = tm->LoadTexture("rock_normal.jpg");
    mRenderObjectRock.bumpMapId = tm->LoadTexture("rock_bump.jpg");

    std::filesystem::path shaderFile = L"../../Assets/Shaders/CelShader.fx";
    mStandardEffect.Initialize(shaderFile);
    mStandardEffect.SetCamera(mCamera);
    mStandardEffect.SetDirectionalLight(mDirectionalLight);
}
void GameState::Terminate()
{
    mRenderObject.Terminate();
    mRenderObjectFloor.Terminate();
    mRenderObjectRock.Terminate();
    mStandardEffect.Terminate();
}
void GameState::Update(float deltaTime)
{
    UpdateCamera(deltaTime);
}
void GameState::Render()
{
    SimpleDraw::AddGroundPlane(10.0f, Colors::DarkGray);
    SimpleDraw::Render(mCamera);

    mStandardEffect.Begin();
    switch (currentObject)
    {
    case 0:
        mStandardEffect.Render(mRenderObject);
        break;
    case 1:
        mStandardEffect.Render(mRenderObjectRock);
        break;
    case 2:
        mStandardEffect.Render(mRenderObjectFloor);
        break;
    }
    mStandardEffect.End();
}

void GameState::DebugUI()
{
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if(ImGui::CollapsingHeader("Object", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Combo("Object Shown", &currentObject, objects, IM_ARRAYSIZE(objects));
    }

    if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::DragFloat3("Direction#Light", &mDirectionalLight.direction.x, 0.01f))
        {
            mDirectionalLight.direction = Math::Normalize(mDirectionalLight.direction);
        }
        ImGui::ColorEdit4("Ambient#Light", &mDirectionalLight.ambient.r);
        ImGui::ColorEdit4("Diffuse#Light", &mDirectionalLight.diffuse.r);
        ImGui::ColorEdit4("Specular#Light", &mDirectionalLight.specular.r);
    }
    if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::ColorEdit4("Emissive#Material", &mRenderObject.material.emissive.r);
        ImGui::ColorEdit4("Ambient#Material", &mRenderObject.material.ambient.r);
        ImGui::ColorEdit4("Diffuse#Material", &mRenderObject.material.diffuse.r);
        ImGui::ColorEdit4("Specular#Material", &mRenderObject.material.specular.r);
        ImGui::DragFloat("Shininess#Material", &mRenderObject.material.shininess, 0.01f, 0.0f, 10000.0f);
    }

    ImGui::Separator();

    mStandardEffect.DebugUI();

    ImGui::End();
}

void GameState::UpdateCamera(float deltaTime)
{
    Input::InputSystem* input = Input::InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
    const float turnSpeed = 0.1f;

    if (input->IsKeyDown(KeyCode::W))
    {
        mCamera.Walk(moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::S))
    {
        mCamera.Walk(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::D))
    {
        mCamera.Strafe(moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::A))
    {
        mCamera.Strafe(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::E))
    {
        mCamera.Rise(moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::Q))
    {
        mCamera.Rise(-moveSpeed * deltaTime);
    }

    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime); // INVERT IF U WANT
        mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
    }
}