#pragma once

#include <stdlib.h>
#include <iostream>
#include <string>
#include "FishType.h"
#include "imgui.h"

struct BehaviorVariables {
    float _protectedRange;
    float _visibleRange;
    float _avoidFactor;
    float _matchingFactor;
    float _centeringFactor;
    float _turnFactor;
    float _maxSpeed;
    float _minSpeed;

    inline BehaviorVariables() = default;
    inline BehaviorVariables(FishType type)
    {
        if (type == FishType::koi)
        {
            _protectedRange  = 0.3f;
            _visibleRange    = 0.5f;
            _avoidFactor     = 0.05f;
            _matchingFactor  = 0.05;
            _centeringFactor = 0.001;
            _turnFactor      = 0.5;

            _maxSpeed = 0.35;
            _minSpeed = 0.3;
        }
        else if (type == FishType::shark)
        {
            _protectedRange  = 1.5f;
            _visibleRange    = 1.7f;
            _avoidFactor     = 0.005f;
            _matchingFactor  = 0.005f;
            _centeringFactor = 0.001;
            _turnFactor      = 0.05;

            _maxSpeed = 0.1;
            _minSpeed = 0.15;
        }
    };
};