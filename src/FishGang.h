#pragma once

#include <string>
#include "BehaviorVariables.h"
#include "DebugUiParameters.h"
#include "Fish.h"
#include "FishType.h"
#include "FoodKind.h"
#include "Vertices3D.h"
#include "my3DModel.h"

class FishGang {
private:
    std::vector<Fish> _fishes{};
    BehaviorVariables _bhvVariables{};
    DebugUiParameters _debugUiParameters{};
    Vertices3D        _vertices3D{};
    // my3DModel _3Dmodel;
    // GLuint _texture;

    FishType  _type;
    p6::Color _color{};
    float     _radius;

public:
    inline FishGang(const FishType type, const unsigned int number, const glm::vec3& maxDistanceFromCenter)
        : _bhvVariables(static_cast<unsigned int>(type)), _type(type)
    {
        _vertices3D = Vertices3D(ShapeType::cone);
        if (_type == FishType::koi)
        {
            _color  = p6::Color(1.f, 0.2f, .0f);
            _radius = 0.1f;
            _vertices3D = Vertices3D(ShapeType::model, "koi");

        }
        else if (_type == FishType::tuna)
        {
            _color  = p6::Color(0.f, 0.7f, .5f);
            _radius = 0.03f;
        }
        else if (_type == FishType::shark)
        {
            _color  = p6::Color(0.f, 1.f, 1.f);
            _radius = 0.5f;
            _vertices3D = Vertices3D(ShapeType::model, "shark");

        }

        for (unsigned int i = 0; i < number; i++)
        {
            _fishes.emplace_back(maxDistanceFromCenter, &_fishes);
        }
        // std::cout << fishTypeToString(_type) << " initialisation - vertices.size : " << _vertices3D.size();
        // int a;
        // std::cin >> a;
    };

    void            draw(p6::Context& ctx, const myProgram& program, const glm::mat4& projMatrix);
    void            update(const glm::vec3& maxDistanceFromCenter, FoodKind& particularFoodKind, const glm::mat4& viewMatrix);
    inline FishType type()
    {
        return _type;
    }

    inline p6::Color* colorPtr()
    {
        return &_color;
    }

    inline std::vector<Fish>* fishesPtr();
    BehaviorVariables*        bhvVariablesPtr();
    DebugUiParameters*        debugUiParametersPtr();

    void GUIdisplayFishGangDebugParameters()
    {
        ImGui::Checkbox("Display visible range", &(_debugUiParameters._displayVisibleRange));
        ImGui::Checkbox("Display protected range", &(_debugUiParameters._displayProtectedRange));
        ImGui::Checkbox("Display velocity vector", &(_debugUiParameters._displayVelocityVector));
        ImGui::Checkbox("Display proximity number", &(_debugUiParameters._displayProximityNbr));
        ImGui::Checkbox("Display link to nearest food", &(_debugUiParameters._displayLinkToNearestFood));
        ImGui::ColorEdit4("Color", &(_color.r()));
    }

    void GUIdisplayFishGangBehaviorVariables()
    {
        ImGui::SliderFloat("Protected range", &(_bhvVariables._protectedRange), 0.f, 1.f);
        ImGui::SliderFloat("Visible range", &(_bhvVariables._visibleRange), 0.f, 1.f);
        ImGui::SliderFloat("Avoid factor", &(_bhvVariables._avoidFactor), 0.f, 1.f);
        ImGui::SliderFloat("Matching factor", &(_bhvVariables._matchingFactor), 0.f, 1.f);
        ImGui::SliderFloat("Centering factor", &(_bhvVariables._centeringFactor), 0.f, 1.f);
        ImGui::SliderFloat("Turn factor", &(_bhvVariables._turnFactor), 0.f, 1.f);
        ImGui::SliderFloat("Max speed", &(_bhvVariables._maxSpeed), 0.f, 5.f);
        ImGui::SliderFloat("Min speed", &(_bhvVariables._minSpeed), 0.f, 2.f);
    }

    std::string name()
    {
        return fishTypeToString(_type);
    }

    inline int vertices3DSize()
    {
        return _vertices3D.size();
    }
};
