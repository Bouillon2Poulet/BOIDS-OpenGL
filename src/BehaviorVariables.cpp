#include "BehaviorVariables.h"

void BehaviorVariables::protectedRange(float input)
{
    _protectedRange = input;
}
float BehaviorVariables::protectedRange() const
{
    return _protectedRange;
}
float* BehaviorVariables::protectedRangePtr()
{
    return &_protectedRange;
}

void BehaviorVariables::visibleRange(float input)
{
    _visibleRange = input;
}
float BehaviorVariables::visibleRange() const
{
    return _visibleRange;
}
float* BehaviorVariables::visibleRangePtr()
{
    return &_visibleRange;
}

void BehaviorVariables::avoidFactor(float input)
{
    _avoidFactor = input;
}
float BehaviorVariables::avoidFactor() const
{
    return _avoidFactor;
}
float* BehaviorVariables::avoidFactorPtr()
{
    return &_avoidFactor;
}

void BehaviorVariables::matchingFactor(float input)
{
    _matchingFactor = input;
}
float BehaviorVariables::matchingFactor() const
{
    return _matchingFactor;
}
float* BehaviorVariables::matchingFactorPtr()
{
    return &_matchingFactor;
}

void BehaviorVariables::centeringFactor(float input)
{
    _centeringFactor = input;
}
float BehaviorVariables::centeringFactor() const
{
    return _centeringFactor;
}
float* BehaviorVariables::centeringFactorPtr()
{
    return &_centeringFactor;
}

void BehaviorVariables::turnFactor(float input)
{
    _turnFactor = input;
}
float BehaviorVariables::turnFactor() const
{
    return _turnFactor;
}
float* BehaviorVariables::turnFactorPtr()
{
    return &_turnFactor;
}

void BehaviorVariables::maxSpeed(float input)
{
    _maxSpeed = input;
}
float BehaviorVariables::maxSpeed() const
{
    return _maxSpeed;
}
float* BehaviorVariables::maxSpeedPtr()
{
    return &_maxSpeed;
}

void BehaviorVariables::minSpeed(float input)
{
    _minSpeed = input;
}
float BehaviorVariables::minSpeed() const
{
    return _minSpeed;
}
float* BehaviorVariables::minSpeedPtr()
{
    return &_minSpeed;
}