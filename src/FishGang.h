#pragma once

#include <string>
#include "BehaviorVariables.h"
#include "Fish.h"
#include "FishType.h"
#include "FoodKind.h"
#include "Lods.h"
#include "Vertices3D.h"
#include "my3DModel.h"

class FishGang {
private:
    std::vector<Fish> _fishes{};
    BehaviorVariables _bhvVariables{};
    LoDs              _lods;

    FishType _type;
    float    _radius;

public:
    FishGang(const FishType type, const unsigned int number, const glm::vec3& maxDistanceFromCenter, float radius);

    void draw(const myProgram& program, const glm::mat4& projMatrix, const glm::vec3& cameraPosition);
    void update(const glm::vec3& maxDistanceFromCenter, FoodKind& particularFoodKind, const glm::mat4& viewMatrix);

    // GUI
    void GUIdisplayFishGangBehaviorVariables();

    //  Pointeurs
    std::vector<Fish>* fishesPtr();
    BehaviorVariables* bhvVariablesPtr();

    // Getters
    FishType    type();
    std::string name();
};
