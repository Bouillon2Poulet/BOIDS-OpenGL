#include "Scene.h"
#include <string.h>
#include <vector>
#include "Arpenteur.h"
#include "Fish.h"
#include "FishGang.h"
#include "Obstacle.h"
#include "Vertices3D.h"
#include "my3DModel.h"


void Scene::draw(p6::Context& ctx)
{
    // ctx.background(_backgroundColor);

    // _program.m_Program.use();
    _shadowMap.useProgram();

    // sendOpacityToShader(1.);
    // for (auto& food : _allFoods)
    // {
    //     food.draw(_program, _projMatrix, _camera.getViewMatrix());
    // }

    // for (auto& fish : _fishGangs)
    // {
    //     std::cout << fish.name() << std::endl;
    //     fish.draw(ctx, _program, _projMatrix);
    // }

    // _arpenteur.draw(_program, _projMatrix);

    for (auto& obstacle : _obstacles)
    {
        obstacle.draw(_program, _projMatrix);
    }

    // sendOpacityToShader(0.3);
    // displayBoundingBoxIfNecessary();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
   


}

void Scene::displayBoundingBoxIfNecessary()
{
    if (displayBoundingBox())
    {
        drawBoundingBox();
    }
}
void Scene::update(p6::Context& ctx)
{
    // _pointLight.update(ctx.time(), _camera.getViewMatrix(), _program);
    // _directionalLight.update(ctx.time(), _camera.getViewMatrix(), _program);
    // _camera.updateArpenteurPosition(_arpenteur.position());

    // for (unsigned int i = 0; i < _fishGangs.size(); i++)
    // {
    //     _fishGangs[i].update(_maxDistanceFromCenter, _allFoods[i], _camera.getViewMatrix());
    //     _allFoods[i].update(_maxDistanceFromCenter);
    // }
    // _arpenteur.update(ctx, _camera.getViewMatrix(), _maxDistanceFromCenter);
    // _camera.handleDeplacement(ctx);
    // _boundingBoxMatrices.updateBB(_camera.getViewMatrix(), _maxDistanceFromCenter);

    for (auto& obstacle : _obstacles)
    {
        obstacle.update(_camera.getViewMatrix());
    }
}

Scene::Scene(const p6::Context& ctx)
    : _maxDistanceFromCenter(glm::vec3(10)), _arpenteur(_maxDistanceFromCenter), _projMatrix(glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f)), _boundingBox(ShapeType::cube), _shadowMap(_directionalLight.direction())
{
    // Init FishGang and Foods n°1

    std::cout << "CONSTRUCTEUR SCENE\n";
    // createFishGangAndFoods(FishType::tuna, 3);
    createFishGangAndFoods(FishType::koi, 50, 1.f);
    // createFishGangAndFoods(FishType::shark, 3);

    _obstacles.push_back(Obstacle("coral", {0, -4.2, 0.9}, .7));
    _obstacles.push_back(Obstacle("ground", {0., -8., -0.}, 0.31f));
    // Init allFoods
}

void Scene::drawBoundingBox()
{
    _boundingBoxMatrices.sendMatricesToShader(_program, _projMatrix);
    _boundingBox.bindVertexArrayVAO();
    glDrawArrays(GL_TRIANGLES, 0, _boundingBox.size());
    glBindVertexArray(0);
}

bool Scene::displayBoundingBox()
{
    return _displayBoundingBox;
};

std::vector<FishGang>* Scene::fishGangsPtr()
{
    return &_fishGangs;
}

bool* Scene::displayBoundingBoxPtr()
{
    return &_displayBoundingBox;
}

glm::vec3* Scene::maxDistanceFromCenterPtr()
{
    return &_maxDistanceFromCenter;
}

glm::vec3 Scene::randomPosInBoundingBox()
{
    return {p6::random::number(-_maxDistanceFromCenter.x, _maxDistanceFromCenter.x), p6::random::number(-_maxDistanceFromCenter.y, _maxDistanceFromCenter.y), p6::random::number(-_maxDistanceFromCenter.z, _maxDistanceFromCenter.z)};
}

void Scene::createFishGangAndFoods(FishType type, int nbFishes, float radius)
{
    _fishGangs.emplace_back(type, nbFishes, _maxDistanceFromCenter, radius);
    _allFoods.emplace_back(type, _maxDistanceFromCenter);
}
