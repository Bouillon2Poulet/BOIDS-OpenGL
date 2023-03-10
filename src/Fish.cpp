#include "Fish.h"

void Fish::draw(p6::Context& ctx) const
{
    drawFish(ctx);
    if (_displayProtectedRange)
        drawProtectedCircle(ctx);
    if (_displayVisibleRange)
        drawVisibleCircle(ctx);
}

void Fish::update(float aspect_ratio, glm::vec2& maxDistanceFromCenter)
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

void Fish::drawFish(p6::Context& ctx) const
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

void Fish::drawProtectedCircle(p6::Context& ctx) const
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

void Fish::drawVisibleCircle(p6::Context& ctx) const
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

void Fish::linkArrayToFish(std::vector<Fish>* array)
{
    _allFishes = array;
}

glm::vec2 Fish::randomPosInBoundingBox(glm::vec2 radii)
{
    return {p6::random::number(-radii.x, radii.x), p6::random::number(-radii.y, radii.y)};
}

void Fish::handleSeparation(glm::vec2& OtherFishPosition, glm::vec2& closeSum)
{
    if (glm::length(OtherFishPosition - _position) <= _protectedRange)
    {
        closeSum += (_position - OtherFishPosition);
    }
}

void Fish::handleAlignment(glm::vec2& OtherFishPosition, glm::vec2& averageVelocity, unsigned int& neighboringFishes)
{
    if (glm::length(OtherFishPosition - _position) <= _visibleRange)
    {
        averageVelocity += OtherFishPosition;
        neighboringFishes++;
    }
}

void Fish::handleCohesion(glm::vec2& OtherFishPosition, glm::vec2& averagePosition)
{
    if (glm::length(OtherFishPosition - _position) <= _visibleRange)
    {
        averagePosition += OtherFishPosition;
    }
}

void Fish::handleScreenBorders(glm::vec2& maxDistanceFromCenter)
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

void Fish::transferTemplateArguments(Fish& fishTemplate)
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
void Fish::protectedRange(float input)
{
    _protectedRange = input;
}
float Fish::protectedRange() const
{
    return _protectedRange;
}
float* Fish::protectedRange()
{
    return &_protectedRange;
}

void Fish::visibleRange(float input)
{
    _visibleRange = input;
}
float Fish::visibleRange() const
{
    return _visibleRange;
}
float* Fish::visibleRange()
{
    return &_visibleRange;
}

void Fish::avoidFactor(float input)
{
    _avoidFactor = input;
}
float Fish::avoidFactor() const
{
    return _avoidFactor;
}
float* Fish::avoidFactor()
{
    return &_avoidFactor;
}

void Fish::matchingFactor(float input)
{
    _matchingFactor = input;
}
float Fish::matchingFactor() const
{
    return _matchingFactor;
}
float* Fish::matchingFactor()
{
    return &_matchingFactor;
}

void Fish::centeringFactor(float input)
{
    _centeringFactor = input;
}
float Fish::centeringFactor() const
{
    return _centeringFactor;
}
float* Fish::centeringFactor()
{
    return &_centeringFactor;
}

void Fish::turnFactor(float input)
{
    _turnFactor = input;
}
float Fish::turnFactor() const
{
    return _turnFactor;
}
float* Fish::turnFactor()
{
    return &_turnFactor;
}

void Fish::displayVisibleRange(bool input)
{
    _displayVisibleRange = input;
}
bool Fish::displayVisibleRange() const
{
    return _displayVisibleRange;
}
bool* Fish::displayVisibleRange()
{
    return &_displayVisibleRange;
}

void Fish::displayProtectedRange(bool input)
{
    _displayProtectedRange = input;
}
bool Fish::displayProtectedRange() const
{
    return _displayProtectedRange;
}
bool* Fish::displayProtectedRange()
{
    return &_displayProtectedRange;
}