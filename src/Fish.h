#pragma once

#include <p6/p6.h>
#include <vector>
#include "DebugUi.h"
#include "DebugUiParameters.h"
#include "FishTemplate.h"
#include "MovementVariables.h"
#include "behaviorVariables.h"
#include "glm/fwd.hpp"

class Fish {
private:
    float _radius            = 0.01f;
    float _screenAspectRatio = .0f;

    MovementVariables _mvtVariables;
    // BehaviorVariables _bhvVariables{};
    unsigned int _neighboringFishes = 0;
    // DebugUi      _debugUi;

    std::vector<Fish>* _allFishes{};

public:
    Fish(glm::vec2& maxDistanceFromCenter)
        : _mvtVariables(maxDistanceFromCenter)
    {
    }

    void draw(p6::Context& ctx, DebugUiParameters& templateDebugUi, BehaviorVariables& behaviorVariables) const;

    void update(FishTemplate& fishTemplate, float aspect_ratio, glm::vec2& maxDistanceFromCenter);

    void drawFish(p6::Context& ctx) const;

    void linkArrayToFish(std::vector<Fish>* array);

    void handleSeparation(Fish& OtherFish, glm::vec2& closeSum, float protectedRange);

    void handleAlignment(Fish& OtherFish, glm::vec2& averageVelocity, float visibleRange);

    void handleCohesion(Fish& OtherFish, glm::vec2& averagePosition, float visibleRange);

    void handleScreenBorders(glm::vec2& maxDistanceFromCenter);

    void transferTemplateArguments(FishTemplate& fishTemplate);

    void   screenAspectRatio(float input);
    float  screenAspectRatio() const;
    float* screenAspectRatioPtr();

    void          neighboringFishesReset();
    void          neighboringFishesIncrement();
    unsigned int  neighboringFishes() const;
    unsigned int* neighboringFishesPtr();

    // void               variables(BehaviorVariables input);
    BehaviorVariables* bhvVariablesPtr();
    MovementVariables* mvtVariablesPtr();

    // DebugUi* debugUiPtr();
};
