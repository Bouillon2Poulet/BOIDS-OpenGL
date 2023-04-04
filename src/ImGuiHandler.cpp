#pragma once

#include "ImGuiHandler.h"
#include <cstring>
#include "FishGang.h"
#include "imgui.h"

void ImGuiHandler::setDebugVariables(FishGang& FishGang)
{
    ImGui::SliderFloat("Protected range", FishGang.bhvVariablesPtr()->protectedRangePtr(), 0.f, 1.f);
    ImGui::SliderFloat("Visible range", FishGang.bhvVariablesPtr()->visibleRangePtr(), 0.f, 1.f);
    ImGui::SliderFloat("Avoid factor", FishGang.bhvVariablesPtr()->avoidFactorPtr(), 0.f, 1.f);
    ImGui::SliderFloat("Matching factor", FishGang.bhvVariablesPtr()->matchingFactorPtr(), 0.f, 1.f);
    ImGui::SliderFloat("Centering factor", FishGang.bhvVariablesPtr()->centeringFactorPtr(), 0.f, 1.f);
    ImGui::SliderFloat("Turn factor", FishGang.bhvVariablesPtr()->turnFactorPtr(), 0.f, 1.f);
    ImGui::SliderFloat("Max speed", FishGang.bhvVariablesPtr()->maxSpeedPtr(), 0.f, 5.f);
    ImGui::SliderFloat("Min speed", FishGang.bhvVariablesPtr()->minSpeedPtr(), 0.f, 2.f);
}
void ImGuiHandler::setDebugParameters(FishGang& fishGang)
{
    ImGui::Checkbox("Display visible range", fishGang.debugUiParametersPtr()->displayVisibleRangePtr());
    ImGui::Checkbox("Display protected range", fishGang.debugUiParametersPtr()->displayProtectedRangePtr());
    ImGui::Checkbox("Display velocity vector", fishGang.debugUiParametersPtr()->displayVelocityVectorPtr());
    ImGui::Checkbox("Display proximity number", fishGang.debugUiParametersPtr()->displayProximityNbrPtr());
    ImGui::ColorEdit4("Color", &(fishGang.colorPtr()->r()));
}

void ImGuiHandler::setBoundingBox(Scene& scene)
{
    ImGui::Checkbox("Display bounding box", scene.displayBoundingBoxPtr());
    ImGui::SliderFloat("BoundingBox width", &(scene.maxDistanceFromCenterPtr()->x), 0.f, 2.f);
    ImGui::SliderFloat("BoundingBox height", &(scene.maxDistanceFromCenterPtr()->y), 0.f, 2.f);
    ImGui::ColorEdit4("Color", &(scene.backgroundColorPtr()->r()));
}

void ImGuiHandler::displayImGuiManager(Scene& scene)
{
    for (auto it = scene.fishGangsPtr()->begin(); it != scene.fishGangsPtr()->end(); it++)
    {
        // std::cout << it->name() << std::endl;
        // std::cout << it->bhvVariablesPtr()->avoidFactor() << std::endl;
        // Show a simple window

        ImGui::Begin(it->name().c_str());

        ImGuiHandler::setDebugVariables(*it);
        ImGuiHandler::setDebugParameters(*it);
        ImGui::End();
        // // Show the official ImGui demo window
        // It is very useful to discover all the widgets available in ImGui
        ImGui::ShowDemoWindow();
    }
    ImGuiHandler::setBoundingBox(scene);
}
