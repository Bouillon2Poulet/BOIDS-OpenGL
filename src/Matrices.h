#pragma once

#include "myProgram.h"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "p6/p6.h"

struct Matrices {
    glm::mat4 _MVMatrixFish{};
    glm::mat4 _NormalMatrix{};

    inline void update(const glm::vec3& position, const float radius, const glm::vec3& velocity, const glm::mat4& viewMatrix)
    {
        glm::vec3 direction = glm::normalize(velocity);

        // Rotation sur Y
        glm::vec3 targetY   = glm::vec3(0.0f, 0.0f, -1.0f);
        float     angleY    = glm::orientedAngle(targetY, direction, glm::vec3(0.0f, 1.0f, 0.0f));

        // Rotation sur X
        glm::vec3 targetX   = glm::vec3(0.0f, direction.y, -glm::length(glm::vec2(direction.x, direction.z)));
        float     angleX    = glm::orientedAngle(glm::vec3(0.0f, 0.0f, -1.0f), targetX, glm::vec3(1.0f, 0.0f, 0.0f));

        // Calcul de la nouvelle matrice de modèle
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(radius));
        modelMatrix           = glm::rotate(modelMatrix, angleY, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix           = glm::rotate(modelMatrix, angleX, glm::vec3(1.0f, 0.0f, 0.0f));

        // Calculer la nouvelle matrice de modèle-vue
        _MVMatrixFish = viewMatrix * modelMatrix;

        // Calculer la nouvelle matrice de normalisation
        _NormalMatrix = glm::transpose(glm::inverse(_MVMatrixFish));
    }

    inline void updateObstacle(const glm::mat4 viewMatrix, const glm::vec3& position, const float radius)
    {
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(radius));
        _MVMatrixFish = viewMatrix * modelMatrix;
        _NormalMatrix = glm::transpose(glm::inverse(_MVMatrixFish));
    }

    inline void updateBB(const glm::mat4 viewMatrix, const glm::vec3& maxDistanceFromCenter)
    {
        _MVMatrixFish = viewMatrix * glm::scale(maxDistanceFromCenter);
        _NormalMatrix = glm::transpose(glm::inverse(_MVMatrixFish));
    }

    inline void updateArpenteur(const glm::mat4 viewMatrix, const glm::vec3& position)
    {
        _MVMatrixFish = viewMatrix * glm::translate(glm::mat4(1), position);
        _NormalMatrix = glm::transpose(glm::inverse(_MVMatrixFish));
    }

    inline void sendMatricesToShader(const myProgram& program, const glm::mat4& projMatrix) const
    {
        glUniformMatrix4fv(program.uMVPMatrix, 1, false, glm::value_ptr(projMatrix * _MVMatrixFish));
        glUniformMatrix4fv(program.uMVMatrix, 1, false, glm::value_ptr(_MVMatrixFish));
        glUniformMatrix4fv(program.uNormalMatrix, 1, false, glm::value_ptr(_NormalMatrix));
    }
};