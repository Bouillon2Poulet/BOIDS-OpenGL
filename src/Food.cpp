#include "Food.h"

Food::Food(glm::vec3 maxDistanceFromCenter, unsigned int maxHP, float maxRadius)
    : _position(internal::randomPosInBoundingBox(maxDistanceFromCenter / 2.f)), _maxRadius(maxRadius), _maxHP(maxHP) {}

void Food::draw(myProgram& program, const glm::mat4& projMatrix, const my3DModel& model, const glm::mat4& viewMatrix)
{
    _matrices.updateObstacle(viewMatrix, _position, _currentRadius);
    _matrices.sendMatricesToShader(program, projMatrix);
    model.draw(program);
}

void Food::isEaten()
{
    if (_currentHP != 0)
        _currentHP -= 1;
    _currentRadius = _maxRadius * _currentHP / _maxHP;
    if (_currentRadius < 0.03)
    {
        _currentHP = 0;
    }
}

unsigned int Food::currentHP()
{
    return _currentHP;
}

glm::vec3 Food::position()
{
    return _position;
}

float Food::radius()
{
    return _currentRadius;
}