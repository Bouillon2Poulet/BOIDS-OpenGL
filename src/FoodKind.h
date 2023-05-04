#pragma once
#include <p6/p6.h>
#include <algorithm>
#include <vector>
#include "FishType.h"
#include "Food.h"
#include "glm/fwd.hpp"

class FoodKind {
private:
    std::vector<Food> _foods;
    FishType          _type;
    float             _radius{};
    p6::Color         _color;
    unsigned int      _hp;

public:
    FoodKind(FishType type, const glm::vec3& maxDistanceFromCenter)
        : _type(type)
    {
        switch (_type)
        {
        case FishType::koi:
            _color  = p6::Color(1.f, .6f, .9f);
            _radius = 0.05f;
            _hp     = 10.f;
            break;
        case FishType::tuna:
            _color  = p6::Color(.7f, .2, .9f);
            _radius = 0.1f;
            _hp     = 50.f;
            break;
        case FishType::shark:
            _color  = p6::Color(.1f, .8, .3f);
            _radius = 0.2f;
            _hp     = 100.f;
            break;
        default:
            break;
        }
        addFood(maxDistanceFromCenter);
    }

    inline void update(const glm::vec3& maxDistanceFromCenter)
    {
        std::vector<int> indexArray;
        for (int i = 0; i < _foods.size(); i++)
        {
            if (_foods[i].currentHP() == 0)
            {
                indexArray.push_back(i);
            }
        }

        int indexCount = 0;
        for (auto& index : indexArray)
        {
            _foods.erase(_foods.begin() + (index + indexCount));
            indexCount++;
        }

        {
            static constexpr float chanceForNewFood = 0.0005;
            if (p6::random::number() < chanceForNewFood)
            {
                addFood(maxDistanceFromCenter);
            }
        }
    }

    inline void draw(p6::Context& ctx) const
    {
        int index = 0;
        for (auto it = _foods.begin(); it != _foods.end(); it++)
        {
            it->draw(ctx, _color);
            index++;
        }
    }
    inline void addFood(const glm::vec3& maxDistanceFromCenter)
    {
        _foods.emplace_back(maxDistanceFromCenter, _hp, _radius);
    }

    inline Food* nearestFood(const glm::vec3& position)
    {
        if (_foods.empty())
        {
            return nullptr;
        }
        Food* nearestFood = &(_foods.front());
        for (auto it = _foods.begin(); it != _foods.end(); it++)
        {
            if (glm::length(it->position() - position) <= glm::length(nearestFood->position() - position))
            {
                nearestFood = &*it;
            }
        }
        return nearestFood;
    }
};
