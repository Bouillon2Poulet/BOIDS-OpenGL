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

void FishGang::draw(p6::Context& ctx, glm::vec2 maxDistanceFromCenter)
{
    std::vector<Fish>::iterator it;

    for (it = _fishes.begin(); it != _fishes.end(); it++)
    {
        it->draw(ctx, _debugUiParameters, _bhvVariables, _color, _radius);
        it->update(_bhvVariables, maxDistanceFromCenter, _fishes);
        // std::cout << "/"<<_fishGangs[0].debugUiPtr()->variables().protectedRange();
        ;
    }
}