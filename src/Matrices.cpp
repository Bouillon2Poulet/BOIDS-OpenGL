#include "Matrices.h"

void Matrices::updateFishOrArpenteur(const glm::vec3& position, const float radius, const glm::vec3& velocity, const glm::mat4& viewMatrix)
{
    glm::vec3 direction = glm::normalize(velocity);

    // Rotation sur Y
    glm::vec3 targetY = glm::vec3(0.0f, 0.0f, -1.0f);
    float     angleY  = glm::orientedAngle(targetY, direction, glm::vec3(0.0f, 1.0f, 0.0f));

    // Rotation sur X
    glm::vec3 targetX = glm::vec3(0.0f, direction.y, -glm::length(glm::vec2(direction.x, direction.z)));
    float     angleX  = glm::orientedAngle(glm::vec3(0.0f, 0.0f, -1.0f), targetX, glm::vec3(1.0f, 0.0f, 0.0f));

    // Calcul de la nouvelle matrice de modèle
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(radius));
    modelMatrix           = glm::rotate(modelMatrix, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix           = glm::rotate(modelMatrix, angleX, glm::vec3(1.0f, 0.0f, 0.0f));

    // Calculer la nouvelle matrice de modèle-vue
    _MVMatrix = viewMatrix * modelMatrix;

    // Calculer la nouvelle matrice de normalisation
    _NormalMatrix = glm::transpose(glm::inverse(_MVMatrix));
}

void Matrices::updateTurbine(const glm::vec3& position, const float radius, const glm::vec3& velocity, const glm::mat4& viewMatrix, float turbineAngleAsDegrees)
{
    glm::vec3 direction = glm::normalize(velocity);

    // Rotation sur Y
    glm::vec3 targetY = glm::vec3(0.0f, 0.0f, -1.0f);
    float     angleY  = glm::orientedAngle(targetY, direction, glm::vec3(0.0f, 1.0f, 0.0f));

    // Rotation sur X
    glm::vec3 targetX = glm::vec3(0.0f, direction.y, -glm::length(glm::vec2(direction.x, direction.z)));
    float     angleX  = glm::orientedAngle(glm::vec3(0.0f, 0.0f, -1.0f), targetX, glm::vec3(1.0f, 0.0f, 0.0f));

    // Calcul de la nouvelle matrice de modèle
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(radius));
    modelMatrix           = glm::rotate(modelMatrix, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix           = glm::rotate(modelMatrix, angleX, glm::vec3(1.0f, 0.0f, 0.0f));

    // Rotation sur Z
    float angleZ = p6::degrees_to_radians(turbineAngleAsDegrees).value;
    modelMatrix  = glm::rotate(modelMatrix, angleZ, glm::vec3(0.0f, 0.0f, 1.0f));

    // Calculer la nouvelle matrice de modèle-vue
    _MVMatrix = viewMatrix * modelMatrix;

    // Calculer la nouvelle matrice de normalisation
    _NormalMatrix = glm::transpose(glm::inverse(_MVMatrix));
}

void Matrices::updateObstacle(const glm::mat4 viewMatrix, const glm::vec3& position, const float radius)
{
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(radius));
    _MVMatrix             = viewMatrix * modelMatrix;
    _NormalMatrix         = glm::transpose(glm::inverse(_MVMatrix));
}

void Matrices::updateBB(const glm::mat4 viewMatrix, const glm::vec3& maxDistanceFromCenter)
{
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), {}) * glm::scale(glm::mat4(1.0f), maxDistanceFromCenter/2.f);
    _MVMatrix     = viewMatrix * modelMatrix;
    _NormalMatrix = glm::transpose(glm::inverse(_MVMatrix));
}

void Matrices::updateArpenteur(const glm::vec3& position, const float radius, const glm::mat4 viewMatrix)
{
    _MVMatrix = viewMatrix * glm::scale(glm::mat4(1), glm::vec3(radius)) * glm::translate(glm::mat4(1), position);

    _NormalMatrix = glm::transpose(glm::inverse(_MVMatrix));
}

void Matrices::sendMatricesToShader(const myProgram& program, const glm::mat4& projMatrix) const
{
    glUniformMatrix4fv(program.uMVPMatrix, 1, false, glm::value_ptr(projMatrix * _MVMatrix));
    glUniformMatrix4fv(program.uMVMatrix, 1, false, glm::value_ptr(_MVMatrix));
    glUniformMatrix4fv(program.uNormalMatrix, 1, false, glm::value_ptr(_NormalMatrix));
}