#include "FishGang.h"
#include "DebugUiParameters.h"
#include "FoodKind.h"
#include "glm/fwd.hpp"

BehaviorVariables* FishGang::bhvVariablesPtr()
{
    return &_bhvVariables;
}

DebugUiParameters* FishGang::debugUiParametersPtr()
{
    return &_debugUiParameters;
}

void FishGang::draw(p6::Context& ctx)
{
    std::vector<Fish>::iterator it;

    for (it = _fishes.begin(); it != _fishes.end(); it++)
    {
        it->draw(ctx, _debugUiParameters, _bhvVariables, _color, _radius);
    }
}

void FishGang::update(glm::vec2 maxDistanceFromCenter, FoodKind& particularFoodKind)
{
    for (auto it = _fishes.begin(); it != _fishes.end(); it++)
    {
        glm::vec2 position = (it->mvtVariablesPtr()->position());
        it->update(_bhvVariables, maxDistanceFromCenter, _fishes, *(particularFoodKind.nearestFood(position)));
    }
}
