#include "drawing.h"

void drawBoundingBox(p6::Context& ctx, glm::vec2 maxDistanceFromCenter)
{
    // Bounding box
    ctx.push_transform();
    ctx.use_fill   = false;
    ctx.use_stroke = true;
    ctx.stroke     = p6::Color{1.f, 0.f, 0.f};
    ctx.rectangle(
        p6::Center{.0f, .0f},
        p6::Radii{maxDistanceFromCenter.x, maxDistanceFromCenter.y},
        p6::Rotation{}
    );
    ctx.pop_transform();
}