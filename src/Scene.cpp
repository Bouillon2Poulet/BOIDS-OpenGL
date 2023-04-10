#include "Scene.h"
#include <string.h>
#include "Fish.h"
#include "FishGang.h"
#include "PlayableFish.h"

void Scene::draw(p6::Context& ctx)
{
    ctx.background(_backgroundColor);
    // First update Fishes
    // Second update Foods
    for (const auto& food : _allFoods)
    {
        food.draw(ctx);
    }

    for (auto it = _fishGangs.begin(); it != _fishGangs.end(); it++) // TODO range-for
    {
        it->draw(ctx);
    }
    _playableFish.update(ctx); // Move into Scene::update()
    _playableFish.draw(ctx);
}

void Scene::update()
{
    for (unsigned int i = 0; i < _fishGangs.size(); i++)
    {
        _fishGangs[i].update(_maxDistanceFromCenter, _allFoods[i]);
        _allFoods[i].update(_maxDistanceFromCenter);
    }
}

Scene::Scene(float aspect_ratio)
    : _maxDistanceFromCenter(*new glm::vec2(aspect_ratio - .3f, 1.f - .2f)), _playableFish(_maxDistanceFromCenter)
{
    // _playableFish = *new PlayableFish(_maxDistanceFromCenter);
    // Init FishGang and Foods n°1
    createFishGangAndFoods(0, 200);
    createFishGangAndFoods(1, 40);
    createFishGangAndFoods(2, 4);

    // Init allFoods
}

void Scene::drawBoundingBox(p6::Context& ctx)
{
    // Bounding box
    ctx.push_transform();
    ctx.use_fill   = false;
    ctx.use_stroke = true;
    ctx.stroke     = p6::Color{1.f, 1.f, 0.f};
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

void Scene::createFishGangAndFoods(int type, int nbFishes)
{
    _fishGangs.emplace_back(type, nbFishes, _maxDistanceFromCenter);
    _allFoods.emplace_back(type, _maxDistanceFromCenter);
}
