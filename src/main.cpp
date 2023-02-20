#include <p6/p6.h>
#include "SimplexNoise.h"
#include "internal.h"
#include <vcruntime.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "glm/fwd.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

class Fish {
private:
    glm::vec2 _pos = glm::vec2(0., 0.);
    glm::vec2 _destination{};
    p6::Angle _direction{};
    float     _speed  = 1.f;
    float     _radius = 0.2f;

public:
    explicit Fish(float aspect_ratio)
        : _pos(glm::vec2(p6::random::number(-aspect_ratio, aspect_ratio), p6::random::number(-1, 1))), _destination(glm::vec2(static_cast<float>(internal::sign(_pos.x)*-1)*p6::random::number(-aspect_ratio, aspect_ratio), static_cast<float>(internal::sign(_pos.x)*-1)*p6::random::number(-1, 1))), _direction(p6::Angle(_destination-_pos)), _speed(p6::random::number() / 100), _radius(p6::random::number(0.2f, 0.3f)) {}

    void draw(p6::Context& ctx) const
    {
        ctx.push_transform();

        ctx.translate({_pos.x, _pos.y});
        ctx.rotate(p6::Angle(p6::Radians(p6::PI)));
        ctx.rotate(_direction);

        ctx.fill       = {1.f, 0.7f, 0.2f};
        ctx.use_stroke = false;

        float diagonalOfSquare = sqrt((_radius * _radius) * 2);
        // Direction vector
        ctx.line(glm::vec2(-diagonalOfSquare,.0f), glm::vec2(-diagonalOfSquare-0.2f, .0f));

        ctx.use_fill=false;
        ctx.use_stroke = true;
        // FISH SHAPE
        ctx.square(
            p6::Center{.0f, .0f},
            p6::Radius{_radius},
            p6::Rotation{p6::Radians(p6::PI / 4)}
        );
        ctx.triangle(
            p6::Point2D(glm::vec2(_radius, 0)),
            p6::Point2D(glm::vec2((5.f / 3.f) * diagonalOfSquare, diagonalOfSquare)),
            p6::Point2D(glm::vec2((4.f / 3.f) *diagonalOfSquare, 0))
        );
        ctx.triangle(
            p6::Point2D(glm::vec2(_radius, 0)),
            p6::Point2D(glm::vec2((5.f / 3.f) * diagonalOfSquare, -1 * diagonalOfSquare)),
            p6::Point2D(glm::vec2((4.f / 3.f) * diagonalOfSquare, 0))
        );
        ctx.pop_transform();

        // Destination
        ctx.square(
            p6::Center{_destination.x, _destination.y},
            p6::Radius{0.1f}
        );
    }

    void update(float aspect_ratio)
    {
        float noise = SimplexNoise::noise(_pos.x,_pos.y); //btw 0 and 1
        p6::Angle angle((p6::Radians((noise*p6::PI)-p6::PI))/20.f); //btw -pi/20 and pi/20 ????

        _direction = p6::Angle(_destination-_pos) + angle;

        auto move = (_destination-_pos)*_speed;
        _pos += move;

        if (glm::length(_destination-_pos)<0.3)
        {
            _destination = (glm::vec2(static_cast<float>(internal::sign(_pos.x)*-1)*p6::random::number(-aspect_ratio, aspect_ratio), static_cast<float>(internal::sign(_pos.x)*-1)*p6::random::number(-1, 1)));
        }
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

    Fish test(ctx.aspect_ratio());

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);
        test.update(ctx.aspect_ratio());
        test.draw(ctx);
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}