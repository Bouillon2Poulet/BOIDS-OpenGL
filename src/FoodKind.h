#pragma once
#include <p6/p6.h>
#include <algorithm>
#include <vector>
#include "FishType.h"
#include "Food.h"
#include "Matrices.h"
#include "glm/fwd.hpp"
#include "my3DModel.h"

class FoodKind {
private:
    std::vector<Food> _foods;
    FishType          _type;
    float             _radius{};
    unsigned int      _hp;
    my3DModel         _model;
    float             _chanceForNewFood = 0.005;
    float             _minDetectionLength;

public:
    FoodKind(FishType type, const glm::vec3& maxDistanceFromCenter);
    void update(const glm::vec3& maxDistanceFromCenter);
    void draw(myProgram& program, const glm::mat4& projMatrix, const glm::mat4 viewMatrix);

    void addFood(const glm::vec3& maxDistanceFromCenter);
    Food* nearestFood(const glm::vec3& position);
};
