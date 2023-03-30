#include "FishGang.h"
#include "DebugUiParameters.h"

BehaviorVariables* FishGang::bhvVariablesPtr()
{
    return &_bhvVariables;
}

DebugUiParameters* FishGang::debugUiParametersPtr()
{
    return &_debugUiParameters;
}