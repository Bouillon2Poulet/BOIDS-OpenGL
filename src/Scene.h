#pragma once

#include "Fish.h"
#include "FishTemplate.h"



class Scene {
private:
    std::vector<Fish>         _fishes{};
    std::vector<FishTemplate> _fishTemplates{};
    glm::vec2                 _maxDistanceFromCenter;
    bool                      _displayBoundingBox = false;

public:
    Scene(unsigned int nbFishes, glm::vec2 maxDistanceFromCenter);

    void drawBoundingBox(p6::Context& ctx);

    void                       drawFishes(p6::Context& ctx);
    bool                       displayBoundingBox();
    std::vector<FishTemplate>* fishTemplatesPtr();
    bool*                      displayBoundingBoxPtr();

    glm::vec2* maxDistanceFromCenterPtr();
};