#pragma once

#include <p6/p6.h>
#include "BehaviorVariables.h"
#include "glm/fwd.hpp"
#include "internal.h"

struct MovementVariables {
    glm::vec3 _position{};
    glm::vec3 _velocity{};

    inline explicit MovementVariables(const glm::vec3& maxDistanceFromCenter)
        : _position(internal::randomPosInBoundingBox(maxDistanceFromCenter))
        , _velocity(glm::vec3(p6::random::number(.2f) - .1f, p6::random::number(.2f) - .1f, p6::random::number(.2f) - .1f))
    {
    }

    inline void update(const glm::vec3& closeSum, glm::vec3& averageVelocity, const unsigned int neighboringFishes, const BehaviorVariables& bhvVariables, const glm::vec3& maxDistanceFromCenter)
    {
        velocityUpdate(closeSum, averageVelocity, neighboringFishes, bhvVariables._avoidFactor, bhvVariables._matchingFactor);
        handleScreenBorders(maxDistanceFromCenter);
        handleSpeedLimit(bhvVariables._minSpeed, bhvVariables._maxSpeed);
        _position += (_velocity / 10.f);
    }

    inline void velocityUpdate(const glm::vec3& closeSum, glm::vec3& averageVelocity, const unsigned int neighboringFishes, const float avoidFactor, const float matchingFactor)
    {
        _velocity += closeSum * avoidFactor;
        if (neighboringFishes != 0)
        {
            averageVelocity /= neighboringFishes;
            _velocity += (averageVelocity - _velocity) * matchingFactor;
        }
    }

    inline void handleSpeedLimit(const float minSpeed, const float maxSpeed)
    {
        // Min and Max speed
        float speed = std::cbrtf(std::pow(_velocity.x, 3.f) + std::pow(_velocity.y, 2.f) + std::pow(_velocity.z, 2.f));
        if (speed > maxSpeed)
            _velocity = ((_velocity / speed) * maxSpeed);

        if (speed < minSpeed)
            _velocity = (_velocity / speed) * minSpeed;
    }

    inline void handleScreenBorders(const glm::vec3& maxDistanceFromCenter)
    {
        // std::cout << "1.3 - maxDistanceFromCenter.x : " << maxDistanceFromCenter.x << "\n";
        glm::vec3 bordersForces{};
        float     rightBorderForce = -1.f / (std::pow(maxDistanceFromCenter.x - _position.x, 2.f));
        float     leftBorderForce  = 1.f / (std::pow(-maxDistanceFromCenter.x - _position.x, 2.f));

        float topBorderForce = -1.f / ((maxDistanceFromCenter.y - _position.y) * (maxDistanceFromCenter.y - _position.y));
        float botBorderForce = 1.f / ((-maxDistanceFromCenter.y - _position.y) * (-maxDistanceFromCenter.y - _position.y));

        float frontBorderForce = -1.f / ((maxDistanceFromCenter.z - _position.z) * (maxDistanceFromCenter.z - _position.z));
        float backBorderForce  = 1.f / ((-maxDistanceFromCenter.z - _position.z) * (-maxDistanceFromCenter.z - _position.z));

        bordersForces.x = rightBorderForce + leftBorderForce;
        bordersForces.y = topBorderForce + botBorderForce;
        bordersForces.z = frontBorderForce + backBorderForce;

        _velocity += (bordersForces / 10000.f);
    }
};
