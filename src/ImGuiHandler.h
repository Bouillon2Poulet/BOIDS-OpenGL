#pragma once

#include "Fish.h"
#include "FishGang.h"
#include "Scene.h"

class ImGuiHandler {
public:
    static void setDebugVariables(FishGang& FishGang);
    static void setDebugParameters(FishGang& FishGang);
    static void setBoundingBox(Scene& scene);
    static void displayImGuiManager(Scene& scene);
};
