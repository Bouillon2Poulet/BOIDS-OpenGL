#pragma once

#include <string>
#include "BehaviorVariables.h"
#include "DebugUi.h"
#include "DebugUiParameters.h"

class FishTemplate {
private:
    BehaviorVariables _bhvVariables{};
    DebugUiParameters _debugUiParameters{};
    // DebugUi           _debugUi{};
    int         _type;
    std::string _name;
    p6::Color   _color{};

public:
    inline FishTemplate()
        : _bhvVariables(1), _name("koi"), _type(1)
    {
        std::cout << "1.15 -> " << _bhvVariables.avoidFactor() << "<_n";
        if (_type == 1)
            _color = *new p6::Color(1.f, 0.2f, .0f);
        else if (_type = 2)
            _color = *new p6::Color(0.f, 0.7f, .5f);
        else
            std::cout << "1.16\n";
        // std::abort();
    };
    BehaviorVariables* bhvVariablesPtr();
    DebugUiParameters*  debugUiParametersPtr();
};