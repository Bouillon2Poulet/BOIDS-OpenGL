#include "FishTemplate.h"
#include "DebugUiParameters.h"

BehaviorVariables* FishTemplate::bhvVariablesPtr()
{
    return &_bhvVariables;
}

DebugUiParameters* FishTemplate::debugUiParametersPtr()
{
    return &_debugUiParameters;
}