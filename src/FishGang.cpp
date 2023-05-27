#include "FishGang.h"
#include "FoodKind.h"
#include "glm/fwd.hpp"
#include "my3DModel.h"

FishGang::FishGang(const FishType type, const unsigned int number, const glm::vec3& maxDistanceFromCenter, float radius)
    : _bhvVariables(type), _type(type), /*_model(fishTypeToString(type))*/ _lods(fishTypeToString(type)), _radius(radius)
{
    for (unsigned int i = 0; i < number; i++)
    {
        _fishes.emplace_back(maxDistanceFromCenter, &_fishes);
    }
};

void FishGang::draw(const myProgram& program, const glm::mat4& projMatrix, const glm::vec3& arpenteurPosition)
{
    _lods.getRightModel(4).activateTexture(program);

    for (const auto& fish : _fishes)
    {
        fish.draw(program, _lods.getRightModel(glm::length(fish.position() - arpenteurPosition)), projMatrix);
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

void FishGang::GUIdisplayFishGangBehaviorVariables()
{
    ImGui::SliderFloat("Protected range", &(_bhvVariables._protectedRange), 0.f, 1.f);
    ImGui::SliderFloat("Visible range", &(_bhvVariables._visibleRange), 0.f, 1.f);
    ImGui::SliderFloat("Avoid factor", &(_bhvVariables._avoidFactor), 0.f, 1.f);
    ImGui::SliderFloat("Matching factor", &(_bhvVariables._matchingFactor), 0.f, 1.f);
    ImGui::SliderFloat("Centering factor", &(_bhvVariables._centeringFactor), 0.f, 1.f);
    ImGui::SliderFloat("Turn factor", &(_bhvVariables._turnFactor), 0.f, 1.f);
    ImGui::SliderFloat("Max speed", &(_bhvVariables._maxSpeed), 0.f, 5.f);
    ImGui::SliderFloat("Min speed", &(_bhvVariables._minSpeed), 0.f, 2.f);
}

BehaviorVariables* FishGang::bhvVariablesPtr()
{
    return &_bhvVariables;
}

FishType FishGang::type()
{
    return _type;
}

std::string FishGang::name()
{
    return fishTypeToString(_type);
}