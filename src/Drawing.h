#pragma once

#include <p6/p6.h>
#include "MovementVariables.h"
#include "glm/fwd.hpp"

void drawLinkToNearestFood(p6::Context& ctx, const glm::vec2& fishPosition, const glm::vec2& nearestFoodLocation);
void drawProtectedCircle(p6::Context& ctx, float protectedRange, const glm::vec2& mvtVariables);
void drawVisibleCircle(p6::Context& ctx, float visibleRange, const glm::vec2& position);
void drawVelocityVector(p6::Context& ctx, const MovementVariables& mvtVariables);
void drawProximityNbr(unsigned int neighboringFishes, p6::Context& ctx, const glm::vec2& position);
void drawFish(p6::Context& ctx, const glm::vec2& position, const p6::Color& color, float radius);