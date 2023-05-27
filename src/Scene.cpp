#include "Scene.h"
#include <string.h>
#include <vector>
#include "Arpenteur.h"
#include "Fish.h"
#include "FishGang.h"
#include "Obstacle.h"
#include "Vertices3D.h"
#include "my3DModel.h"
#include "myProgram.h"

// Constructor
Scene::Scene(const p6::Context& ctx)
    : _maxDistanceFromCenter(glm::vec3(10)), _projMatrix(glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f)), _boundingBox("boundingBox", "")
{
    // FishGang & Foods
    createFishGangAndFoods(FishType::koi, 30, 1.f);
    createFishGangAndFoods(FishType::shark, 3, 0.3f);

    // Obstacles
    _obstacles.push_back(Obstacle("coral", {0, -4.2, 0.9}, .7));
    _obstacles.push_back(Obstacle("ground", {0., -8., -0.}, 0.31f));
    for (int i = 0; i < 4; i++)
    {
        _obstacles.push_back(Obstacle("algae", {p6::random::number(10) - 5, -6., p6::random::number(10) - 5}, 3.f));
    }
}

void Scene::createFishGangAndFoods(FishType type, int nbFishes, float radius)
{
    _fishGangs.emplace_back(type, nbFishes, _maxDistanceFromCenter, radius);
    _allFoods.emplace_back(type, _maxDistanceFromCenter);
}

// Updates
void Scene::update(p6::Context& ctx)
{
    glm::mat4 viewMatrix = _camera.getViewMatrix(_arpenteur.position());

    updateLights(ctx.time(), viewMatrix);
    _arpenteur.update(ctx, viewMatrix, _camera.getForwardVector(), _maxDistanceFromCenter);
    updateCamera(ctx);
    updateFishGangsAndFoods(viewMatrix);
    updateObstacles(viewMatrix);
    _boundingBoxMatrices.updateBB(viewMatrix, _maxDistanceFromCenter);
}

void Scene::updateFishGangsAndFoods(const glm::mat4& viewMatrix)
{
    for (unsigned int i = 0; i < _fishGangs.size(); i++)
    {
        _fishGangs[i].update(_maxDistanceFromCenter, _allFoods[i], viewMatrix);
        _allFoods[i].update(_maxDistanceFromCenter);
    }
}

void Scene::updateObstacles(const glm::mat4& viewMatrix)
{
    for (auto& obstacle : _obstacles)
    {
        obstacle.update(viewMatrix);
    }
}

void Scene::updateCamera(p6::Context& ctx)
{
    _camera.updateArpenteurPosition(_arpenteur.position());
    _camera.handleDeplacement(ctx);
}

void Scene::updateLights(const float time, const glm::mat4& viewMatrix)
{
    _pointLight.update(time, viewMatrix, _program);
    _directionalLight.update(_program);
}

// Draw
void Scene::draw(p6::Context& ctx)
{
    _program.m_Program.use();
    sendOpacityToShader(1.);

    drawFishGangsAndFoods(ctx);
    drawObstacles();
    _arpenteur.draw(_program, _projMatrix);
    _cubemap.draw(_program, _projMatrix, _camera.getViewMatrix(_arpenteur.position()), ctx.time());
    drawBoundingBox();
}

void Scene::drawFishGangsAndFoods(p6::Context& ctx)
{
    for (auto& food : _allFoods)
    {
        food.draw(_program, _projMatrix, _camera.getViewMatrix(_arpenteur.position()));
    }

    for (auto& fish : _fishGangs)
    {
        fish.draw(_program, _projMatrix, _arpenteur.position());
    }
}

void Scene::drawObstacles()
{
    for (auto& obstacle : _obstacles)
    {
        obstacle.draw(_program, _projMatrix, _arpenteur.position());
    }
}

void Scene::drawBoundingBox()
{
    sendOpacityToShader(_boundingBoxOpacity);
    _boundingBox.activateTexture(_program);
    _boundingBoxMatrices.sendMatricesToShader(_program, _projMatrix);
    _boundingBox.draw(_program);
}

void Scene::sendOpacityToShader(float opacity)
{
    glUniform1f(_program.uOpacity, opacity);
}

// Pointeur
std::vector<FishGang>* Scene::fishGangsPtr()
{
    return &_fishGangs;
}

glm::vec3* Scene::maxDistanceFromCenterPtr()
{
    return &_maxDistanceFromCenter;
}

float* Scene::boundingBoxOpacityPtr()
{
    return &_boundingBoxOpacity;
}

// Position
glm::vec3 Scene::randomPosInBoundingBox()
{
    return {p6::random::number(-_maxDistanceFromCenter.x, _maxDistanceFromCenter.x), p6::random::number(-_maxDistanceFromCenter.y, _maxDistanceFromCenter.y), p6::random::number(-_maxDistanceFromCenter.z, _maxDistanceFromCenter.z)};
}

glm::vec3 Scene::maxDistanceFromCenter()
{
    return _maxDistanceFromCenter;
}

// GUI
void Scene::GUIdisplay()
{
    for (auto& fishGang : _fishGangs)
    {
        ImGui::Begin(fishGang.name().c_str());
        fishGang.GUIdisplayFishGangBehaviorVariables();
        ImGui::End();
    }
    GUIdisplaySceneParameter();
}

void Scene::GUIdisplaySceneParameter()
{
    ImGui::SliderFloat("BoundingBox opacity", &_boundingBoxOpacity, 0.f, 1.f);
    ImGui::SliderFloat("BoundingBox width", &(maxDistanceFromCenterPtr()->x), 0.f, 20.f);
    ImGui::SliderFloat("BoundingBox depth", &(maxDistanceFromCenterPtr()->z), 0.f, 20.f);
    ImGui::SliderFloat("BoundingBox height", &(maxDistanceFromCenterPtr()->y), 0.f, 20.f);
}
