#pragma once

#include "Program.h"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "p6/p6.h"

struct Matrices {
    glm::mat4 _MVMatrixFish{};
    glm::mat4 _NormalMatrix{};

    inline void update(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& velocity, const glm::mat4& viewMatrix)
    {
        glm::vec3 up        = glm::vec3(1.0, 0.0, 0.0); // Vecteur vertical arbitraire
        glm::vec3 eye       = position;                 // Position de la caméra arbitraire, ici centrée sur l'origine
        glm::vec3 center    = eye + velocity;           // Position cible de la caméra correspondant à la vélocité
        glm::mat3 rotation  = glm::lookAt(eye, center, up);
        glm::mat4 rotation4 = glm::mat4(glm::vec4(rotation[0], 0.0), glm::vec4(rotation[1], 0.0), glm::vec4(rotation[2], 0.0), glm::vec4(0.0, 0.0, 0.0, 1.0));
        // _MVMatrixFish       = viewMatrix * rotation4 * glm::scale(glm::translate(glm::mat4(1), position), scale);

        _MVMatrixFish = viewMatrix * glm::translate(glm::mat4(1), position);
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

    inline void sendMatricesToShader(const Program& program, const glm::mat4& projMatrix) const
    {
        glUniformMatrix4fv(program.uMVPMatrix, 1, false, glm::value_ptr(projMatrix * _MVMatrixFish));
        glUniformMatrix4fv(program.uMVMatrix, 1, false, glm::value_ptr(_MVMatrixFish));
        glUniformMatrix4fv(program.uNormalMatrix, 1, false, glm::value_ptr(_NormalMatrix));
    }
};