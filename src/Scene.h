#pragma once

#include "Arpenteur.h"
#include "Fish.h"
#include "FishGang.h"
#include "FishType.h"
#include "FoodKind.h"
#include "Obstacle.h"
#include "PointLight.h"
#include "TrackballCamera.hpp"
#include "Vertices3D.h"
#include "my3DModel.h"
#include "myProgram.h"
#include "DirectionalLight.h"


class Scene {
private:
    std::vector<FishGang> _fishGangs{};
    std::vector<FoodKind> _allFoods{};
    bool                  _displayBoundingBox = false;
    glm::vec3             _maxDistanceFromCenter{};
    Arpenteur             _arpenteur;
    p6::Color             _backgroundColor = p6::NamedColor::Black;
    myProgram             _program{};
    TrackballCamera       _camera{};
    glm::mat4             _projMatrix;
    Vertices3D            _boundingBox;
    Matrices              _boundingBoxMatrices;
    std::vector<Obstacle> _obstacles;
    PointLight            _pointLight;
    DirectionalLight _directionalLight;

public:
    Scene(const p6::Context& ctx);


    void drawBoundingBox();

    void createFishGangAndFoods(FishType type, int nbFishes, float radius);

    void                   draw(p6::Context& ctx);
    void                   update(p6::Context& ctx);
    bool                   displayBoundingBox();
    std::vector<FishGang>* fishGangsPtr();
    bool*                  displayBoundingBoxPtr();

    void       displayBoundingBoxIfNecessary();
    glm::vec3* maxDistanceFromCenterPtr();
    glm::vec3  randomPosInBoundingBox();

    inline glm::vec3 maxDistanceFromCenter()
    {
        return _maxDistanceFromCenter;
    }
    inline p6::Color* backgroundColorPtr()
    {
        return &_backgroundColor;
    }

    inline void GUIdisplay()
    {
        for (auto& fishGang : _fishGangs) // TODO : not working !
        {
            ImGui::Begin(fishGang.name().c_str());
            fishGang.GUIdisplayFishGangBehaviorVariables();
            fishGang.GUIdisplayFishGangDebugParameters();
            ImGui::End();

            // // Show the official ImGui demo window
            // It is very useful to discover all the widgets available in ImGui
            // ImGui::ShowDemoWindow();
        }
        GUIdisplaySceneParameter();
    }
    inline void GUIdisplaySceneParameter()
    {
        ImGui::Checkbox("Display bounding box", displayBoundingBoxPtr());
        ImGui::SliderFloat("BoundingBox width", &(maxDistanceFromCenterPtr()->x), 0.f, 2.f);
        ImGui::SliderFloat("BoundingBox height", &(maxDistanceFromCenterPtr()->y), 0.f, 2.f);
        ImGui::ColorEdit4("Color", &(backgroundColorPtr()->r()));
    }

    inline void sendOpacityToShader(float opacity)
    {
        glUniform1f(_program.uOpacity, opacity);
    }
};