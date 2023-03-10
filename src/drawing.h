#ifndef __DRAWING__HPP
#define __DRAWING__HPP

#include <p6/p6.h>
#include <vector>
#include "glm/fwd.hpp"

void drawBoundingBox(p6::Context& ctx, glm::vec2 maxDistanceFromCenter);

#endif