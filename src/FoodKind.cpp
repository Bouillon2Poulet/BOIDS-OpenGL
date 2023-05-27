#include "FoodKind.h"

FoodKind::FoodKind(FishType type, const glm::vec3& maxDistanceFromCenter)
    : _type(type), _model(fishTypeToString(type) + "Food", "")
{
    switch (_type)
    {
    case FishType::koi:
        _radius             = .1f;
        _hp                 = 100.f;
        _chanceForNewFood   = 0.005;
        _minDetectionLength = 2.f;
        break;
    case FishType::shark:
        _radius             = 0.2f;
        _hp                 = 100.f;
        _chanceForNewFood   = 0.00005;
        _minDetectionLength = 3.f;
        break;
    default:
        break;
    }
    addFood(maxDistanceFromCenter);
}

void FoodKind::update(const glm::vec3& maxDistanceFromCenter)
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
        try
        {
            _foods.erase(_foods.begin() + (index + indexCount));
        }
        catch (std::exception& e)
        {
            std::cout << &e << std::endl;
        }

        indexCount++;
    }

    {
        if (p6::random::number() < _chanceForNewFood)
        {
            addFood(maxDistanceFromCenter);
        }
    }
}

void FoodKind::draw(myProgram& program, const glm::mat4& projMatrix, const glm::mat4 viewMatrix)
{
    _model.activateTexture(program);

    for (auto it = _foods.begin(); it != _foods.end(); it++)
    {
        it->draw(program, projMatrix, _model, viewMatrix);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FoodKind::addFood(const glm::vec3& maxDistanceFromCenter)
{
    _foods.emplace_back(maxDistanceFromCenter, _hp, _radius);
}

Food* FoodKind::nearestFood(const glm::vec3& position)
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
    if (glm::length(nearestFood->position() - position) > _minDetectionLength)
    {
        return nullptr;
    }
    return nearestFood;
}