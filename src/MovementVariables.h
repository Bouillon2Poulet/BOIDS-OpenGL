#pragma once

#include <p6/p6.h>
#include "BehaviorVariables.h"
#include "glm/fwd.hpp"
#include "internal.h"

struct MovementVariables {
    glm::vec3 _position{};
    glm::vec3 _velocity{};

    explicit MovementVariables(const glm::vec3& maxDistanceFromCenter = glm::vec3());

    void update(const glm::vec3& closeSum, glm::vec3& averageVelocity, const unsigned int neighboringFishes, const BehaviorVariables& bhvVariables, const glm::vec3& maxDistanceFromCenter);
    void velocityUpdate(const glm::vec3& closeSum, glm::vec3& averageVelocity, const unsigned int neighboringFishes, const float avoidFactor, const float matchingFactor);
    
    void handleTurningForce(const glm::vec3& lastVelocity);
    void handleSpeedLimit(const float minSpeed, const float maxSpeed);
    void handleScreenBorders(const glm::vec3& maxDistanceFromCenterBig);

    void handleOutOfBorders(const glm::vec3& maxDistanceFromCenter);
};
