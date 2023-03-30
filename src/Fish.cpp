#include "Fish.h"
#include <cmath>
#include <string>
#include "FishTemplate.h"
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
        _debugUi.drawProximityNbr(_neighboringFishes, ctx);
    drawFish(ctx);
}

static void handleBehaviors(Fish& actualFish, FishTemplate& fishTemplate, Fish& otherFish, glm::vec2 closeSum, glm::vec2& averageVelocity, glm::vec2& averagePosition, glm::vec2& maxDistanceFromCenter)
{
    actualFish.handleSeparation(otherFish, closeSum, fishTemplate.bhvVariablesPtr()->protectedRange());
    actualFish.handleAlignment(otherFish, averageVelocity, fishTemplate.bhvVariablesPtr()->visibleRange());
    actualFish.handleCohesion(otherFish, averagePosition, fishTemplate.bhvVariablesPtr()->visibleRange());
}

void Fish::update(FishTemplate& fishTemplate, float aspect_ratio, glm::vec2& maxDistanceFromCenter)
{
    screenAspectRatio(aspect_ratio);
    neighboringFishesReset();

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
        handleBehaviors(*this, fishTemplate, *it, closeSum, averageVelocity, averagePosition, maxDistanceFromCenter);
    }

    // Velocity update
    // Separation
    _mvtVariables.velocity(_mvtVariables.velocity() + closeSum * fishTemplate.bhvVariablesPtr()->avoidFactor());

    // Alignment and Cohesion
    if (neighboringFishes() != 0)
    {
        averageVelocity /= neighboringFishes();
        _mvtVariables.velocity(_mvtVariables.velocity() + (averageVelocity - _mvtVariables.velocity()) * fishTemplate.bhvVariablesPtr()->matchingFactor());
    }

    handleScreenBorders(maxDistanceFromCenter);

    // Min and Max speed
    float speed = std::sqrt(std::pow(_mvtVariables.velocity().x, 2.f) + std::pow(_mvtVariables.velocity().y, 2.f));
    if (speed > fishTemplate.bhvVariablesPtr()->maxSpeed())
        _mvtVariables.velocity((_mvtVariables.velocity() / speed) * fishTemplate.bhvVariablesPtr()->maxSpeed());

    if (speed < fishTemplate.bhvVariablesPtr()->minSpeed())
        _mvtVariables.velocity((_mvtVariables.velocity() / speed) * fishTemplate.bhvVariablesPtr()->minSpeed());

    // Position update
    _mvtVariables.position(_mvtVariables.position() + (_mvtVariables.velocity() / 10.f));

    _debugUi = DebugUi(_mvtVariables, *(fishTemplate.bhvVariablesPtr()), _debugUi);
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

void Fish::handleSeparation(Fish& OtherFish, glm::vec2& closeSum, float protectedRange)
{
    if (glm::length(OtherFish._mvtVariables.position() - _mvtVariables.position()) <= protectedRange)
    {
        //std::cout << "! - " << protectedRange << "\n"
                //   << std::endl;
        closeSum += (_mvtVariables.position() - OtherFish._mvtVariables.position());
    }
}

void Fish::handleAlignment(Fish& OtherFish, glm::vec2& averageVelocity, float visibleRange)
{
    if (glm::length(OtherFish._mvtVariables.position() - _mvtVariables.position()) <= visibleRange)
    {
        averageVelocity += OtherFish._mvtVariables.velocity();
        neighboringFishesIncrement();
    }
}

void Fish::handleCohesion(Fish& OtherFish, glm::vec2& averagePosition, float visibleRange)
{
    if (glm::length(OtherFish._mvtVariables.position() - _mvtVariables.position()) <= visibleRange)
    {
        averagePosition += OtherFish._mvtVariables.position();
    }
}

void Fish::handleScreenBorders(glm::vec2& maxDistanceFromCenter)
{
    std::cout << "1.3 - maxDistanceFromCenter.x : " << maxDistanceFromCenter.x << "\n";
    glm::vec2 bordersForces{};
    float     rightBorderForce = -1.f / (std::pow(maxDistanceFromCenter.x - _mvtVariables.position().x, 2.f));
    float     leftBorderForce  = 1.f / (std::pow(-maxDistanceFromCenter.x - _mvtVariables.position().x, 2.f));

    float topBorderForce = -1.f / ((maxDistanceFromCenter.y - _mvtVariables.position().y) * (maxDistanceFromCenter.y - _mvtVariables.position().y));
    float botBorderForce = 1.f / ((-maxDistanceFromCenter.y - _mvtVariables.position().y) * (-maxDistanceFromCenter.y - _mvtVariables.position().y));

    bordersForces.x = rightBorderForce + leftBorderForce;
    bordersForces.y = topBorderForce + botBorderForce;

    _mvtVariables.velocity(_mvtVariables.velocity() + (bordersForces / 10000.f));
}

void Fish::transferTemplateArguments(FishTemplate& fishTemplate)
{
    _debugUi.copyParameters(fishTemplate.debugUiPtr());
}

void Fish::neighboringFishesReset()
{
    _neighboringFishes = 0;
}
void Fish::neighboringFishesIncrement()
{
    _neighboringFishes += 1;
}
unsigned int Fish::neighboringFishes() const
{
    return _neighboringFishes;
}
unsigned int* Fish::neighboringFishesPtr()
{
    return &_neighboringFishes;
}