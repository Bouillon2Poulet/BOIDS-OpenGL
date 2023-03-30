#include "Scene.h"
#include "Fish.h"
#include "FishTemplate.h"

Scene::Scene(unsigned int nbFishes, glm::vec2 maxDistanceFromCenter)
    : _maxDistanceFromCenter(maxDistanceFromCenter), _fishTemplate(*new FishTemplate())
{
    std::cout << "1.1\n";
    for (unsigned int i = 0; i < nbFishes; i++)
    {
        _fishes.emplace_back(_fishTemplate, _maxDistanceFromCenter);
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
        it->transferTemplateArguments(_fishTemplate); // FIX : class fishTemplate et class Fish pour pas avoir avoir à copier les variables 200 fois
        it->update(_fishTemplate, ctx.aspect_ratio(), _maxDistanceFromCenter);
        it->draw(ctx);
    }
}

bool Scene::displayBoundingBox()
{
    return _displayBoundingBox;
};

FishTemplate& Scene::fishTemplate()
{
    return _fishTemplate;
}

bool* Scene::displayBoundingBoxPtr()
{
    return &_displayBoundingBox;
}

glm::vec2* Scene::maxDistanceFromCenterPtr()
{
    return &_maxDistanceFromCenter;
}