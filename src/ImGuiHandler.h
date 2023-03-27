#pragma once

#include "Fish.h"
#include "Scene.h"

class ImGuiHandler {
public:
    static void setDebugVariables(Fish& FishTemplate);
    static void setDebugParameters(Fish& fishTemplate);
    static void setBoundingBox(Scene& scene);
    static void displayImGuiManager(Scene& scene);
};
