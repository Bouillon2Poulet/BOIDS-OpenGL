#pragma once

#include <stdlib.h>
#include <iostream>
#include <string>
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
    inline BehaviorVariables(int type)
    {
        std::cout << "!!1.15 : 1\n";
        if (type == 0)
        {
            _protectedRange  = 0.03f;
            _visibleRange    = 0.2f;
            _avoidFactor     = 0.1f;
            _matchingFactor  = 0.05;
            _centeringFactor = 0.001;
            _turnFactor      = 0.05;

            _maxSpeed = 0.1;
            _minSpeed = 0.05;
        }
        else if (type == 1)
        {
            std::cout << "!!1.16\n";
            _protectedRange  = 0.1f;
            _visibleRange    = 0.2f;
            _avoidFactor     = 0.2f;
            _matchingFactor  = 0.001;
            _centeringFactor = 0.001;
            _turnFactor      = 0.05;

            _maxSpeed = 0.05;
            _minSpeed = 0.01;
        }
        else if (type == 2)
        {
            _protectedRange  = 0.3f;
            _visibleRange    = 0.5f;
            _avoidFactor     = 0.2f;
            _matchingFactor  = 0.001;
            _centeringFactor = 0.001;
            _turnFactor      = 0.05;

            _maxSpeed = 0.01;
            _minSpeed = 0.005;
        }
    };
};