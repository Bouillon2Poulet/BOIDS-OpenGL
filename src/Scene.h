#pragma once

#include "Fish.h"
#include "FishGang.h"
#include "FishType.h"
#include "FoodKind.h"
#include "PlayableFish.h"

class Scene {
private:
    std::vector<FishGang> _fishGangs{};
    std::vector<FoodKind> _allFoods{};
    bool                  _displayBoundingBox = false;
    glm::vec2             _maxDistanceFromCenter{};
    PlayableFish          _playableFish;
    p6::Color             _backgroundColor = p6::NamedColor::Blue;

public:
    Scene(float aspect_ratio);

    void drawBoundingBox(p6::Context& ctx);

    void createFishGangAndFoods(FishType type, int nbFishes);

    void                   draw(p6::Context& ctx);
    void                   update(const glm::vec2& mousePosition);
    bool                   displayBoundingBox();
    std::vector<FishGang>* fishGangsPtr();
    bool*                  displayBoundingBoxPtr();

    void       displayBoundingBoxIfNecessary(p6::Context& ctx);
    glm::vec2* maxDistanceFromCenterPtr();
    glm::vec2  randomPosInBoundingBox();

    inline glm::vec2 maxDistanceFromCenter()
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
};