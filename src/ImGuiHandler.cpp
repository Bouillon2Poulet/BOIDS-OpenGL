#pragma once

#include "ImGuiHandler.h"

static void setDebugVariables(Fish& FishTemplate)
{
    ImGui::SliderFloat("Protected range", FishTemplate.bhvVariablesPtr()->protectedRangePtr(), 0.f, 1.f);
    ImGui::SliderFloat("Visible range", FishTemplate.bhvVariablesPtr()->visibleRangePtr(), 0.f, 1.f);
    ImGui::SliderFloat("Avoid factor", FishTemplate.bhvVariablesPtr()->avoidFactorPtr(), 0.f, 1.f);
    ImGui::SliderFloat("Matching factor", FishTemplate.bhvVariablesPtr()->matchingFactorPtr(), 0.f, 1.f);
    ImGui::SliderFloat("Centering factor", FishTemplate.bhvVariablesPtr()->centeringFactorPtr(), 0.f, 1.f);
    ImGui::SliderFloat("Turn factor", FishTemplate.bhvVariablesPtr()->turnFactorPtr(), 0.f, 1.f);
    ImGui::SliderFloat("Max speed", FishTemplate.bhvVariablesPtr()->maxSpeedPtr(), 0.f, 5.f);
    ImGui::SliderFloat("Min speed", FishTemplate.bhvVariablesPtr()->minSpeedPtr(), 0.f, 2.f);
}
static void setDebugParameters(Fish& fishTemplate)
{
    ImGui::Checkbox("Display visible range", fishTemplate.debugUiPtr()->parametersPtr()->displayVisibleRangePtr());
    ImGui::Checkbox("Display protected range", fishTemplate.debugUiPtr()->parametersPtr()->displayProtectedRangePtr());
    ImGui::Checkbox("Display velocity vector", fishTemplate.debugUiPtr()->parametersPtr()->displayVelocityVectorPtr());
    ImGui::Checkbox("Display proximity number", fishTemplate.debugUiPtr()->parametersPtr()->displayProximityNbrPtr());
}

void imGuiManager(Scene& scene)
{
    // Show a simple window
    ImGui::Begin("BOIDs variables");

    setDebugVariables(scene.fishTemplate());
    setDebugParameters(scene.fishTemplate());

    ImGui::Checkbox("Display bounding box", scene.displayBoundingBoxPtr());

    ImGui::End();
    // // Show the official ImGui demo window
    // // It is very useful to discover all the widgets available in ImGui
    // ImGui::ShowDemoWindow();
}
