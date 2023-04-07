#pragma once

#include "Fish.h"
#include "FishGang.h"
#include "FoodKind.h"
#include "PlayableFish.h"

class Scene {
private:
    std::vector<FishGang> _fishGangs{};
    std::vector<FoodKind> _allFoods{};
    bool                  _displayBoundingBox = false;
    glm::vec2             _maxDistanceFromCenter{};
    PlayableFish          _playableFish;
    p6::Color             _backgroundColor = p6::NamedColor::Blue;

public:
    Scene(float aspect_ratio);

    void drawBoundingBox(p6::Context& ctx);

    void createFishGangAndFoods(int type, int nbFishes);

    void                   draw(p6::Context& ctx);
    void                   update();
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