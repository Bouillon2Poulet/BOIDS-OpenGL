#include "DebugUi.h"
#include "internal.h"

void DebugUi::drawProtectedCircle(p6::Context& ctx) const
{
    ctx.push_transform();
    ctx.translate({_variables.position().x, _variables.position().x});
    ctx.stroke     = {1.f, .0f, .0f};
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
    ctx.stroke     = {.0f, .1f, 0.f};
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
    ctx.stroke        = {.1f, .5f, 0.f};
    ctx.stroke_weight = .01f;
    ctx.use_fill      = false;
    ctx.use_stroke    = true;
    ctx.line(
        glm::vec2(.0f, .0f),
        _variables.velocity()
    );
    ctx.pop_transform();
}

void DebugUi::drawProximityNbr(p6::Context& ctx) const
{
    ctx.push_transform();
    ctx.translate({_variables.position().x, _variables.position().y});
    ctx.stroke                           = {.1f, .5f, 0.f};
    ctx.stroke_weight                    = .01f;
    ctx.use_fill                         = false;
    ctx.use_stroke                       = true;
    const std::u16string proximityNumber = internal::to_u16string(static_cast<int>(_variables.neighboringFishes()));
    ctx.text(
        proximityNumber,
        p6::Center{},
        p6::Rotation{}
    );
    ctx.pop_transform();
}