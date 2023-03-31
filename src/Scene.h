#pragma once

#include "Fish.h"
#include "FishGang.h"

class Scene {
private:
    // std::vector<Fish>     _fishes{};
    std::vector<FishGang> _fishGangs{};
    bool                  _displayBoundingBox = false;
    glm::vec2             _maxDistanceFromCenter{};
    p6::Color             _backgroundColor = p6::NamedColor::Blue;

public:
    Scene(float aspect_ratio);

    void drawBoundingBox(p6::Context& ctx);

    void                   draw(p6::Context& ctx);
    bool                   displayBoundingBox();
    std::vector<FishGang>* fishGangsPtr();
    bool*                  displayBoundingBoxPtr();

    glm::vec2* maxDistanceFromCenterPtr();
    glm::vec2  randomPosInBoundingBox();

    inline glm::vec2 maxDistanceFromCenter()
    {
        return _maxDistanceFromCenter;
    }
    inline p6::Color* backgroundColorPtr()
    {
        return &_backgroundColor;
    }
};