#include <p6/p6.h>
#include <vcruntime.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "glm/fwd.hpp"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

// class squareSwag {
// private:
//     glm::vec2 _pos;
//     p6::Angle _dir{};
//     float     _speed;
//     float     _radius;

// public:
//     explicit squareSwag(float aspect_ratio)
//         : _pos(glm::vec2(p6::random::number(-aspect_ratio, aspect_ratio), p6::random::number(-1, 1))), _speed(p6::random::number() / 500), _radius(p6::random::number(0.2f, 0.3f))
//     {
//     }

//     void draw(p6::Context& ctx) const
//     {
//         ctx.square(
//             p6::Center{_pos.x, _pos.y},
//             p6::Radius{_radius},
//             p6::Rotation{_dir}
//         );
//     }

//     void update(p6::Context& ctx)
//     {
//         First version
//         auto move = rotated_by(_dir, glm::vec2(_speed,0.f));
//         rotated_by(_dir, glm::vec2(_speed,0.f));

//         auto vectorSquareToMouse = (ctx.mouse() - _pos) * _speed;
//         _dir                     = p6::Angle(vectorSquareToMouse);
//         _pos += vectorSquareToMouse;
//     }
// };

class Fish {
private:
    glm::vec2 _pos = glm::vec2(0., 0.);
    p6::Angle _direction{};
    p6::Angle _destination{};
    float     _speed  = 1.f;
    float     _radius = 0.2f;

public:
    explicit Fish(float aspect_ratio)
        : _pos(glm::vec2(p6::random::number(-aspect_ratio, aspect_ratio), p6::random::number(-1, 1))), _direction(p6::Angle(glm::vec2(-_pos.x, -_pos.y))), _speed(p6::random::number() / 100), _radius(p6::random::number(0.2f, 0.3f)) {}
    //     {
    //     }

    void draw(p6::Context& ctx) const
    {
        // FISH SHAPE
        //  ctx.square(
        //      p6::Center{_pos.x, _pos.y},
        //      p6::Radius{_radius},
        //      p6::Rotation{p6::Radians(p6::PI/4.f)}
        //  );
        //  ctx.fill = {1.f, 0.7f, 0.2f};
        //  ctx.use_stroke=false;
        //  ctx.triangle(
        //      p6::Point2D(glm::vec2(_radius,0)),
        //      p6::Point2D(glm::vec2((5.f/3.f)*sqrt((_radius*_radius)*2),sqrt((_radius*_radius)*2))),
        //      p6::Point2D(glm::vec2((4.f/3.f)*sqrt((_radius*_radius)*2),0))
        //  );
        //  ctx.fill = {1.f, 0.7f, 0.2f};
        //  ctx.use_stroke=false;
        //      ctx.triangle(
        //      p6::Point2D(glm::vec2(_radius,0)),
        //      p6::Point2D(glm::vec2((5.f/3.f)*sqrt((_radius*_radius)*2),-1*sqrt((_radius*_radius)*2))),
        //      p6::Point2D(glm::vec2((4.f/3.f)*sqrt((_radius*_radius)*2),0))
        //  );
        //  ctx.fill = {1.f, 0.7f, 0.2f};
        //  ctx.use_stroke=false;

        // Direction vector
        ctx.line(glm::vec2(_pos.x, _pos.y), glm::vec2(_pos.x, _pos.y) + rotated_by(_direction, glm::vec2(0.5f, 0.f)));
        // Simple triangle shape
        ctx.triangle(
            p6::Point2D(glm::vec2(_radius, 0)),
            p6::Point2D(glm::vec2(-_radius, _radius)),
            p6::Point2D(glm::vec2(-_radius, -_radius)),
            p6::Center{_pos.x, _pos.y},
            p6::Rotation(p6::Angle(_direction))
        );
        ctx.fill       = {1.f, 0.7f, 0.2f};
        ctx.use_stroke = false;
    }

    void update(p6::Context& ctx)
    {
        if (p6::random::number(.0f, 1.f) <= 0.3)
            _direction += p6::Angle(p6::Radians((p6::random::number(0.0f, 0.5f) - 0.25f) / 30.f));
        auto move = rotated_by(_direction, glm::vec2(_speed, 0.f));
        _pos += move;
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

    // // Init array
    // std::vector<squareSwag> square_array;
    // for (size_t i = 0; i < 20; ++i)
    // {
    //     squareSwag squareTemp(ctx.aspect_ratio());
    //     square_array.push_back(squareTemp);
    // }

    Fish test(ctx.aspect_ratio());

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);

        test.draw(ctx);
        test.update(ctx);
        // Draw array
        // for (auto& i : square_array)
        // {
        //     i.draw(ctx);
        //     i.update(ctx);
        // }

        // ctx.circle(
        //     p6::Center{ctx.mouse()},
        //     p6::Radius{0.2f}
        // );
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}