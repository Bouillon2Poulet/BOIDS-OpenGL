#pragma once

#include <p6/p6.h>
#include <vector>
#include "Food.h"
#include "Matrices.h"
#include "MovementVariables.h"
#include "Vertices3D.h"
#include "behaviorVariables.h"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "my3DModel.h"
#include "myProgram.h"

class Fish {
private:
    MovementVariables _mvtVariables;
    Matrices          _matrices;
    glm::vec3         _nearestFoodLocation;

    std::vector<Fish>* _allFishes{};

public:
    // Constructor
    Fish(const glm::vec3& maxDistanceFromCenter, std::vector<Fish>* allFishes);
    void linkArrayToFish(std::vector<Fish>* array);

    void update(BehaviorVariables& bvhVariables, float radius, const glm::vec3& maxDistanceFromCenter, std::vector<Fish>& allFishes, Food* nearestFood, const glm::mat4& viewMatrix);
    void draw(const myProgram& program, const my3DModel& model, const glm::mat4& projMatrix) const;

    // Behaviors
    void handleSeparation(Fish& OtherFish, glm::vec3& closeSum, float protectedRange);
    void handleAlignment(Fish& OtherFish, glm::vec3& averageVelocity, float visibleRange, int& neighboringFishes);
    void handleCohesion(Fish& OtherFish, glm::vec3& averagePosition, float visibleRange);
    void handleScreenBorders(const glm::vec3& maxDistanceFromCenter);
    void handleNearestFoodIfNecessary(Food* nearestFood);

    // Pointeurs
    MovementVariables* mvtVariablesPtr();

    glm::vec3   position() const;
    inline bool operator==(const Fish& other) const;
};
