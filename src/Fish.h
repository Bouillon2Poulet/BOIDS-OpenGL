#pragma once

#include "Food.h"
#pragma once

#include <p6/p6.h>
#include <vector>
#include "DebugUiParameters.h"
#include "MovementVariables.h"
#include "behaviorVariables.h"
#include "glm/fwd.hpp"

class Fish {
private:
    MovementVariables _mvtVariables;
    glm::vec2         _nearestFoodLocation;
    unsigned int      _debugUiNeighboringFishes = 0;

    std::vector<Fish>* _allFishes{};

public:
    Fish(glm::vec2& maxDistanceFromCenter, std::vector<Fish>* allFishes)
        : _mvtVariables(maxDistanceFromCenter), _allFishes(allFishes)
    {
    }

    bool operator==(const Fish& other) const
    {
        return this == &other;
    }
    void draw(p6::Context& ctx, const DebugUiParameters& debugUiParameters, const BehaviorVariables& behaviorVariables, const p6::Color& color, float radius) const;

    void drawDebugFishIfNecessary(p6::Context& ctx, const DebugUiParameters& debugUiParameters, const BehaviorVariables& behaviorVariables) const;

    void update(BehaviorVariables& bvhVariables, glm::vec2& maxDistanceFromCenter, std::vector<Fish>& allFishes, Food* nearestFood);

    void linkArrayToFish(std::vector<Fish>* array);

    void handleSeparation(Fish& OtherFish, glm::vec2& closeSum, float protectedRange);

    void handleAlignment(Fish& OtherFish, glm::vec2& averageVelocity, float visibleRange, int& neighboringFishes);

    void handleCohesion(Fish& OtherFish, glm::vec2& averagePosition, float visibleRange);

    void handleScreenBorders(glm::vec2& maxDistanceFromCenter);

    void handleNearestFoodIfNecessary(Food* nearestFood);

    unsigned int* neighboringFishesPtr();

    // void               variables(BehaviorVariables input);
    BehaviorVariables* bhvVariablesPtr();
    MovementVariables* mvtVariablesPtr();

    // DebugUi* debugUiPtr();
};
