#pragma once

#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "myProgram.h"
#include "p6/p6.h"

struct Matrices {
    glm::mat4 _MVMatrix{};
    glm::mat4 _NormalMatrix{};

    void updateFishOrArpenteur(const glm::vec3& position, const float radius, const glm::vec3& velocity, const glm::mat4& viewMatrix);
    void updateTurbine(const glm::vec3& position, const float radius, const glm::vec3& velocity, const glm::mat4& viewMatrix, float turbineAngleAsDegrees);
    void updateObstacle(const glm::mat4 viewMatrix, const glm::vec3& position, const float radius);
    void updateCubeMap(const glm::mat4 viewMatrix, const glm::vec3& cubeMapSize);
    void updateBB(const glm::mat4 viewMatrix, const glm::vec3& maxDistanceFromCenter);
    void updateArpenteur(const glm::vec3& position, const float radius, const glm::mat4 viewMatrix);

    void sendMatricesToShader(const myProgram& program, const glm::mat4& projMatrix) const;
};