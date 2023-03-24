#include "Fish.h"
#include <cmath>
#include <string>
#include "glm/fwd.hpp"
#include "internal.h"

void Fish::screenAspectRatio(float input)
{
    _screenAspectRatio = input;
}
float Fish::screenAspectRatio() const
{
    return _screenAspectRatio;
}
float* Fish::screenAspectRatioPtr()
{
    return &_screenAspectRatio;
}

// void Fish::bhvVariables(BehaviorVariables input)
// {
//     _bhvVariables = input;
// }
BehaviorVariables* Fish::bhvVariablesPtr()
{
    return &_bhvVariables;
}

DebugUi* Fish::debugUiPtr()
{
    return &_debugUi;
}

void Fish::draw(p6::Context& ctx) const
{
    std::cout << "DRAWFISH :" << _mvtVariables.position().x << std::endl;
    drawFish(ctx);
    if (_debugUi.parameters().displayProtectedRange())
        _debugUi.drawProtectedCircle(ctx);
    if (_debugUi.parameters().displayVisibleRange())
        _debugUi.drawVisibleCircle(ctx);
    if (_debugUi.parameters().displayVelocityVector())
        _debugUi.drawVelocityVector(ctx);
    if (_debugUi.parameters().displayProximityNbr())
        _debugUi.drawProximityNbr(ctx);
}

void Fish::update(float aspect_ratio, glm::vec2& maxDistanceFromCenter)
{
    screenAspectRatio(aspect_ratio);
    _bhvVariables.neighboringFishesReset();

    // Separation variable
    glm::vec2 closeSum(.0f, .0f);

    // Alignment _bhvVariables
    glm::vec2 averageVelocity(.0f, .0f);

    // Cohesion _bhvVariables
    glm::vec2 averagePosition(.0f, .0f);

    // Behaviors
    std::vector<Fish>::iterator it;
    for (it = _allFishes->begin(); it != _allFishes->end(); it++)
    {
        if (this == &(*it))
        {
            continue;
        }
        handleSeparation(*it, closeSum);
        handleAlignment(*it, averageVelocity);
        handleCohesion(*it, averagePosition);
    }

    // Velocity update
    // Separation
    _mvtVariables.velocity(_mvtVariables.velocity() + closeSum * _bhvVariables.avoidFactor());

    // Alignment and Cohesion
    if (_bhvVariables.neighboringFishes() != 0)
    {
        averageVelocity /= _bhvVariables.neighboringFishes();
        _mvtVariables.velocity(_mvtVariables.velocity() + (averageVelocity - _mvtVariables.velocity()) * _bhvVariables.matchingFactor());
        // _velocity += (averageVelocity - _velocity) * _bhvVariables.matchingFactor();

        // averagePosition /= neighboringFishes;
        // _velocity += (averagePosition - _position) * _bhvVariables.centeringFactor();
    }

    handleScreenBorders(maxDistanceFromCenter);

    // Min and Max speed
    float speed = std::sqrt(std::pow(_mvtVariables.velocity().x, 2.f) + std::pow(_mvtVariables.velocity().y, 2.f));
    if (speed > _bhvVariables.maxSpeed())
        // _velocity = (_velocity / speed) * _bhvVariables.maxSpeed();
        _mvtVariables.velocity((_mvtVariables.velocity() / speed) * _bhvVariables.maxSpeed());

    if (speed < _bhvVariables.minSpeed())
        // _velocity = (_velocity / speed) * _bhvVariables.minSpeed();
        _mvtVariables.velocity((_mvtVariables.velocity() / speed) * _bhvVariables.minSpeed());

    // Position update
    // _position += _velocity / 10.f;
    _mvtVariables.position(_mvtVariables.position() + (_mvtVariables.velocity() / 10.f));
}

void Fish::drawFish(p6::Context& ctx) const
{
    ctx.push_transform();
    ctx.translate({_mvtVariables.position().x, _mvtVariables.position().y});
    ctx.fill       = {1.f, 0.7f, 0.2f};
    ctx.use_fill   = true;
    ctx.use_stroke = false;
    ctx.square(
        p6::Center{.0f, .0f},
        p6::Radius{_radius}
    );
    ctx.pop_transform();
}

void Fish::linkArrayToFish(std::vector<Fish>* array)
{
    _allFishes = array;
}

void Fish::handleSeparation(Fish& OtherFish, glm::vec2& closeSum)
{
    if (glm::length(OtherFish._mvtVariables.position() - _mvtVariables.position()) <= _bhvVariables.protectedRange())
    {
        closeSum += (_mvtVariables.position() - OtherFish._mvtVariables.position());
    }
}

void Fish::handleAlignment(Fish& OtherFish, glm::vec2& averageVelocity)
{
    if (glm::length(OtherFish._mvtVariables.position() - _mvtVariables.position()) <= _bhvVariables.visibleRange())
    {
        averageVelocity += OtherFish._mvtVariables.velocity();
        _bhvVariables.neighboringFishesIncrement();
    }
}

void Fish::handleCohesion(Fish& OtherFish, glm::vec2& averagePosition)
{
    if (glm::length(OtherFish._mvtVariables.position() - _mvtVariables.position()) <= _bhvVariables.visibleRange())
    {
        averagePosition += OtherFish._mvtVariables.position();
    }
}

void Fish::handleScreenBorders(glm::vec2& maxDistanceFromCenter)
{
    glm::vec2 bordersForces{};
    float     rightBorderForce = -1.f / (std::pow(maxDistanceFromCenter.x - _mvtVariables.position().x, 2.f));
    float     leftBorderForce  = 1.f / (std::pow(-maxDistanceFromCenter.x - _mvtVariables.position().x, 2.f));

    float topBorderForce = -1.f / ((maxDistanceFromCenter.y - _mvtVariables.position().y) * (maxDistanceFromCenter.y - _mvtVariables.position().y));
    float botBorderForce = 1.f / ((-maxDistanceFromCenter.y - _mvtVariables.position().y) * (-maxDistanceFromCenter.y - _mvtVariables.position().y));

    bordersForces.x = rightBorderForce + leftBorderForce;
    bordersForces.y = topBorderForce + botBorderForce;

    _mvtVariables.velocity(_mvtVariables.velocity() + (bordersForces / 100.f));
}

void Fish::transferTemplateArguments(Fish& fishTemplate)
{
    //_mvtVariables.copy(fishTemplate._mvtVariables); DEBUG
    _bhvVariables.copy(fishTemplate._bhvVariables);
    //_debugUi.copy(fishTemplate._debugUi); DEBUG
}
