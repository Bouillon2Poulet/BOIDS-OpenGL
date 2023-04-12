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

void Fish::drawDebugFishIfNecessary(p6::Context& ctx, const DebugUiParameters& debugUiParameters, const BehaviorVariables& behaviorVariables) const
{
    if (debugUiParameters._displayLinkToNearestFood)
        drawLinkToNearestFood(ctx, _mvtVariables._position, _nearestFoodLocation);
    if (debugUiParameters._displayProtectedRange)
        drawProtectedCircle(ctx, behaviorVariables._protectedRange, _mvtVariables._position);
    if (debugUiParameters._displayVisibleRange)
        drawVisibleCircle(ctx, behaviorVariables._visibleRange, _mvtVariables._position);
    if (debugUiParameters._displayVelocityVector)
        drawVelocityVector(ctx, _mvtVariables);
    if (debugUiParameters._displayProximityNbr)
        drawProximityNbr(_debugUiNeighboringFishes, ctx, _mvtVariables._position);
}

void Fish::draw(p6::Context& ctx, const DebugUiParameters& debugUiParameters, const BehaviorVariables& behaviorVariables, const p6::Color& color, float radius) const
{
    drawDebugFishIfNecessary(ctx, debugUiParameters, behaviorVariables);
    drawFish(ctx, _mvtVariables._position, color, radius);
}

static void handleBehaviors(Fish& actualFish, BehaviorVariables& bhvVariables, Fish& otherFish, glm::vec2& closeSum, glm::vec2& averageVelocity, glm::vec2& averagePosition, int& neighboringFishes)
{
    actualFish.handleSeparation(otherFish, closeSum, bhvVariables._protectedRange);
    actualFish.handleAlignment(otherFish, averageVelocity, bhvVariables._visibleRange, neighboringFishes);
    actualFish.handleCohesion(otherFish, averagePosition, bhvVariables._visibleRange);
}

static void handleBehaviorsWithAllFishes(Fish& actualFish, std::vector<Fish>& allFishes, BehaviorVariables& bhvVariables, int& neighboringFishes, glm::vec2& closeSum, glm::vec2& averageVelocity, glm::vec2& averagePosition)
{
    std::vector<Fish>::iterator it;
    for (it = allFishes.begin(); it != allFishes.end(); it++)
    {
        if ((*it) == actualFish)
        {
            continue;
        }
        handleBehaviors(actualFish, bhvVariables, *it, closeSum, averageVelocity, averagePosition, neighboringFishes);
    }
}

void Fish::update(BehaviorVariables& bhvVariables, glm::vec2& maxDistanceFromCenter, std::vector<Fish>& allFishes, Food* nearestFood)
{
    int       neighboringFishes = 0;
    glm::vec2 closeSum(.0f, .0f);        // Separation variable
    glm::vec2 averageVelocity(.0f, .0f); // Alignment _bhvVariables
    glm::vec2 averagePosition(.0f, .0f); // Cohesion _bhvVariables

    // Behaviors
    handleBehaviorsWithAllFishes(*this, allFishes, bhvVariables, neighboringFishes, closeSum, averageVelocity, averagePosition);

    _mvtVariables.update(closeSum, averageVelocity, neighboringFishes, bhvVariables, maxDistanceFromCenter);

    handleNearestFoodIfNecessary(nearestFood);

    _debugUiNeighboringFishes = neighboringFishes;
}

void Fish::handleNearestFoodIfNecessary(Food* nearestFood)
{
    float biasval = 0.001f;
    if (nearestFood != nullptr)
    {
        _nearestFoodLocation = nearestFood->position();
        _mvtVariables._velocity += biasval * glm::normalize(_nearestFoodLocation - _mvtVariables._position);
        // Food interaction
        if (glm::length(_mvtVariables._position - _nearestFoodLocation) < nearestFood->radius())
            nearestFood->isEaten();
    }
}

void Fish::handleSeparation(Fish& OtherFish, glm::vec2& closeSum, float protectedRange)
{
    if (glm::length(OtherFish._mvtVariables._position - _mvtVariables._position) <= protectedRange)
    {
        closeSum += (_mvtVariables._position - OtherFish._mvtVariables._position);
    }
}

void Fish::handleAlignment(Fish& OtherFish, glm::vec2& averageVelocity, float visibleRange, int& neighboringFishes)
{
    if (glm::length(OtherFish._mvtVariables._position - _mvtVariables._position) <= visibleRange)
    {
        averageVelocity += OtherFish._mvtVariables._velocity;
        neighboringFishes++;
    }
}

void Fish::handleCohesion(Fish& OtherFish, glm::vec2& averagePosition, float visibleRange)
{
    if (glm::length(OtherFish._mvtVariables._position - _mvtVariables._position) <= visibleRange)
    {
        averagePosition += OtherFish._mvtVariables._position;
    }
}

unsigned int* Fish::neighboringFishesPtr()
{
    return &_debugUiNeighboringFishes;
}

MovementVariables* Fish::mvtVariablesPtr()
{
    return &_mvtVariables;
}