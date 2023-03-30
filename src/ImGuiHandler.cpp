#pragma once

#include "ImGuiHandler.h"
#include "FishTemplate.h"

void ImGuiHandler::setDebugVariables(FishTemplate& FishTemplate)
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
void ImGuiHandler::setDebugParameters(FishTemplate& fishTemplate)
{
    ImGui::Checkbox("Display visible range", fishTemplate.debugUiPtr()->parametersPtr()->displayVisibleRangePtr());
    ImGui::Checkbox("Display protected range", fishTemplate.debugUiPtr()->parametersPtr()->displayProtectedRangePtr());
    ImGui::Checkbox("Display velocity vector", fishTemplate.debugUiPtr()->parametersPtr()->displayVelocityVectorPtr());
    ImGui::Checkbox("Display proximity number", fishTemplate.debugUiPtr()->parametersPtr()->displayProximityNbrPtr());
}

void ImGuiHandler::setBoundingBox(Scene& scene)
{
    ImGui::Checkbox("Display bounding box", scene.displayBoundingBoxPtr());
    ImGui::SliderFloat("BoundingBox width", &(scene.maxDistanceFromCenterPtr()->x), 0.f, 2.f);
    ImGui::SliderFloat("BoundingBox height", &(scene.maxDistanceFromCenterPtr()->y), 0.f, 2.f);
}

void ImGuiHandler::displayImGuiManager(Scene& scene)
{
    // Show a simple window
    ImGui::Begin("BOIDs variables");

    ImGuiHandler::setDebugVariables(scene.fishTemplate());
    ImGuiHandler::setDebugParameters(scene.fishTemplate());
    ImGuiHandler::setBoundingBox(scene);

    ImGui::End();
    // // Show the official ImGui demo window
    // // It is very useful to discover all the widgets available in ImGui
    // ImGui::ShowDemoWindow();
}
