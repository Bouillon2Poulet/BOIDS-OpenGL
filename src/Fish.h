#pragma once

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
    // BehaviorVariables _bhvVariables{};
    unsigned int _neighboringFishes = 0;
    // DebugUi      _debugUi;

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
    void draw(p6::Context& ctx, DebugUiParameters& templateDebugUi, BehaviorVariables& behaviorVariables, p6::Color& color, float radius) const;

    void update(BehaviorVariables& bvhVariables, glm::vec2& maxDistanceFromCenter, std::vector<Fish>& allFishes);

    void drawFish(p6::Context& ctx, p6::Color& color, float radius) const;

    void linkArrayToFish(std::vector<Fish>* array);

    void handleSeparation(Fish& OtherFish, glm::vec2& closeSum, float protectedRange);

    void handleAlignment(Fish& OtherFish, glm::vec2& averageVelocity, float visibleRange);

    void handleCohesion(Fish& OtherFish, glm::vec2& averagePosition, float visibleRange);

    void handleScreenBorders(glm::vec2& maxDistanceFromCenter);

    void          neighboringFishesReset();
    void          neighboringFishesIncrement();
    unsigned int  neighboringFishes() const;
    unsigned int* neighboringFishesPtr();

    // void               variables(BehaviorVariables input);
    BehaviorVariables* bhvVariablesPtr();
    MovementVariables* mvtVariablesPtr();

    // DebugUi* debugUiPtr();
};
