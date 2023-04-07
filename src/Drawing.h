#pragma once

#include <p6/p6.h>
#include "MovementVariables.h"
#include "glm/fwd.hpp"

void drawLinkToNearestFood(p6::Context& ctx, glm::vec2 fishPosition, glm::vec2 nearestFoodLocation);
void drawProtectedCircle(p6::Context& ctx, float protectedRange, glm::vec2 mvtVariables);
void drawVisibleCircle(p6::Context& ctx, float visibleRange, glm::vec2 position);
void drawVelocityVector(p6::Context& ctx, MovementVariables mvtVariables);
void drawProximityNbr(unsigned int neighboringFishes, p6::Context& ctx, glm::vec2 position);
void drawFish(p6::Context& ctx, glm::vec2 position, p6::Color& color, float radius);