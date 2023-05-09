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

void FishGang::draw(p6::Context& ctx, const myProgram& program, const glm::mat4& projMatrix)
{
    int count = 0;
    _model.activateTexture(program);

    for (const auto& fish : _fishes)
    {
        fish.draw(program, _model, projMatrix, ctx, _debugUiParameters, _bhvVariables);
        // glBindVertexArray(0);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FishGang::update(const glm::vec3& maxDistanceFromCenter, FoodKind& particularFoodKind, const glm::mat4& viewMatrix)
{
    for (auto& fish : _fishes)
    {
        fish.update(_bhvVariables, _radius, maxDistanceFromCenter, _fishes, (particularFoodKind.nearestFood(fish.mvtVariablesPtr()->_position)), viewMatrix);
    }
}
