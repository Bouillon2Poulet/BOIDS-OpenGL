#include "Fish.h"
#include <cmath>
#include <string>
#include "BehaviorVariables.h"
#include "DebugUiParameters.h"
#include "Drawing.h"
#include "FishGang.h"
#include "MovementVariables.h"
#include "Vertices3D.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "internal.h"

void Fish::drawDebugFishIfNecessary(p6::Context& ctx, const DebugUiParameters& debugUiParameters, const BehaviorVariables& behaviorVariables, const glm::mat4& projMatrix) const
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
        drawProximityNbr(_debugUiNeighboringFishes, ctx, (glm::vec4(_mvtVariables._position, 1)) * projMatrix);
}

void Fish::draw(const myProgram& program, const glm::mat4& projMatrix, Vertices3D& vertices, p6::Context& ctx, const DebugUiParameters& debugUiParameters, const BehaviorVariables& behaviorVariables) const
{
    drawDebugFishIfNecessary(ctx, debugUiParameters, behaviorVariables, projMatrix);
    drawFish(program, projMatrix, vertices);
}

void Fish::drawFish(const myProgram& program, const glm::mat4& projMatrix, Vertices3D& vertices) const
{
    // std::cout << _mvtVariables._position.x << "//" << _mvtVariables._position.y << "//" << _mvtVariables._position.z << "\n";
    _matrices.sendMatricesToShader(program, projMatrix);
    // std::cout << vertices.shapeVertices().size() << std::endl;
    glDrawArrays(GL_TRIANGLES, 0, vertices.shapeVertices().size());
    // glBindVertexArray(0);
}

static void handleBehaviors(Fish& actualFish, BehaviorVariables& bhvVariables, Fish& otherFish, glm::vec3& closeSum, glm::vec3& averageVelocity, glm::vec3& averagePosition, int& neighboringFishes)
{
    actualFish.handleSeparation(otherFish, closeSum, bhvVariables._protectedRange);
    actualFish.handleAlignment(otherFish, averageVelocity, bhvVariables._visibleRange, neighboringFishes);
    actualFish.handleCohesion(otherFish, averagePosition, bhvVariables._visibleRange);
}

static void handleBehaviorsWithAllFishes(Fish& actualFish, std::vector<Fish>& allFishes, BehaviorVariables& bhvVariables, int& neighboringFishes, glm::vec3& closeSum, glm::vec3& averageVelocity, glm::vec3& averagePosition)
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

void Fish::update(BehaviorVariables& bhvVariables, const float radius, const glm::vec3& maxDistanceFromCenter, std::vector<Fish>& allFishes, Food* nearestFood, const glm::mat4& viewMatrix)
{
    int       neighboringFishes = 0;
    glm::vec3 closeSum(.0f);        // Separation variable
    glm::vec3 averageVelocity(.0f); // Alignment _bhvVariables
    glm::vec3 averagePosition(.0f); // Cohesion _bhvVariables

    // Behaviors
    handleBehaviorsWithAllFishes(*this, allFishes, bhvVariables, neighboringFishes, closeSum, averageVelocity, averagePosition);
    // std::cout<<"1"<<_mvtVariables._velocity.x<<"/"<<_mvtVariables._velocity.y<<"/"<<_mvtVariables._velocity.z<<std::endl;

    _mvtVariables.update(closeSum, averageVelocity, neighboringFishes, bhvVariables, maxDistanceFromCenter);

    // handleNearestFoodIfNecessary(nearestFood);

    _matrices.update(_mvtVariables._position, radius, _mvtVariables._velocity, viewMatrix);

    _debugUiNeighboringFishes = neighboringFishes;
}

void Fish::handleScreenBorders(const glm::vec3& maxDistanceFromCenterBig)
{
    // std::cout << "1.3 - maxDistanceFromCenter.x : " << maxDistanceFromCenter.x << "\n";
    const glm::vec3& maxDistanceFromCenter = maxDistanceFromCenterBig;
    glm::vec3 bordersForces{};
    float     rightBorderForce = -1.f / (std::pow(maxDistanceFromCenter.x - _mvtVariables._position.x, 2.f));
    float     leftBorderForce  = 1.f / (std::pow(-maxDistanceFromCenter.x - _mvtVariables._position.x, 2.f));

    float topBorderForce = -1.f / ((maxDistanceFromCenter.y - _mvtVariables._position.y) * (maxDistanceFromCenter.y - _mvtVariables._position.y));
    float botBorderForce = 1.f / ((-maxDistanceFromCenter.y - _mvtVariables._position.y) * (-maxDistanceFromCenter.y - _mvtVariables._position.y));

    float frontBorderForce = -1.f / ((maxDistanceFromCenter.z - _mvtVariables._position.z) * (maxDistanceFromCenter.z - _mvtVariables._position.z));
    float backBorderForce  = 1.f / ((-maxDistanceFromCenter.z - _mvtVariables._position.z) * (-maxDistanceFromCenter.z - _mvtVariables._position.z));

    bordersForces.x = rightBorderForce + leftBorderForce;
    bordersForces.y = topBorderForce + botBorderForce;
    bordersForces.z = frontBorderForce + backBorderForce;

    _mvtVariables._velocity += (bordersForces / 10.f);
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

void Fish::handleSeparation(Fish& OtherFish, glm::vec3& closeSum, float protectedRange)
{
    if (glm::length(OtherFish._mvtVariables._position - _mvtVariables._position) <= protectedRange)
    {
        closeSum += (_mvtVariables._position - OtherFish._mvtVariables._position);
    }
}

void Fish::handleAlignment(Fish& OtherFish, glm::vec3& averageVelocity, float visibleRange, int& neighboringFishes)
{
    if (glm::length(OtherFish._mvtVariables._position - _mvtVariables._position) <= visibleRange)
    {
        averageVelocity += OtherFish._mvtVariables._velocity;
        neighboringFishes++;
    }
}

void Fish::handleCohesion(Fish& OtherFish, glm::vec3& averagePosition, float visibleRange)
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