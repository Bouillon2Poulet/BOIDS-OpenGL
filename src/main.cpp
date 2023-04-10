#include <p6/p6.h>
#include <vcruntime.h>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <vector>
// #include "../lib/SimplexNoise/src/SimplexNoise.h"
#include "Fish.h"
#include "ImGuiHandler.h"
#include "Scene.h"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "internal.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

void imGuiManager(Fish& FishGang, bool* displayBoundingBox);

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

    Scene scene(ctx.aspect_ratio()); // TODO pass the aspect_ratio during update instead of construction
    // Declare your infinite update loop.
    ctx.update = [&]() {
        scene.update();
        scene.draw(ctx);
        if (scene.displayBoundingBox()) // TODO Make a method "displayBoundingBox_ifNecessary"
        {
            scene.drawBoundingBox(ctx);
        }

        ImGuiHandler::displayImGuiManager(scene);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}
