#pragma once
#include <p6/p6.h>
#include <string>
#include <vector>
#include "Matrices.h"
#include "glm/fwd.hpp"
#include "internal.h"
#include "my3DModel.h"
#include "myProgram.h"

class Food {
private:
    glm::vec3    _position{};
    Matrices     _matrices;
    float        _maxRadius;
    unsigned int _maxHP;
    float        _currentRadius = _maxRadius;
    unsigned int _currentHP     = _maxHP;

public:
    Food(glm::vec3 maxDistanceFromCenter, unsigned int maxHP, float maxRadius);
    void draw(myProgram& program, const glm::mat4& projMatrix, const my3DModel& model, const glm::mat4& viewMatrix);

    void isEaten();

    unsigned int currentHP();
    glm::vec3    position();
    float        radius();
};