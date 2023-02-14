#include <p6/p6.h>
#include <vcruntime.h>
#include <cstdlib>
#include <vector>
#include "glm/fwd.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

class squareSwag {
private:
    glm::vec2 _pos;
    p6::Angle _dir{};
    float     _speed;
    float     _radius;

public:
    explicit squareSwag(float aspect_ratio)
        : _pos(glm::vec2(p6::random::number(-aspect_ratio, aspect_ratio), p6::random::number(-1, 1))), _speed(p6::random::number() / 500), _radius(p6::random::number(0.2f, 0.3f))
    {
    }

    void draw(p6::Context& ctx) const
    {
        ctx.square(
            p6::Center{_pos.x, _pos.y},
            p6::Radius{_radius},
            p6::Rotation{_dir}
        );
    }

    void update(p6::Context& ctx)
    {
        // auto move = rotated_by(_dir, glm::vec2(_speed,0.f));
        auto vectorSquareToMouse = (ctx.mouse() - _pos) * _speed;
        _dir                     = p6::Angle(vectorSquareToMouse);
        // rotated_by(_dir, glm::vec2(_speed,0.f));
        _pos += vectorSquareToMouse;
    }
};

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

    // Init array
    std::vector<squareSwag> square_array;
    for (size_t i = 0; i < 20; ++i)
    {
        squareSwag squareTemp(ctx.aspect_ratio());
        square_array.push_back(squareTemp);
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);

        // Draw array
        for (auto& i : square_array)
        {
            i.draw(ctx);
            i.update(ctx);
        }

        // ctx.circle(
        //     p6::Center{ctx.mouse()},
        //     p6::Radius{0.2f}
        // );
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}