#ifndef __FISH__HPP
#define __FISH__HPP

#include <p6/p6.h>
#include <vector>
#include "DebugUi.h"
#include "MovementVariables.h"
#include "behaviorVariables.h"
#include "displayDebugUiParameters.h"
#include "glm/fwd.hpp"

class Fish {
private:
    float _radius            = 0.01f;
    float _screenAspectRatio = .0f;

    MovementVariables _mvtVariables;
    BehaviorVariables _bhvVariables{};
    DebugUi           _debugUi;

    std::vector<Fish>* _allFishes{};

public:
    explicit Fish(glm::vec2& maxDistanceFromCenter)
        : _mvtVariables(maxDistanceFromCenter), _debugUi(_mvtVariables, _bhvVariables)
    {
        std::cout << "Fish Constructor, position.x :" << _mvtVariables.position().x << ", debugUI.variables.position.x :" << _debugUi.variables().position().x << std::endl;
    }

    void draw(p6::Context& ctx) const;

    void update(float aspect_ratio, glm::vec2& maxDistanceFromCenter);

    void drawFish(p6::Context& ctx) const;

    void linkArrayToFish(std::vector<Fish>* array);

    void handleSeparation(Fish& OtherFish, glm::vec2& closeSum);

    void handleAlignment(Fish& OtherFish, glm::vec2& averageVelocity);

    void handleCohesion(Fish& OtherFish, glm::vec2& averagePosition);

    void handleScreenBorders(glm::vec2& maxDistanceFromCenter);

    void transferTemplateArguments(Fish& fishTemplate);

    void   screenAspectRatio(float input);
    float  screenAspectRatio() const;
    float* screenAspectRatioPtr();

    // void               variables(BehaviorVariables input);
    BehaviorVariables* bhvVariablesPtr();
    MovementVariables* mvtVariablesPtr();

    DebugUi* debugUiPtr();
};

#endif