#include "DebugUiVariable.h"

void DebugUiVariables::operator()(const DebugUiVariables& toCopy)
{
    _position          = toCopy._position;
    _velocity          = toCopy._velocity;
    _protectedRange    = toCopy._protectedRange;
    _visibleRange      = toCopy._visibleRange;
    _neighboringFishes = toCopy._neighboringFishes;
}

DebugUiVariables::DebugUiVariables(MovementVariables& mvtToCopy, BehaviorVariables& bhvToCopy)
    : _position(*(mvtToCopy.positionPtr())), _velocity(*(mvtToCopy.velocityPtr())), _protectedRange(*(bhvToCopy.protectedRangePtr())), _visibleRange(*(bhvToCopy.visibleRangePtr())), _neighboringFishes(*(bhvToCopy.neighboringFishesPtr())){};

glm::vec2 DebugUiVariables::position() const
{
    return _position;
}

glm::vec2 DebugUiVariables::velocity() const
{
    return _velocity;
}

float DebugUiVariables::protectedRange() const
{
    return _protectedRange;
}

float DebugUiVariables::visibleRange() const
{
    return _visibleRange;
}

unsigned int DebugUiVariables::neighboringFishes() const
{
    return _neighboringFishes;
}