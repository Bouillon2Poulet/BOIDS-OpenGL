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
    inline void update(p6::Context& ctx)
    {
        _mvtVariables.velocity((0.08f * (glm::normalize(ctx.mouse() - _mvtVariables.position()))) * glm::length(ctx.mouse() - _mvtVariables.position()));
        _mvtVariables.position(_mvtVariables.position() + _mvtVariables.velocity());
    }
    inline void draw(p6::Context& ctx)
    {
        drawFish(ctx, _mvtVariables.position(), _color, _radius);
    }
};