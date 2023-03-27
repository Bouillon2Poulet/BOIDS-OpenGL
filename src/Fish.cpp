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
    if (_debugUi.parameters().displayProtectedRange())
    {
        _debugUi.drawProtectedCircle(ctx);
    }
    if (_debugUi.parameters().displayVisibleRange())
        _debugUi.drawVisibleCircle(ctx);
    if (_debugUi.parameters().displayVelocityVector())
        _debugUi.drawVelocityVector(ctx);
    if (_debugUi.parameters().displayProximityNbr())
        _debugUi.drawProximityNbr(ctx);
    drawFish(ctx);
}

static void handleBehaviors(Fish& actualFish, Fish& otherFish, glm::vec2 closeSum, glm::vec2& averageVelocity, glm::vec2& averagePosition, glm::vec2& maxDistanceFromCenter)
{
    actualFish.handleSeparation(otherFish, closeSum);
    actualFish.handleAlignment(otherFish, averageVelocity);
    actualFish.handleCohesion(otherFish, averagePosition);
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
        handleBehaviors(*this, *it, closeSum, averageVelocity, averagePosition, maxDistanceFromCenter);
    }

    // Velocity update
    // Separation
    _mvtVariables.velocity(_mvtVariables.velocity() + closeSum * _bhvVariables.avoidFactor());

    // Alignment and Cohesion
    if (_bhvVariables.neighboringFishes() != 0)
    {
        averageVelocity /= _bhvVariables.neighboringFishes();
        _mvtVariables.velocity(_mvtVariables.velocity() + (averageVelocity - _mvtVariables.velocity()) * _bhvVariables.matchingFactor());
    }

    handleScreenBorders(maxDistanceFromCenter);

    // Min and Max speed
    float speed = std::sqrt(std::pow(_mvtVariables.velocity().x, 2.f) + std::pow(_mvtVariables.velocity().y, 2.f));
    if (speed > _bhvVariables.maxSpeed())
        _mvtVariables.velocity((_mvtVariables.velocity() / speed) * _bhvVariables.maxSpeed());

    if (speed < _bhvVariables.minSpeed())
        _mvtVariables.velocity((_mvtVariables.velocity() / speed) * _bhvVariables.minSpeed());

    // Position update
    _mvtVariables.position(_mvtVariables.position() + (_mvtVariables.velocity() / 10.f));

    _debugUi = DebugUi(_mvtVariables, _bhvVariables, _debugUi);
}

void Fish::drawFish(p6::Context& ctx) const
{
    ctx.push_transform();
    ctx.translate({_mvtVariables.position().x, _mvtVariables.position().y});
    ctx.fill       = {1.f, 0.7f, 0.2f, 1.f};
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
    _bhvVariables.copy(fishTemplate._bhvVariables);
    _debugUi.copyParameters(fishTemplate._debugUi);
}
