#include "Scene.h"
#include "Fish.h"
#include "FishTemplate.h"

Scene::Scene(unsigned int nbFishes, glm::vec2 maxDistanceFromCenter)
    : _maxDistanceFromCenter(maxDistanceFromCenter)
{
    std::cout << "1.1\n";
    FishTemplate test;
    _fishTemplates.emplace_back();
    std::cout << "1.2\n";
    _fishTemplates.emplace_back();
    for (unsigned int i = 0; i < nbFishes; i++)
    {
        _fishes.emplace_back(_maxDistanceFromCenter);
        _fishes.back().linkArrayToFish(&_fishes);
    }
    std::cout << "1.2 - maxDistanceFromCenter.x : " << _maxDistanceFromCenter.x << "\n";
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

void Scene::drawFishes(p6::Context& ctx)
{
    std::vector<Fish>::iterator it;
    // int                         count = 0;
    for (it = _fishes.begin(); it != _fishes.end(); it++)
    {
        // count++;
        // std::cout << "N°" << count << std::endl;
        it->update(_fishTemplates[0], ctx.aspect_ratio(), _maxDistanceFromCenter);
        it->draw(ctx, *(_fishTemplates[0].debugUiParametersPtr()), *(_fishTemplates[0].bhvVariablesPtr()));
        // std::cout << "/"<<_fishTemplates[0].debugUiPtr()->variables().protectedRange();
        ;
    }
}

bool Scene::displayBoundingBox()
{
    return _displayBoundingBox;
};

std::vector<FishTemplate>* Scene::fishTemplatesPtr()
{
    return &_fishTemplates;
}

bool* Scene::displayBoundingBoxPtr()
{
    return &_displayBoundingBox;
}

glm::vec2* Scene::maxDistanceFromCenterPtr()
{
    return &_maxDistanceFromCenter;
}