#pragma once
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "myProgram.h"
#include "p6/p6.h"

class PointLight {
private:
    // glm::vec3 _position = {10.f, .0f, .0f};
    // float     radius = 10.f;
    // glm::vec3 _direction{-1.f, .0f, .0f};
    glm::vec3 _lightIntensity = {0.f, 4.f, 1.f};
    // glm::vec3 _lightPosition  = {1.f, 0.f, 0.f};

public:
    inline void update(float time, const glm::mat4& viewMatrix, const myProgram& program)
    {
        // glm::vec3 lightDir = (glm::rotate(glm::mat4(1), time, glm::vec3(0., 0., 1.)) * glm::vec4(1) * viewMatrix);
       
        glm::mat4 rotationTime        = viewMatrix * glm::rotate(glm::mat4(1), time, glm::vec3(.0, 0., 1.));
        glm::vec3 lightPosXViewMatrix = rotationTime * glm::vec4(3.,0., 0.0, 1.0);
        // glm::vec3 lightPosXViewMatrix = glm::vec4(0., 5.0, 0.0, 1.0);

        program.m_Program.use();
        glUniform3f(program.uLight1Position, lightPosXViewMatrix.x, lightPosXViewMatrix.y, lightPosXViewMatrix.z);
        glUniform3f(program.uLight1Intensity, _lightIntensity.x, _lightIntensity.y, _lightIntensity.z);
    }
};