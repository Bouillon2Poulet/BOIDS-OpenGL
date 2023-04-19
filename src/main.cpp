#include <math.h>
#include <p6/p6.h>
#include <vcruntime.h>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <vector>
#include "Fish.h"
#include "Mesh.h"
#include "Scene.h"
#include "assimp/aabb.h"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "internal.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
#include "doctest/doctest.h"

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
    glEnable(GL_DEPTH_TEST);

    // Mesh meshTest;
    // meshTest.LoadMesh("coral");
    Scene scene(ctx);
    // Declare your infinite update loop.
    ctx.update = [&]() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.update(ctx);
        scene.draw(ctx);

        scene.GUIdisplay();
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}
