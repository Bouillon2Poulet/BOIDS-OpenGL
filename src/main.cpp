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

bool isInside(glm::vec2 vec, float aspect_ratio){
    if (vec.x > -aspect_ratio && vec.x<aspect_ratio){
        if (vec.y>-1.f && vec.y<1.f){
            return true;
        }
    }
    return false;
}

class Fish {
private:
    glm::vec2 _pos = glm::vec2(0., 0.);
    glm::vec2 _destination{};
    p6::Angle _direction{};
    float     _speed  = 1.f;
    float     _radius = 0.1f;

public:
    explicit Fish(float aspect_ratio)
        : _pos(glm::vec2(p6::random::number(-aspect_ratio, aspect_ratio),
            p6::random::number(-1, 1))),
            _destination(_pos+p6::rotated_by(p6::Angle(p6::Radians(p6::random::number(2.f*p6::PI))), glm::vec2(1.f,.0f))){}

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
        p6::Angle angle((p6::Radians((noise*p6::PI)))/100.f); //btw -pi/20 and pi/20 ????

        _destination = _pos+p6::rotated_by(p6::Angle(_destination-_pos)+angle, glm::vec2(1.f,.0f));
        
        //Bounding box
        if (!isInside(_destination, aspect_ratio)){
            glm::vec2 destinationOnLeft(_destination);
            glm::vec2 destinationOnRight(_destination);
            p6::Angle angleTemp;
            do {
                //Increment on right and left to choose which angle is closer to come back in the box
                angleTemp=p6::Angle(p6::Radians(p6::PI/12.f));
                destinationOnLeft=_pos+p6::rotated_by(p6::Angle(destinationOnLeft-_pos)+angle, glm::vec2(1.f,.0f));
                destinationOnRight=_pos+p6::rotated_by(p6::Angle(destinationOnRight-_pos)-angle, glm::vec2(1.f,.0f));

                _destination = (isInside(destinationOnRight,aspect_ratio))?  destinationOnRight:destinationOnLeft;
            } while (!isInside(_destination, aspect_ratio));
        }
        p6::Angle destinationAsAngle(_destination);
        
        p6::Angle deltaAngle((_destination-_pos) - p6::rotated_by(_direction, glm::vec2(1.f,.0f)));
        if (deltaAngle.as_radians()>p6::PI){
                std::cout<<deltaAngle.as_degrees()<<std::endl;
        }
        //_direction = p6::Angle(_destination-_pos);
        p6::Angle rotation = ((p6::Angle(_destination-_pos) - _direction)/5.f);
        // if((p6::Angle(_destination-_pos) - _direction).as_radians()>p6::PI){
        //     std::cout<<"!!\n";
        //     rotation=p6::Angle(p6::Radians(-(2.f*p6::PI)-rotation.as_radians()));
        // }
        _direction += rotation;
        // std::cout<<deltaAngle.as_radians()<<"\n";

        auto move = (_destination-_pos)/50.f;
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