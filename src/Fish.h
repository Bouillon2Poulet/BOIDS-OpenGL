#ifndef __FISH__HPP
#define __FISH__HPP

#include <p6/p6.h>
#include <vector>
#include "glm/fwd.hpp"

class Fish {
private:
    glm::vec2 _position              = glm::vec2(0., 0.);
    glm::vec2 _velocity              = glm::vec2(0., 0.);
    float     _protectedRange        = 0.02f;
    float     _visibleRange          = 0.07f;
    float     _radius                = 0.01f;
    float     _avoidFactor           = 0.5f;
    float     _matchingFactor        = 0.05f;
    float     _centeringFactor       = 0.05f;
    float     _turnFactor            = 0.05f;
    float     _screenAspectRatio     = .0f;
    bool      _displayProtectedRange = false;
    bool      _displayVisibleRange   = false;

    std::vector<Fish>* _allFishes{};

public:
    explicit Fish(glm::vec2& maxDistanceFromCenter)
        : _position(randomPosInBoundingBox(maxDistanceFromCenter))
    {}

    void draw(p6::Context& ctx) const;

    void update(float aspect_ratio, glm::vec2& maxDistanceFromCenter);

    void drawFish(p6::Context& ctx) const;

    void drawProtectedCircle(p6::Context& ctx) const;

    void drawVisibleCircle(p6::Context& ctx) const;

    void linkArrayToFish(std::vector<Fish>* array);

    static glm::vec2 randomPosInBoundingBox(glm::vec2 radii);

    void handleSeparation(glm::vec2& OtherFishPosition, glm::vec2& closeSum);

    void handleAlignment(glm::vec2& OtherFishPosition, glm::vec2& averageVelocity, unsigned int& neighboringFishes);

    void handleCohesion(glm::vec2& OtherFishPosition, glm::vec2& averagePosition);

    void handleScreenBorders(glm::vec2& maxDistanceFromCenter);

    void transferTemplateArguments(Fish& fishTemplate);

    // Get & Setters
    void   protectedRange(float input);
    float  protectedRange() const;
    float* protectedRange();

    void   visibleRange(float input);
    float  visibleRange() const;
    float* visibleRange();

    void   avoidFactor(float input);
    float  avoidFactor() const;
    float* avoidFactor();

    void   matchingFactor(float input);
    float  matchingFactor() const;
    float* matchingFactor();

    void   centeringFactor(float input);
    float  centeringFactor() const;
    float* centeringFactor();

    void   turnFactor(float input);
    float  turnFactor() const;
    float* turnFactor();

    void  displayVisibleRange(bool input);
    bool  displayVisibleRange() const;
    bool* displayVisibleRange();

    void  displayProtectedRange(bool input);
    bool  displayProtectedRange() const;
    bool* displayProtectedRange();
};

#endif