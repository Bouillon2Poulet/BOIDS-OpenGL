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

    LoDs _lods;

public:
    Obstacle(const std::string modelName, const glm::vec3& position, const float radius);

    void update(const glm::mat4& viewMatrix);
    void draw(const myProgram& program, const glm::mat4& projMatrix, const glm::vec3 cameraPosition);
};