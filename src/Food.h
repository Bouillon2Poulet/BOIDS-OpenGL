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
    Matrices _matrices;
    float        _maxRadius;
    unsigned int _maxHP;
    float        _currentRadius = _maxRadius;
    unsigned int _currentHP     = _maxHP;

public:
    Food(glm::vec3 maxDistanceFromCenter, unsigned int maxHP, float maxRadius)
        : _position(internal::randomPosInBoundingBox(maxDistanceFromCenter / 2.f)), _maxRadius(maxRadius), _maxHP(maxHP) {}

    inline void isEaten()
    {
        if (_currentHP != 0)
            _currentHP -= 1;
        _currentRadius = _maxRadius * _currentHP / _maxHP;
        if (_currentRadius < 0.03)
        {
            _currentHP = 0;
        }
    }

    inline unsigned int currentHP()
    {
        return _currentHP;
    }

    inline glm::vec3 position()
    {
        return _position;
    }

    inline float radius()
    {
        return _currentRadius;
    }

    inline void draw(myProgram& program,const glm::mat4& projMatrix, const my3DModel& model, const glm::mat4& viewMatrix)
    {
        _matrices.updateObstacle(viewMatrix,_position, _currentRadius);
        _matrices.sendMatricesToShader(program, projMatrix);
        model.draw(program);
    }
};