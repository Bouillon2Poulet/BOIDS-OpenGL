#pragma once

#include "Food.h"
#include "myProgram.h"
#include "Vertices3D.h"
#include "glm/gtc/type_ptr.hpp"
#pragma once

#include <p6/p6.h>
#include <vector>
#include "DebugUiParameters.h"
#include "Matrices.h"
#include "MovementVariables.h"
#include "behaviorVariables.h"
#include "glm/fwd.hpp"

class Fish {
private:
    MovementVariables _mvtVariables;
    Matrices          _matrices;
    glm::vec3         _nearestFoodLocation;
    unsigned int      _debugUiNeighboringFishes = 0;

    std::vector<Fish>* _allFishes{};

public:
    Fish(const glm::vec3& maxDistanceFromCenter, std::vector<Fish>* allFishes)
        : _mvtVariables(maxDistanceFromCenter), _allFishes(allFishes)
    {
    }

    bool operator==(const Fish& other) const
    {
        return this == &other;
    }
    void draw(const myProgram& program, const glm::mat4& projMatrix, Vertices3D& vertices, p6::Context& ctx, const DebugUiParameters& debugUiParameters, const BehaviorVariables& behaviorVariables) const;

    void drawFish(const myProgram& program, const glm::mat4& projMatrix, Vertices3D& vertices) const;
    void drawDebugFishIfNecessary(p6::Context& ctx, const DebugUiParameters& debugUiParameters, const BehaviorVariables& behaviorVariables, const glm::mat4& projMatrix) const;

    void update(BehaviorVariables& bvhVariables, float radius, const glm::vec3& maxDistanceFromCenter, std::vector<Fish>& allFishes, Food* nearestFood, const glm::mat4& viewMatrix);

    void linkArrayToFish(std::vector<Fish>* array);

    void handleSeparation(Fish& OtherFish, glm::vec3& closeSum, float protectedRange);

    void handleAlignment(Fish& OtherFish, glm::vec3& averageVelocity, float visibleRange, int& neighboringFishes);

    void handleCohesion(Fish& OtherFish, glm::vec3& averagePosition, float visibleRange);

    void handleScreenBorders(const glm::vec3& maxDistanceFromCenter);

    void handleNearestFoodIfNecessary(Food* nearestFood);

    unsigned int* neighboringFishesPtr();

    // void               variables(BehaviorVariables input);
    BehaviorVariables* bhvVariablesPtr();
    MovementVariables* mvtVariablesPtr();

    // DebugUi* debugUiPtr();
};
