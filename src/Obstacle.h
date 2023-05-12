#pragma once

#include "Matrices.h"
#include "my3DModel.h"
#include "p6/p6.h"

class Obstacle {
private:
    my3DModel _model;

    glm::vec3 _position{};
    float     _radius;
    Matrices  _matrices;

public:
    inline Obstacle(const std::string modelName, const glm::vec3& position, const float radius)
        : _position(position), _radius(radius), _model(modelName)
    {
    }

    inline void update(const glm::mat4& viewMatrix){
        _matrices.updateObstacle(viewMatrix, _position, _radius);
    }

    inline void draw(const myProgram& program, const glm::mat4& projMatrix)
    {
        _matrices.sendMatricesToShader(program, projMatrix);
        _model.activateTexture(program);
        _model.draw(program);
    }

    inline void draw(){
        _model.draw();
    }
};