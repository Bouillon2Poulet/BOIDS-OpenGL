#pragma once
#include <p6/p6.h>
#include <vector>
#include "FishGang.h"
#include "glm/fwd.hpp"

class Food {
private:
    glm::vec2    _position{};
    float        _maxRadius;
    float        _currentRadius;
    unsigned int _maxHP;
    unsigned int _currentHP = _maxHP;

public:
    inline void update(std::vector<FishGang>& FishGangs)
    {
        // Check for every Boids in radius and increment life;
        // Does Food look into each BOIDS or each BOID look into all Foods ?
        unsigned int fishEatingFood = 0;
        for (auto actualFishGang = FishGangs.begin(); actualFishGang != FishGangs.end(); ++actualFishGang)
        {
            for (auto actualFish = *(actualFishGang)->fishesPtr()->begin(); actualFish != *(actualFishGang)->fishesPtr()->end(); actualFish++)
            {
                if (glm::length(actualFish.mvtVariablesPtr()->position() - _position) < _currentRadius)
                {
                    fishEatingFood += 1;
                }
            }
        }
        _currentHP -= fishEatingFood;
        _currentRadius = _maxRadius / std::static_cast<float>(_currentHP) * _maxRadius;
    }
};