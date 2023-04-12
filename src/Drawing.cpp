#include "Drawing.h"
#include "MovementVariables.h"
#include "glm/fwd.hpp"
#include "internal.h"

void drawLinkToNearestFood(p6::Context& ctx, const glm::vec2& fishPosition, const glm::vec2& nearestFoodLocation)
{
    ctx.push_transform();
    ctx.stroke        = {.1f, .5f, 0.f, 1.f};
    ctx.stroke_weight = .001f;
    ctx.use_fill      = false;
    ctx.use_stroke    = true;
    ctx.line(
        fishPosition,
        nearestFoodLocation
    );
    ctx.pop_transform();
}

void drawProtectedCircle(p6::Context& ctx, float protectedRange, const glm::vec2& position)
{
    ctx.push_transform();
    ctx.translate({position.x, position.y});
    ctx.stroke     = {1.f, .0f, .0f, 0.4f};
    ctx.use_fill   = false;
    ctx.use_stroke = true;
    ctx.circle(
        p6::Center{.0f, .0f},
        p6::Radius{protectedRange}
    );
    ctx.pop_transform();
}

void drawVisibleCircle(p6::Context& ctx, float visibleRange, const glm::vec2& position)
{
    ctx.push_transform();
    ctx.translate({position.x, position.y});
    ctx.stroke     = {.0f, .1f, 0.f, 0.4f};
    ctx.use_fill   = false;
    ctx.use_stroke = true;
    ctx.circle(
        p6::Center{.0f, .0f},
        p6::Radius{visibleRange}
    );
    ctx.pop_transform();
}

void drawVelocityVector(p6::Context& ctx, const MovementVariables& mvtVariables)
{
    ctx.push_transform();
    ctx.translate({mvtVariables._position.x, mvtVariables._position.y});
    ctx.stroke        = {.1f, .5f, 0.f, 1.f};
    ctx.stroke_weight = .01f;
    ctx.use_fill      = false;
    ctx.use_stroke    = true;
    ctx.line(
        glm::vec2(.0f, .0f),
        mvtVariables._velocity
    );
    ctx.pop_transform();
}

void drawProximityNbr(unsigned int neighboringFishes, p6::Context& ctx, const glm::vec2& position)
{
    ctx.push_transform();
    ctx.translate({position.x + 0.04f, position.y});
    ctx.stroke                           = {.1f, .5f, 0.f};
    ctx.stroke_weight                    = .01f;
    ctx.use_fill                         = false;
    ctx.use_stroke                       = true;
    const std::u16string proximityNumber = internal::to_u16string(static_cast<int>(neighboringFishes));
    ctx.text(
        proximityNumber,
        p6::Center{},
        p6::Rotation{}
    );
    ctx.pop_transform();
}

void drawFish(p6::Context& ctx, const glm::vec2& position, const p6::Color& color, float radius)
{
    ctx.push_transform();
    ctx.translate({position.x, position.y});
    ctx.fill       = color;
    ctx.use_fill   = true;
    ctx.use_stroke = false;
    ctx.square(
        p6::Center{.0f, .0f},
        p6::Radius{radius}
    );
    ctx.pop_transform();
}