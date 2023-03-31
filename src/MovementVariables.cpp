#include "MovementVariables.h"
#include <p6/p6.h>

void MovementVariables::position(glm::vec2 input)
{
    _position = input;
}
glm::vec2 MovementVariables::position() const
{
    return _position;
}
glm::vec2* MovementVariables::positionPtr()
{
    return &_position;
}

void MovementVariables::velocity(glm::vec2 input)
{
    _velocity = input;
}
glm::vec2 MovementVariables::velocity() const
{
    return _velocity;
}
glm::vec2* MovementVariables::velocityPtr()
{
    return &_velocity;
}