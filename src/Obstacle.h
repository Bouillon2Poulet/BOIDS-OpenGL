#pragma once

#include "Lods.h"
#include "Matrices.h"
#include "my3DModel.h"
#include "p6/p6.h"

class Obstacle {
private:
    glm::vec3 _position{};
    float     _radius;
    Matrices  _matrices;

    // my3DModel _model;
    LoDs _lods;

public:
    inline Obstacle(const std::string modelName, const glm::vec3& position, const float radius)
        : _position(position), _radius(radius), _lods(modelName)
    {
    }

    inline void update(const glm::mat4& viewMatrix)
    {
        _matrices.updateObstacle(viewMatrix, _position, _radius);
    }

    inline void draw(const myProgram& program, const glm::mat4& projMatrix, const glm::vec3 cameraPosition)
    {
        _matrices.sendMatricesToShader(program, projMatrix);
        std::cout << "GROUND" << std::endl;
        _lods.getRightModel(glm::length(_position - cameraPosition)).activateTexture(program);
        _lods.getRightModel(glm::length(_position - cameraPosition)).draw(program);
    }
};