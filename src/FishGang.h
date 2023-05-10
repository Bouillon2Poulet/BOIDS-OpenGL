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
    my3DModel _model;
    // GLuint _texture;

    FishType  _type;
    float _radius;
    // p6::Color _color{};

public:
    inline FishGang(const FishType type, const unsigned int number, const glm::vec3& maxDistanceFromCenter, float radius)
        : _bhvVariables(static_cast<unsigned int>(type)), _type(type), _model(fishTypeToString(type)), _radius(radius)
    {    
        for (unsigned int i = 0; i < number; i++)
        {
            _fishes.emplace_back(maxDistanceFromCenter, &_fishes);
        }
    };

    void            draw(p6::Context& ctx, const myProgram& program, const glm::mat4& projMatrix);
    void            update(const glm::vec3& maxDistanceFromCenter, FoodKind& particularFoodKind, const glm::mat4& viewMatrix);
    inline FishType type()
    {
        return _type;
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
        // ImGui::ColorEdit4("Color", &(_color.r()));
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

    // inline int vertices3DSize()
    // {
    //     return _vertices3D.size();
    // }
};
