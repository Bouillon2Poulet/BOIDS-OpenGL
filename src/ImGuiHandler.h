#pragma once

#include "Fish.h"
#include "FishTemplate.h"
#include "Scene.h"

class ImGuiHandler {
public:
    static void setDebugVariables(FishTemplate& FishTemplate);
    static void setDebugParameters(FishTemplate& fishTemplate);
    static void setBoundingBox(Scene& scene);
    static void displayImGuiManager(Scene& scene);
};
