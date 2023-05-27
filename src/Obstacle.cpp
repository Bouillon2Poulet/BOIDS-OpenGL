#include "Obstacle.h"

Obstacle::Obstacle(const std::string modelName, const glm::vec3& position, const float radius)
    : _position(position), _radius(radius), _lods(modelName)
{
}

void Obstacle::update(const glm::mat4& viewMatrix)
{
    _matrices.updateObstacle(viewMatrix, _position, _radius);
}

void Obstacle::draw(const myProgram& program, const glm::mat4& projMatrix, const glm::vec3 cameraPosition)
{
    _matrices.sendMatricesToShader(program, projMatrix);

    _lods.getRightModel(glm::length(_position - cameraPosition)).activateTexture(program);
    _lods.getRightModel(glm::length(_position - cameraPosition)).draw(program);
}