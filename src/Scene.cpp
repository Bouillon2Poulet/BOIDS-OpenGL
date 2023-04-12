#include "Scene.h"
#include <string.h>
#include "Fish.h"
#include "FishGang.h"
#include "PlayableFish.h"

void Scene::draw(p6::Context& ctx)
{
    ctx.background(_backgroundColor);

    for (const auto& food : _allFoods)
    {
        food.draw(ctx);
    }

    for (const auto& fish : _fishGangs)
    {
        fish.draw(ctx);
    }

    displayBoundingBoxIfNecessary(ctx);

    _playableFish.draw(ctx);
}

void Scene::displayBoundingBoxIfNecessary(p6::Context& ctx)
{
    if (displayBoundingBox())
    {
        drawBoundingBox(ctx);
    }
}
void Scene::update(const glm::vec2& mousePosition)
{
    for (unsigned int i = 0; i < _fishGangs.size(); i++)
    {
        _fishGangs[i].update(_maxDistanceFromCenter, _allFoods[i]);
        _allFoods[i].update(_maxDistanceFromCenter);
    }
    _playableFish.update(mousePosition); // Move into Scene::update()
}

Scene::Scene(float aspect_ratio)
    : _maxDistanceFromCenter(*new glm::vec2(aspect_ratio - .3f, 1.f - .2f)), _playableFish(_maxDistanceFromCenter)
{
    // _playableFish = *new PlayableFish(_maxDistanceFromCenter);
    // Init FishGang and Foods n°1
    createFishGangAndFoods(FishType::koi, 200);
    createFishGangAndFoods(FishType::tuna, 40);
    createFishGangAndFoods(FishType::whale, 4);

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

void Scene::createFishGangAndFoods(FishType type, int nbFishes)
{
    _fishGangs.emplace_back(type, nbFishes, _maxDistanceFromCenter);
    _allFoods.emplace_back(type, _maxDistanceFromCenter);
}
