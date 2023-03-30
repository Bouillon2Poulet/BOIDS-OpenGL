#pragma once

#include "Fish.h"
#include "FishGang.h"

class Scene {
private:
    std::vector<Fish>     _fishes{};
    std::vector<FishGang> _fishGangs{};
    glm::vec2             _maxDistanceFromCenter;
    bool                  _displayBoundingBox = false;

public:
    Scene(unsigned int nbFishes, glm::vec2 maxDistanceFromCenter);

    void drawBoundingBox(p6::Context& ctx);

    void                   drawFishes(p6::Context& ctx);
    bool                   displayBoundingBox();
    std::vector<FishGang>* fishGangsPtr();
    bool*                  displayBoundingBoxPtr();

    glm::vec2* maxDistanceFromCenterPtr();
};