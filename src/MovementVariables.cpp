#include "MovementVariables.h"
#include <p6/p6.h>

glm::vec2 MovementVariables::randomPosInBoundingBox(glm::vec2 radii)
{
    return {p6::random::number(-radii.x, radii.x), p6::random::number(-radii.y, radii.y)};
}

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