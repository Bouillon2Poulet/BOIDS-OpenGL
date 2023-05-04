#include "Scene.h"
#include <string.h>
#include <vector>
#include "Arpenteur.h"
#include "Fish.h"
#include "FishGang.h"
#include "Vertices3D.h"
#include "my3DModel.h"


void Scene::draw(p6::Context& ctx)
{
    // ctx.background(_backgroundColor);

    _program.m_Program.use();

    sendOpacityToShader(1.);
    // for (const auto& food : _allFoods)
    // {
    //     food.draw(ctx);
    // }

    for (auto& fish : _fishGangs)
    {
        std::cout << fish.name() << std::endl;
        fish.draw(ctx, _program, _projMatrix);
    }
    // for (std::vector<FishGang>::iterator i = _fishGangs.begin(); i != _fishGangs.end() - 1; i++) // Without last fishGang
    // {
    //     std::cout << i->name() << std::endl;
    //     i->draw(ctx, _program, _projMatrix);
    // }
    _arpenteur.draw(_program, _projMatrix);

    for (auto& obstacle : _environment)
    {
        obstacle.draw(_program, _projMatrix);
    }

    sendOpacityToShader(0.3);
    displayBoundingBoxIfNecessary();
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
    std::cout << "Tuna.vertices.size : " << _fishGangs.front().vertices3DSize() << std::endl;
    std::cout << "Koi.vertices.size : " << _fishGangs.back().vertices3DSize() << std::endl;
    // int a;
    // std::cin >> a;

    _camera.updateArpenteurPosition(_arpenteur.position());

    for (unsigned int i = 0; i < _fishGangs.size(); i++)
    {
        _fishGangs[i].update(_maxDistanceFromCenter, _allFoods[i], _camera.getViewMatrix());
        // _allFoods[i].update(_maxDistanceFromCenter);
    }
    _arpenteur.update(ctx, _camera.getViewMatrix(), _maxDistanceFromCenter);
    _camera.handleDeplacement(ctx);
    _boundingBoxMatrices.updateBB(_camera.getViewMatrix(), _maxDistanceFromCenter);

    for (auto& obstacle : _environment)
    {
        obstacle.update(_camera.getViewMatrix());
    }
}

Scene::Scene(const p6::Context& ctx)
    : _maxDistanceFromCenter(glm::vec3(10)), _arpenteur(_maxDistanceFromCenter), _projMatrix(glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f)), _boundingBox(ShapeType::cube)
{
    // Init FishGang and Foods n°1

    std::cout << "CONSTRUCTEUR SCENE\n";
    // createFishGangAndFoods(FishType::tuna, 3);
    createFishGangAndFoods(FishType::koi, 50);
    // createFishGangAndFoods(FishType::shark, 4);

    _environment.push_back(my3DModel("coral", {0, -3, 0.2}, 1));
    _environment.push_back(my3DModel("ground", {0.5, -4, -0.7}, 0.29f));
    // my3DModel coralTest("coral.obj");
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

void Scene::createFishGangAndFoods(FishType type, int nbFishes)
{
    _fishGangs.emplace_back(type, nbFishes, _maxDistanceFromCenter);
    _allFoods.emplace_back(type, _maxDistanceFromCenter);
}
