#include "DebugUi.h"
#include "internal.h"

void DebugUi::drawProtectedCircle(p6::Context& ctx) const
{
    ctx.push_transform();
    ctx.translate({_variables.position().x, _variables.position().y});
    ctx.stroke     = {1.f, .0f, .0f, 0.4f};
    ctx.use_fill   = false;
    ctx.use_stroke = true;
    ctx.circle(
        p6::Center{.0f, .0f},
        p6::Radius{_variables.protectedRange()}
    );
    ctx.pop_transform();
}

void DebugUi::drawVisibleCircle(p6::Context& ctx) const
{
    ctx.push_transform();
    ctx.translate({_variables.position().x, _variables.position().y});
    ctx.stroke     = {.0f, .1f, 0.f, 0.4f};
    ctx.use_fill   = false;
    ctx.use_stroke = true;
    ctx.circle(
        p6::Center{.0f, .0f},
        p6::Radius{_variables.visibleRange()}
    );
    ctx.pop_transform();
}

void DebugUi::drawVelocityVector(p6::Context& ctx) const
{
    ctx.push_transform();
    ctx.translate({_variables.position().x, _variables.position().y});
    ctx.stroke        = {.1f, .5f, 0.f, 1.f};
    ctx.stroke_weight = .01f;
    ctx.use_fill      = false;
    ctx.use_stroke    = true;
    ctx.line(
        glm::vec2(.0f, .0f),
        _variables.velocity()
    );
    ctx.pop_transform();
}

void DebugUi::drawProximityNbr(unsigned int neighboringFishes, p6::Context& ctx) const
{
    ctx.push_transform();
    ctx.translate({_variables.position().x + 0.04f, _variables.position().y});
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
