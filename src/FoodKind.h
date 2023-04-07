#pragma once
#include <p6/p6.h>
#include <algorithm>
#include <vector>
#include "Food.h"
#include "glm/fwd.hpp"

class FoodKind {
private:
    std::vector<Food> _foods;
    int               _type;
    float             _radius{};
    p6::Color         _color;
    unsigned int      _hp;

public:
    FoodKind(int type, glm::vec2& maxDistanceFromCenter)
        : _type(type)
    {
        if (_type == 0)
        {
            _color  = p6::Color(1.f, .6f, .9f);
            _radius = 0.05f;
            _hp     = 10.f;
        }
        else if (_type == 1)
        {
            _color  = p6::Color(.7f, .2, .9f);
            _radius = 0.1f;
            _hp     = 50.f;
        }
        else if (_type == 2)
        {
            _color  = p6::Color(.1f, .8, .3f);
            _radius = 0.2f;
            _hp     = 100.f;
        }
        addFood(maxDistanceFromCenter);
    }

    inline void update(glm::vec2& maxDistanceFromCenter)
    {
        float chanceForNewFood = 0.0005;
        for (int i = 0; i < _foods.size(); i++)
        {
            if (_foods[i].currentHP() == 0)
            {
                addFood(maxDistanceFromCenter);
                _foods.erase(_foods.begin() + i);
            }
        }
        if (p6::random::number() < chanceForNewFood)
        {
            addFood(maxDistanceFromCenter);
        }
        // for (auto it = _foods.begin(); it != _foods.end();)
        // {
        //     if (it->currentHP() == 0)
        //     {
        //         std::cout
        //             << "DELETE Num" << index << std::endl;

        //         addFood(maxDistanceFromCenter);
        //         std::cout
        //             << "ADD OK\n"
        //             << std::endl;

        //         it = _foods.erase(it);
        //         std::cout
        //             << "DELETE OK !\n"
        //             << std::endl;
        //     }
        //     else
        //     {
        //         ++it;
        //     }
        //     index++;
        // }
        // if (p6::random::number() < chanceForNewFood)
        // {
        //     std::cout << "ADD\n";
        //     addFood(maxDistanceFromCenter);
        // }
    }

    inline void draw(p6::Context& ctx)
    {
        int index = 0;
        for (auto it = _foods.begin(); it != _foods.end(); it++)
        {
            it->draw(ctx, _color, index);
            index++;
        }
    }
    inline void addFood(glm::vec2 maxDistanceFromCenter)
    {
        _foods.emplace_back(maxDistanceFromCenter, _hp, _radius);
    }
    inline void deleteFood(std::vector<Food>::iterator& index)
    {
    }
    inline Food* nearestFood(glm::vec2& position)
    {
        Food* nearestFood = &*(_foods.begin());
        if (nearestFood == nullptr)
            std::cout << "C ICI\n"
                      << std::endl;
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