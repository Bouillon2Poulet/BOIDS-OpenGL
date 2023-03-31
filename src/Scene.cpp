#include "Scene.h"
#include <string.h>
#include "Fish.h"
#include "FishGang.h"

void Scene::draw(p6::Context& ctx)
{
    ctx.background(_backgroundColor);
    //First update Fishes
    //Second update Foods
    for (auto it = _fishGangs.begin(); it != _fishGangs.end(); it++)
    {
        // std::cout << "DRAWING SCENE, fishGang : ";
        // it->printName();
        // std::cout << std::endl;

        it->draw(ctx, _maxDistanceFromCenter);
    }
}

Scene::Scene(float aspect_ratio)
    : _maxDistanceFromCenter(*new glm::vec2(aspect_ratio - .3f, 1.f - .2f))
{
    std::cout << "1.1\n";
    _fishGangs.emplace_back(0, 50, _maxDistanceFromCenter); // Bug
    _fishGangs.emplace_back(1, 10, _maxDistanceFromCenter); // Working
    // for (unsigned int i = 0; i < 50; i++)
    //     std::cout << "1.2 - maxDistanceFromCenter.x : " << _maxDistanceFromCenter.x << "\n";
}

void Scene::drawBoundingBox(p6::Context& ctx)
{
    // Bounding box
    ctx.push_transform();
    ctx.use_fill   = false;
    ctx.use_stroke = true;
    ctx.stroke     = p6::Color{1.f, 0.f, 0.f};
    ctx.rectangle(
        p6::Center{.0f, .0f},
        p6::Radii{_maxDistanceFromCenter.x, _maxDistanceFromCenter.y},
        p6::Rotation{}
    );
    ctx.pop_transform();
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

glm::vec2* Scene::maxDistanceFromCenterPtr()
{
    return &_maxDistanceFromCenter;
}

glm::vec2 Scene::randomPosInBoundingBox()
{
    return {p6::random::number(_maxDistanceFromCenter.x, _maxDistanceFromCenter.x), p6::random::number(_maxDistanceFromCenter.y, _maxDistanceFromCenter.y)};
}