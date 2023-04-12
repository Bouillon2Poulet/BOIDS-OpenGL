#pragma once

#include <p6/p6.h>
#include "BehaviorVariables.h"
#include "internal.h"

struct MovementVariables {
    glm::vec2 _position{};
    glm::vec2 _velocity{};

    inline explicit MovementVariables(glm::vec2& maxDistanceFromCenter)
        : _position(internal::randomPosInBoundingBox(maxDistanceFromCenter))
        , _velocity(glm::vec2(p6::random::number(.2f) - .1f, p6::random::number(.2f) - .1f))
    {
    }

    inline void update(const glm::vec2& closeSum, glm::vec2 averageVelocity, const unsigned int neighboringFishes, const BehaviorVariables& bhvVariables, const glm::vec2& maxDistanceFromCenter)
    {
        velocityUpdate(closeSum, averageVelocity, neighboringFishes, bhvVariables._avoidFactor, bhvVariables._matchingFactor);
        handleScreenBorders(maxDistanceFromCenter);
        handleSpeedLimit(bhvVariables._minSpeed, bhvVariables._maxSpeed);
        _position += (_velocity / 10.f);
    }

    inline void velocityUpdate(const glm::vec2& closeSum, glm::vec2 averageVelocity, const unsigned int neighboringFishes, const float avoidFactor, const float matchingFactor)
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
        float speed = std::sqrt(std::pow(_velocity.x, 2.f) + std::pow(_velocity.y, 2.f));
        if (speed > maxSpeed)
            _velocity = ((_velocity / speed) * maxSpeed);

        if (speed < minSpeed)
            _velocity = (_velocity / speed) * minSpeed;
    }

    inline void handleScreenBorders(const glm::vec2& maxDistanceFromCenter)
    {
        // std::cout << "1.3 - maxDistanceFromCenter.x : " << maxDistanceFromCenter.x << "\n";
        glm::vec2 bordersForces{};
        float     rightBorderForce = -1.f / (std::pow(maxDistanceFromCenter.x - _position.x, 2.f));
        float     leftBorderForce  = 1.f / (std::pow(-maxDistanceFromCenter.x - _position.x, 2.f));

        float topBorderForce = -1.f / ((maxDistanceFromCenter.y - _position.y) * (maxDistanceFromCenter.y - _position.y));
        float botBorderForce = 1.f / ((-maxDistanceFromCenter.y - _position.y) * (-maxDistanceFromCenter.y - _position.y));

        bordersForces.x = rightBorderForce + leftBorderForce;
        bordersForces.y = topBorderForce + botBorderForce;

        _velocity += (bordersForces / 10000.f);
    }
};
