#ifndef __MOVEMENTVARIABLES__HPP
#define __MOVEMENTVARIABLES__HPP

#include <p6/p6.h>
#include "glm/fwd.hpp"

class MovementVariables {
private:
    glm::vec2 _position{};
    glm::vec2 _velocity{};

public:
    inline explicit MovementVariables(glm::vec2& maxDistanceFromCenter)
        : _position(randomPosInBoundingBox(maxDistanceFromCenter)), _velocity(glm::vec2(p6::random::number(.2f) - .1f, p6::random::number(.2f) - .1f))
    {}

    inline MovementVariables(MovementVariables& toCopy) = default;

    inline void copy(MovementVariables& toCopy)
    {
        _position = toCopy._position;
        _velocity = toCopy._velocity;
    }
    static glm::vec2 randomPosInBoundingBox(glm::vec2 radii);

    void       position(glm::vec2 input);
    glm::vec2  position() const;
    glm::vec2* positionPtr();

    void       velocity(glm::vec2 input);
    glm::vec2  velocity() const;
    glm::vec2* velocityPtr();
};

#endif
