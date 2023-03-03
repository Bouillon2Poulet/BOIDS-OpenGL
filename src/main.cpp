#include <p6/p6.h>
#include <vcruntime.h>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <vector>
#include "../lib/SimplexNoise/src/SimplexNoise.h"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "internal.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

class Fish {
private:
    glm::vec2 _position        = glm::vec2(0., 0.);
    glm::vec2 _velocity        = glm::vec2(0., 0.);
    float     _protectedRange  = 0.02f;
    float     _visibleRange    = 0.07f;
    float     _radius          = 0.01f;
    float     _avoidFactor     = 0.5f;
    float     _matchingFactor  = 0.05f;
    float     _centeringFactor = 0.05f;
    float     _turnFactor      = 0.05f;

    float _screenAspectRatio;
    bool  _displayProtectedRange = false;
    bool  _displayVisibleRange   = false;

    std::vector<Fish>* _allFishes{};

public:
    explicit Fish(glm::vec2 maxDistanceFromCenter)
        : _position(randomPosInBoundingBox(maxDistanceFromCenter))
    {}

    void draw(p6::Context& ctx) const
    {
        drawFish(ctx);
        if (_displayProtectedRange)
            drawProtectedCircle(ctx);
        if (_displayVisibleRange)
            drawVisibleCircle(ctx);
    }

    void update(float aspect_ratio, glm::vec2 maxDistanceFromCenter)
    {
        _screenAspectRatio             = aspect_ratio;
        unsigned int neighboringFishes = 0;

        // Separation variable
        glm::vec2 closeSum(.0f, .0f);

        // Alignment variables
        glm::vec2 averageVelocity(.0f, .0f);

        // Cohesion variables
        glm::vec2 averagePosition(.0f, .0f);

        // Behaviors
        std::vector<Fish>::iterator it;
        for (it = _allFishes->begin(); it != _allFishes->end(); it++)
        {
            handleSeparation(it->_position, closeSum);
            handleAlignment(it->_position, averageVelocity, neighboringFishes);
            handleCohesion(it->_position, averagePosition);
        }

        // Velocity update
        // Separation
        _velocity = closeSum * _avoidFactor;

        // Alignment and Cohesion
        if (neighboringFishes != 0)
        {
            averageVelocity /= neighboringFishes;
            _velocity += (averageVelocity - _velocity) * _matchingFactor;

            averagePosition /= neighboringFishes;
            _velocity += (averagePosition - _position) * _centeringFactor;
        }

        handleScreenBorders(maxDistanceFromCenter);

        // Position update
        _position += _velocity / 10.f;
    }

    void drawFish(p6::Context& ctx) const
    {
        ctx.push_transform();
        ctx.translate({_position.x, _position.y});
        ctx.fill       = {1.f, 0.7f, 0.2f};
        ctx.use_fill   = true;
        ctx.use_stroke = false;
        ctx.square(
            p6::Center{.0f, .0f},
            p6::Radius{_radius}
        );
        ctx.pop_transform();
    }

    void drawProtectedCircle(p6::Context& ctx) const
    {
        ctx.push_transform();
        ctx.translate({_position.x, _position.y});
        ctx.stroke     = {1.f, .0f, .0f};
        ctx.use_fill   = false;
        ctx.use_stroke = true;
        ctx.circle(
            p6::Center{.0f, .0f},
            p6::Radius{_protectedRange}
        );
        ctx.pop_transform();
    }

    void drawVisibleCircle(p6::Context& ctx) const
    {
        ctx.push_transform();
        ctx.translate({_position.x, _position.y});
        ctx.stroke     = {.0f, .1f, 0.f};
        ctx.use_fill   = false;
        ctx.use_stroke = true;
        ctx.circle(
            p6::Center{.0f, .0f},
            p6::Radius{_visibleRange}
        );
        ctx.pop_transform();
    }

    void linkArrayToFish(std::vector<Fish>* array)
    {
        _allFishes = array;
    }

    static glm::vec2 randomPosInBoundingBox(glm::vec2 radii)
    {
        return {p6::random::number(-radii.x, radii.x), p6::random::number(-radii.y, radii.y)};
    }

    void handleSeparation(glm::vec2& OtherFishPosition, glm::vec2& closeSum)
    {
        if (glm::length(OtherFishPosition - _position) <= _protectedRange)
        {
            closeSum += (_position - OtherFishPosition);
        }
    }

    void handleAlignment(glm::vec2& OtherFishPosition, glm::vec2& averageVelocity, unsigned int& neighboringFishes)
    {
        if (glm::length(OtherFishPosition - _position) <= _visibleRange)
        {
            averageVelocity += OtherFishPosition;
            neighboringFishes++;
        }
    }

    void handleCohesion(glm::vec2& OtherFishPosition, glm::vec2& averagePosition)
    {
        if (glm::length(OtherFishPosition - _position) <= _visibleRange)
        {
            averagePosition += OtherFishPosition;
        }
    }

    void handleScreenBorders(glm::vec2 maxDistanceFromCenter)
    {
        float marginFactor = 0.5f;
        if (_position.x <= -maxDistanceFromCenter.x)
        {
            float distanceToMargin = abs(_position.x - (-maxDistanceFromCenter.x));
            float speedLimit       = marginFactor * distanceToMargin;
            _velocity.x            = std::max(_velocity.x, speedLimit);
            _velocity.x += _turnFactor;
        }
        if (_position.x >= maxDistanceFromCenter.x)
        {
            float distanceToMargin = abs(_position.x - maxDistanceFromCenter.x);
            float speedLimit       = marginFactor * distanceToMargin;
            _velocity.x            = std::min(_velocity.x, -speedLimit);
            _velocity.x -= _turnFactor;
        }
        if (_position.y <= -maxDistanceFromCenter.y)
        {
            float distanceToMargin = abs(_position.y - (-maxDistanceFromCenter.y));
            float speedLimit       = marginFactor * distanceToMargin;
            _velocity.y            = std::max(_velocity.y, speedLimit);
            _velocity.y += _turnFactor;
        }
        if (_position.y >= maxDistanceFromCenter.y)
        {
            float distanceToMargin = abs(_position.y - maxDistanceFromCenter.y);
            float speedLimit       = marginFactor * distanceToMargin;
            _velocity.y            = std::min(_velocity.y, -speedLimit);
            _velocity.y -= _turnFactor;
        }
    }

    void transferTemplateArguments(Fish& fishTemplate)
    {
        _protectedRange        = fishTemplate._protectedRange;
        _visibleRange          = fishTemplate._visibleRange;
        _avoidFactor           = fishTemplate._avoidFactor;
        _matchingFactor        = fishTemplate._matchingFactor;
        _centeringFactor       = fishTemplate._centeringFactor;
        _turnFactor            = fishTemplate._turnFactor;
        _displayProtectedRange = fishTemplate._displayProtectedRange;
        _displayVisibleRange   = fishTemplate._displayVisibleRange;
    }

    // Get & Setters
    void protectedRange(float input)
    {
        _protectedRange = input;
    }
    float protectedRange() const
    {
        return _protectedRange;
    }
    float* protectedRange()
    {
        return &_protectedRange;
    }

    void visibleRange(float input)
    {
        _visibleRange = input;
    }
    float visibleRange() const
    {
        return _visibleRange;
    }
    float* visibleRange()
    {
        return &_visibleRange;
    }

    void avoidFactor(float input)
    {
        _avoidFactor = input;
    }
    float avoidFactor() const
    {
        return _avoidFactor;
    }
    float* avoidFactor()
    {
        return &_avoidFactor;
    }

    void matchingFactor(float input)
    {
        _matchingFactor = input;
    }
    float matchingFactor() const
    {
        return _matchingFactor;
    }
    float* matchingFactor()
    {
        return &_matchingFactor;
    }

    void centeringFactor(float input)
    {
        _centeringFactor = input;
    }
    float centeringFactor() const
    {
        return _centeringFactor;
    }
    float* centeringFactor()
    {
        return &_centeringFactor;
    }

    void turnFactor(float input)
    {
        _turnFactor = input;
    }
    float turnFactor() const
    {
        return _turnFactor;
    }
    float* turnFactor()
    {
        return &_turnFactor;
    }

    void displayVisibleRange(bool input)
    {
        _displayVisibleRange = input;
    }
    bool displayVisibleRange() const
    {
        return _displayVisibleRange;
    }
    bool* displayVisibleRange()
    {
        return &_displayVisibleRange;
    }

    void displayProtectedRange(bool input)
    {
        _displayProtectedRange = input;
    }
    bool displayProtectedRange() const
    {
        return _displayProtectedRange;
    }
    bool* displayProtectedRange()
    {
        return &_displayProtectedRange;
    }
};

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

void drawBoundingBox(p6::Context& ctx, glm::vec2 maxDistanceFromCenter)
{
    // Bounding box
    ctx.push_transform();
    ctx.use_fill   = false;
    ctx.use_stroke = true;
    ctx.stroke     = p6::Color{1.f, 0.f, 0.f};
    ctx.rectangle(
        p6::Center{.0f, .0f},
        p6::Radii{maxDistanceFromCenter.x, maxDistanceFromCenter.y},
        p6::Rotation{}
    );
    ctx.pop_transform();
}