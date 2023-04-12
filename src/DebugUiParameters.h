#pragma once

#include <p6/p6.h>
#include "imgui.h"

struct DebugUiParameters {
    bool _displayProtectedRange    = false;
    bool _displayVisibleRange      = false;
    bool _displayVelocityVector    = false;
    bool _displayProximityNbr      = false;
    bool _displayLinkToNearestFood = false;
};
