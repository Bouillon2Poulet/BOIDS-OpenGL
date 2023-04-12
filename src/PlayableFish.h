#pragma once

#include "Drawing.h"
#include "MovementVariables.h"
#include "glm/ext/quaternion_geometric.hpp"

class PlayableFish {
private:
    MovementVariables _mvtVariables;
    p6::Color         _color  = {1.f, .5f, .5f};
    float             _radius = .05f;

public:
    PlayableFish(glm::vec2 maxDistanceFromCenter)
        : _mvtVariables(maxDistanceFromCenter)
    {
    }
    inline void update(const glm::vec2& mousePosition) // Only take ctx.mouse() as a param
    {
        _mvtVariables._velocity = ((0.08f * (glm::normalize(mousePosition - _mvtVariables._position))) * glm::length(mousePosition - _mvtVariables._position));
        _mvtVariables._position += _mvtVariables._velocity;
    }
    inline void draw(p6::Context& ctx)
    {
        drawFish(ctx, _mvtVariables._position, _color, _radius);
    }
};