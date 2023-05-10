#pragma once
#include <p6/p6.h>
#include <algorithm>
#include <vector>
#include "FishType.h"
#include "Food.h"
#include "Matrices.h"
#include "glm/fwd.hpp"
#include "my3DModel.h"

class FoodKind {
private:
    std::vector<Food> _foods;
    FishType          _type;
    float             _radius{};
    unsigned int      _hp;
    my3DModel         _model;

public:
    FoodKind(FishType type, const glm::vec3& maxDistanceFromCenter)
        : _type(type), _model(fishTypeToString(type) + "Food")
    {
        switch (_type)
        {
        case FishType::koi:
            _radius = .1f;
            _hp     = 100.f;
            break;
        case FishType::tuna:
            _radius = 0.1f;
            _hp     = 50.f;
            break;
        case FishType::shark:
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
            static constexpr float chanceForNewFood = 0.005;

            if (p6::random::number() < chanceForNewFood)
            {
                addFood(maxDistanceFromCenter);
            }
        }
    }

    inline void draw(myProgram& program, const glm::mat4& projMatrix, const glm::mat4 viewMatrix)
    {
        _model.activateTexture(program);

        for (auto it = _foods.begin(); it != _foods.end(); it++)
        {
            it->draw(program, projMatrix, _model, viewMatrix);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
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
