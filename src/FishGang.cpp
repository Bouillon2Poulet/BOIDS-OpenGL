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

void FishGang::draw(p6::Context& ctx) const
{
    for (const auto& fish : _fishes)
    {
        fish.draw(ctx, _debugUiParameters, _bhvVariables, _color, _radius);
    }
}

void FishGang::update(glm::vec2 maxDistanceFromCenter, FoodKind& particularFoodKind)
{
    for (auto& fish : _fishes)
    {
        fish.update(_bhvVariables, maxDistanceFromCenter, _fishes, (particularFoodKind.nearestFood(fish.mvtVariablesPtr()->_position)));
    }
}
