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

void FishGang::draw(p6::Context& ctx, const Program& program, const glm::mat4& projMatrix)
{
    int count = 0;
    for (const auto& fish : _fishes)
    {
        // std::cout << _vertices3D.vao() << "\n";
        // count++;
        _vertices3D.bindVertexArrayVAO();
        // std::cout << _vertices3D.size() << std::endl;
        fish.draw(program, projMatrix, _vertices3D, ctx, _debugUiParameters, _bhvVariables);
        glBindVertexArray(0);
    }
}

void FishGang::update(const glm::vec3& maxDistanceFromCenter, FoodKind& particularFoodKind, const glm::mat4& viewMatrix)
{
    for (auto& fish : _fishes)
    {
        fish.update(_bhvVariables, _radius, maxDistanceFromCenter, _fishes, (particularFoodKind.nearestFood(fish.mvtVariablesPtr()->_position)), viewMatrix);
    }
}
