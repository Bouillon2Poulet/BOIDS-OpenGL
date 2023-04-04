#pragma once

#include <string>
#include "BehaviorVariables.h"
#include "DebugUi.h"
#include "DebugUiParameters.h"
#include "Fish.h"
#include "FoodKind.h"


class FishGang {
private:
    std::vector<Fish> _fishes{};
    BehaviorVariables _bhvVariables{};
    DebugUiParameters _debugUiParameters{};
    // DebugUi           _debugUi{};
    int         _type;
    std::string _name;
    p6::Color   _color{};
    float       _radius;

public:
    inline FishGang(const unsigned int type, const unsigned int number, glm::vec2 maxDistanceFromCenter)
        : _bhvVariables(type), _type(type)
    {
        if (_type == 0)
        {
            _name   = "koi";
            _color  = *new p6::Color(1.f, 0.2f, .0f);
            _radius = 0.01f;
        }
        else if (_type = 1)
        {
            _name   = "tuna";
            _color  = *new p6::Color(0.f, 0.7f, .5f);
            _radius = 0.03f;
        }

        std::cout << "1.15 -> " << _bhvVariables.avoidFactor() << "<_n";

        for (unsigned int i = 0; i < number; i++)
        {
            _fishes.emplace_back(maxDistanceFromCenter, &_fishes);
        }
        std::cout << "1.15 -> " << _bhvVariables.avoidFactor() << "<_n";
    };
    void               draw(p6::Context& ctx);
    void               update(glm::vec2 maxDistanceFromCenter, FoodKind& particularKind);
    inline std::string name()
    {
        return _name;
    }

    inline void printName()
    {
        std::cout << _name;
    }

    inline p6::Color* colorPtr()
    {
        return &_color;
    }

    inline std::vector<Fish>* fishesPtr();
    BehaviorVariables*        bhvVariablesPtr();
    DebugUiParameters*        debugUiParametersPtr();
};