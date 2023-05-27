#pragma once

#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class TrackballCamera {
private:
    float     m_Distance = -5.f;
    float     m_AngleX   = 0.f;
    float     m_AngleY   = 0.f;
    glm::vec3 _arpenteurPosition{};
    glm::mat4 _viewMatrix;

public:
    void updateArpenteurPosition(const glm::vec3& arpenteurPosition);

    // Movement
    void moveFront(float delta);
    void rotateLeft(float degrees);
    void rotateUp(float degrees);
    void handleDeplacement(p6::Context& ctx);

    glm::mat4        getViewMatrix(const glm::vec3& arpenteurPosition);
    glm::vec3 getForwardVector() const;
    glm::vec3        position() const;
};