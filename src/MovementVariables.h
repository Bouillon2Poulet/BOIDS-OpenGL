#pragma once

#include <p6/p6.h>
#include "BehaviorVariables.h"
#include "glm/fwd.hpp"
#include "internal.h"

struct MovementVariables {
    glm::vec3 _position{};
    glm::vec3 _velocity{};

    inline explicit MovementVariables(const glm::vec3& maxDistanceFromCenter = glm::vec3())
        : _position((maxDistanceFromCenter == glm::vec3()) ? glm::vec3() : internal::randomPosInBoundingBox(maxDistanceFromCenter)), _velocity(glm::vec3(p6::random::number(.2f) - .1f, p6::random::number(.2f) - .1f, p6::random::number(.2f) - .1f))
    {
        std::cout << "!!" << _velocity.x << "/" << _velocity.y << "/" << _velocity.z << std::endl;
    }

    inline void update(const glm::vec3& closeSum, glm::vec3& averageVelocity, const unsigned int neighboringFishes, const BehaviorVariables& bhvVariables, const glm::vec3& maxDistanceFromCenter)
    {
        velocityUpdate(closeSum, averageVelocity, neighboringFishes, bhvVariables._avoidFactor, bhvVariables._matchingFactor);
        handleScreenBorders(maxDistanceFromCenter);
        handleSpeedLimit(bhvVariables._minSpeed, bhvVariables._maxSpeed);
        _position += (_velocity / 10.f);
        handleOutOfBorders(maxDistanceFromCenter / 2.f);
    }

    inline void velocityUpdate(const glm::vec3& closeSum, glm::vec3& averageVelocity, const unsigned int neighboringFishes, const float avoidFactor, const float matchingFactor)
    {
        _velocity += closeSum * avoidFactor;
        // std::cout << "3" << _velocity.x << "/" << _velocity.y << "/" << _velocity.z << std::endl;

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
        if (speed != 0.f)
        {
            if (speed > maxSpeed)
                _velocity = ((_velocity / speed) * maxSpeed);

            if (speed < minSpeed)
                _velocity = (_velocity / speed) * minSpeed;
        }
    }

    inline void handleScreenBorders(const glm::vec3& maxDistanceFromCenterBig)
    {
        const glm::vec3 maxDistanceFromCenter = maxDistanceFromCenterBig / 2.f;
        float           xForce                = -1.f * internal::sign(_position.x) / (std::pow(maxDistanceFromCenter.x - std::abs(_position.x), 2.f));
        float           yForce                = -1.f * internal::sign(_position.y) / (std::pow(maxDistanceFromCenter.y - std::abs(_position.y), 2.f));
        float           zForce                = -1.f * internal::sign(_position.z) / (std::pow(maxDistanceFromCenter.z - std::abs(_position.z), 2.f));

        glm::vec3 bordersForces = {xForce, yForce, zForce};
        _velocity += (bordersForces / 1000.f);
    }

    void handleOutOfBorders(const glm::vec3& maxDistanceFromCenter)
    {
        if (std::abs(_position.x) > maxDistanceFromCenter.x)
            _position = internal::randomPosInBoundingBox(maxDistanceFromCenter);
        if (std::abs(_position.y) > maxDistanceFromCenter.y)
            _position = internal::randomPosInBoundingBox(maxDistanceFromCenter);
        if (std::abs(_position.z) > maxDistanceFromCenter.z)
            _position = internal::randomPosInBoundingBox(maxDistanceFromCenter);
    }
};
