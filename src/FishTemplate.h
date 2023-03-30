#pragma once

#include "BehaviorVariables.h"
#include "DebugUi.h"

class FishTemplate {
private:
    BehaviorVariables _bhvVariables{};
    DebugUi           _debugUi;

public:
    FishTemplate() = default;
    BehaviorVariables* bhvVariablesPtr();
    DebugUi*           debugUiPtr();
};