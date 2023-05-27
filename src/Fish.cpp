#include "Fish.h"
#include <cmath>
#include <string>
#include "BehaviorVariables.h"
#include "FishGang.h"
#include "MovementVariables.h"
#include "Vertices3D.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "internal.h"

// Behaviors
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

void Fish::handleScreenBorders(const glm::vec3& maxDistanceFromCenterBig)
{
    const glm::vec3& maxDistanceFromCenter = maxDistanceFromCenterBig;
    glm::vec3        bordersForces{};
    float            rightBorderForce = -1.f / (std::pow(maxDistanceFromCenter.x - _mvtVariables._position.x, 2.f));
    float            leftBorderForce  = 1.f / (std::pow(-maxDistanceFromCenter.x - _mvtVariables._position.x, 2.f));

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
    float biasval = 0.005f;
    if (nearestFood != nullptr)
    {
        _nearestFoodLocation = nearestFood->position();

        _mvtVariables._velocity += biasval * glm::normalize(_nearestFoodLocation - _mvtVariables._position);
        // Food interaction
        if (glm::length(_mvtVariables._position - _nearestFoodLocation) < nearestFood->radius() * 10)
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

//Constructor
Fish::Fish(const glm::vec3& maxDistanceFromCenter, std::vector<Fish>* allFishes)
    : _mvtVariables(maxDistanceFromCenter), _allFishes(allFishes)
{
}

void Fish::update(BehaviorVariables& bhvVariables, const float radius, const glm::vec3& maxDistanceFromCenter, std::vector<Fish>& allFishes, Food* nearestFood, const glm::mat4& viewMatrix)
{
    int       neighboringFishes = 0;
    glm::vec3 closeSum(.0f);        // Separation variable
    glm::vec3 averageVelocity(.0f); // Alignment _bhvVariables
    glm::vec3 averagePosition(.0f); // Cohesion _bhvVariables

    // Behaviors
    handleBehaviorsWithAllFishes(*this, allFishes, bhvVariables, neighboringFishes, closeSum, averageVelocity, averagePosition);
    handleNearestFoodIfNecessary(nearestFood);

    // Update
    _mvtVariables.update(closeSum, averageVelocity, neighboringFishes, bhvVariables, maxDistanceFromCenter);
    _matrices.updateFishOrArpenteur(_mvtVariables._position, radius, _mvtVariables._velocity, viewMatrix);
}

void Fish::draw(const myProgram& program, const my3DModel& model, const glm::mat4& projMatrix) const
{
    _matrices.sendMatricesToShader(program, projMatrix);
    model.draw(program);
}

glm::vec3 Fish::position() const
{
    return _mvtVariables._position;
}

bool Fish::operator==(const Fish& other) const
{
    return this == &other;
}

MovementVariables* Fish::mvtVariablesPtr()
{
    return &_mvtVariables;
}