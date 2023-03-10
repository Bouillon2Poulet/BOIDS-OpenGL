#include <p6/p6.h>
#include <vcruntime.h>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <vector>
#include "../lib/SimplexNoise/src/SimplexNoise.h"
#include "Fish.h"
#include "drawing.h"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "internal.h"


#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

void imGuiManager(Fish& FishTemplate, bool* displayBoundingBox);
void drawBoundingBox(p6::Context& ctx, glm::vec2 maxDistanceFromCenter);

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "maxiprogs4"}};
    ctx.maximize_window();

    glm::vec2         maxDistanceFromCenter(ctx.aspect_ratio() - .3f, 1.f - .2f);
    std::vector<Fish> Fishes;
    for (unsigned int i = 0; i < 150; i++)
    {
        Fishes.emplace_back(maxDistanceFromCenter);
        Fishes.back().linkArrayToFish(&Fishes);
    }

    Fish FishTemplate(maxDistanceFromCenter);
    bool displayBoundingBox = false;

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);

        imGuiManager(FishTemplate, &displayBoundingBox);
        if (displayBoundingBox)
            drawBoundingBox(ctx, maxDistanceFromCenter);

        // Fishes
        std::vector<Fish>::iterator it;
        for (it = Fishes.begin(); it != Fishes.end(); it++)
        {
            it->transferTemplateArguments(FishTemplate);
            it->update(ctx.aspect_ratio(), maxDistanceFromCenter);
            it->draw(ctx);
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}

void imGuiManager(Fish& FishTemplate, bool* displayBoundingBox)
{
    // Show a simple window
    ImGui::Begin("BOID variables");

    ImGui::SliderFloat("Protected range", FishTemplate.protectedRange(), 0.f, 1.f);
    ImGui::SliderFloat("Visible range", FishTemplate.visibleRange(), 0.f, 1.f);
    ImGui::SliderFloat("Avoid factor", FishTemplate.avoidFactor(), 0.f, 1.f);
    ImGui::SliderFloat("Matching factor", FishTemplate.matchingFactor(), 0.f, 1.f);
    ImGui::SliderFloat("Centering factor", FishTemplate.centeringFactor(), 0.f, 1.f);
    ImGui::SliderFloat("Turn factor", FishTemplate.turnFactor(), 0.f, 1.f);

    ImGui::Checkbox("Display visible range", FishTemplate.displayVisibleRange());
    ImGui::Checkbox("Display protected range", FishTemplate.displayProtectedRange());
    ImGui::Checkbox("Display bounding box", displayBoundingBox);

    ImGui::End();
    // // Show the official ImGui demo window
    // // It is very useful to discover all the widgets available in ImGui
    // ImGui::ShowDemoWindow();
}
