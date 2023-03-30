
#pragma once

#include <p6/p6.h>
#include "MovementVariables.h"
#include "behaviorVariables.h"

class DebugUiVariables {
    glm::vec2 _position;
    glm::vec2 _velocity;
    float     _protectedRange;
    float     _visibleRange;

public:
    DebugUiVariables()                               = default;
    DebugUiVariables(const DebugUiVariables& toCopy) = default;

    void operator()(const DebugUiVariables& toCopy);

    DebugUiVariables(MovementVariables& mvtToCopy, BehaviorVariables& bhvToCopy);

    glm::vec2 position() const;

    glm::vec2 velocity() const;

    float protectedRange() const;

    float visibleRange() const;

    unsigned int neighboringFishes() const;
};