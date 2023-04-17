#pragma once
#include <p6/p6.h>
#include <string>
#include <vector>
#include "glm/fwd.hpp"
#include "internal.h"

class Food {
private:
    glm::vec3    _position{};
    float        _maxRadius;
    unsigned int _maxHP;
    float        _currentRadius = _maxRadius;
    unsigned int _currentHP     = _maxHP;

public:
    Food(glm::vec3 maxDistanceFromCenter, unsigned int maxHP, float maxRadius)
        : _position(internal::randomPosInBoundingBox(maxDistanceFromCenter / 2.f)), _maxRadius(maxRadius), _maxHP(maxHP) {}

    inline void isEaten()
    {
        if (_currentHP != 0)
            _currentHP -= 1;
        _currentRadius = _maxRadius * _currentHP / _maxHP;
        if (_currentRadius < 0.01)
        {
            _currentHP = 0;
        }
    }

    inline unsigned int currentHP()
    {
        return _currentHP;
    }

    inline glm::vec3 position()
    {
        return _position;
    }

    inline float radius()
    {
        return _currentRadius;
    }

    inline void draw(p6::Context& ctx, p6::Color color) const
    {
        ctx.push_transform();
        ctx.translate({_position.x, _position.y});
        ctx.fill       = color;
        ctx.use_fill   = true;
        ctx.use_stroke = false;
        ctx.circle(
            p6::Center{.0f, .0f},
            p6::Radius{_currentRadius}
        );
        // ctx.translate({0.03, 0});
        // const std::u16string indexStr = internal::to_u16string(static_cast<int>(index));
        // ctx.text(indexStr, p6::Center{}, p6::Rotation{});
        ctx.pop_transform();
    }
};