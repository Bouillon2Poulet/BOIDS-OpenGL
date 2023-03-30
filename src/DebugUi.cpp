#include "DebugUi.h"
#include "DebugUiVariable.h"
#include "MovementVariables.h"
#include "glm/fwd.hpp"
#include "internal.h"

void drawProtectedCircle(p6::Context& ctx, float protectedRange, glm::vec2 position)
{
    std::cout << "??" << protectedRange;
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

void drawVisibleCircle(p6::Context& ctx, float visibleRange, glm::vec2 position)
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

void drawVelocityVector(p6::Context& ctx, MovementVariables mvtVariables)
{
    ctx.push_transform();
    ctx.translate({mvtVariables.position().x, mvtVariables.position().y});
    ctx.stroke        = {.1f, .5f, 0.f, 1.f};
    ctx.stroke_weight = .01f;
    ctx.use_fill      = false;
    ctx.use_stroke    = true;
    ctx.line(
        glm::vec2(.0f, .0f),
        mvtVariables.velocity()
    );
    ctx.pop_transform();
}

void drawProximityNbr(unsigned int neighboringFishes, p6::Context& ctx, glm::vec2 position)
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
