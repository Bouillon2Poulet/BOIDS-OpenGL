#include "Fish.h"
#include <cmath>
#include <string>
#include "BehaviorVariables.h"
#include "DebugUiParameters.h"
#include "Drawing.h"
#include "FishGang.h"
#include "MovementVariables.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "internal.h"

void Fish::draw(p6::Context& ctx, DebugUiParameters& debugUiParameters, BehaviorVariables& behaviorVariables, p6::Color& color, float radius) const
{
    if (debugUiParameters.displayLinkToNearestFood())
        drawLinkToNearestFood(ctx, _mvtVariables.position(), _nearestFoodLocation);
    if (debugUiParameters.displayProtectedRange())
        drawProtectedCircle(ctx, behaviorVariables.protectedRange(), _mvtVariables.position());
    if (debugUiParameters.displayVisibleRange())
        drawVisibleCircle(ctx, behaviorVariables.visibleRange(), _mvtVariables.position());
    if (debugUiParameters.displayVelocityVector())
        drawVelocityVector(ctx, _mvtVariables);
    if (debugUiParameters.displayProximityNbr())
        drawProximityNbr(_neighboringFishes, ctx, _mvtVariables.position());

    drawFish(ctx, _mvtVariables.position(), color, radius);
}

static void handleBehaviors(Fish& actualFish, BehaviorVariables& bhvVariables, Fish& otherFish, glm::vec2& closeSum, glm::vec2& averageVelocity, glm::vec2& averagePosition)
{
    actualFish.handleSeparation(otherFish, closeSum, bhvVariables.protectedRange());
    actualFish.handleAlignment(otherFish, averageVelocity, bhvVariables.visibleRange());
    actualFish.handleCohesion(otherFish, averagePosition, bhvVariables.visibleRange());
}

void Fish::update(BehaviorVariables& bhvVariables, glm::vec2& maxDistanceFromCenter, std::vector<Fish>& allFishes, Food& nearestFood)
{
    neighboringFishesReset();

    // Separation variable
    glm::vec2 closeSum(.0f, .0f);

    // Alignment _bhvVariables
    glm::vec2 averageVelocity(.0f, .0f);

    // Cohesion _bhvVariables
    glm::vec2 averagePosition(.0f, .0f);
    // Behaviors
    std::vector<Fish>::iterator it;
    for (it = allFishes.begin(); it != allFishes.end(); it++)
    {
        if (&(*it) == this)
        {
            continue;
        }
        handleBehaviors(*this, bhvVariables, *it, closeSum, averageVelocity, averagePosition);
    }

    // Velocity update
    // Separation
    _mvtVariables.velocity(_mvtVariables.velocity() + closeSum * bhvVariables.avoidFactor());

    // Alignment and Cohesion
    if (neighboringFishes() != 0)
    {
        averageVelocity /= neighboringFishes();
        _mvtVariables.velocity(_mvtVariables.velocity() + (averageVelocity - _mvtVariables.velocity()) * bhvVariables.matchingFactor());
    }

    handleScreenBorders(maxDistanceFromCenter);

    // Min and Max speed
    float speed = std::sqrt(std::pow(_mvtVariables.velocity().x, 2.f) + std::pow(_mvtVariables.velocity().y, 2.f));
    if (speed > bhvVariables.maxSpeed())
        _mvtVariables.velocity((_mvtVariables.velocity() / speed) * bhvVariables.maxSpeed());

    if (speed < bhvVariables.minSpeed())
        _mvtVariables.velocity((_mvtVariables.velocity() / speed) * bhvVariables.minSpeed());

    // Position update
    _mvtVariables.position(_mvtVariables.position() + (_mvtVariables.velocity() / 10.f));

    float biasval        = 0.001f;
    _nearestFoodLocation = nearestFood.position();
    _mvtVariables.velocity(_mvtVariables.velocity() + biasval * glm::normalize(_nearestFoodLocation - _mvtVariables.position()));
    // Food interaction
    if (glm::length(_mvtVariables.position() - _nearestFoodLocation) < nearestFood.radius())
        nearestFood.isEaten();
}

// void Fish::drawFish(p6::Context& ctx, p6::Color& color, float radius) const
// {
//     ctx.push_transform();
//     ctx.translate({_mvtVariables.position().x, _mvtVariables.position().y});
//     ctx.fill       = color;
//     ctx.use_fill   = true;
//     ctx.use_stroke = false;
//     ctx.square(
//         p6::Center{.0f, .0f},
//         p6::Radius{radius}
//     );
//     ctx.pop_transform();
// }

void Fish::handleSeparation(Fish& OtherFish, glm::vec2& closeSum, float protectedRange)
{
    if (glm::length(OtherFish._mvtVariables.position() - _mvtVariables.position()) <= protectedRange)
    {
        // std::cout << "! - " << protectedRange << "\n"
        //    << std::endl;
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
    // std::cout << "1.3 - maxDistanceFromCenter.x : " << maxDistanceFromCenter.x << "\n";
    glm::vec2 bordersForces{};
    float     rightBorderForce = -1.f / (std::pow(maxDistanceFromCenter.x - _mvtVariables.position().x, 2.f));
    float     leftBorderForce  = 1.f / (std::pow(-maxDistanceFromCenter.x - _mvtVariables.position().x, 2.f));

    float topBorderForce = -1.f / ((maxDistanceFromCenter.y - _mvtVariables.position().y) * (maxDistanceFromCenter.y - _mvtVariables.position().y));
    float botBorderForce = 1.f / ((-maxDistanceFromCenter.y - _mvtVariables.position().y) * (-maxDistanceFromCenter.y - _mvtVariables.position().y));

    bordersForces.x = rightBorderForce + leftBorderForce;
    bordersForces.y = topBorderForce + botBorderForce;

    _mvtVariables.velocity(_mvtVariables.velocity() + (bordersForces / 10000.f));
}

// void Fish::transferTemplateArguments(FishGang& fishTemplate)
// {
//     _debugUi.copyParameters(fishTemplate.debugUiPtr());
// }

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

MovementVariables* Fish::mvtVariablesPtr()
{
    return &_mvtVariables;
}