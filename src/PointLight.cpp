#include "PointLight.h"

void PointLight::update(float time, const glm::mat4& viewMatrix, const myProgram& program)
{
    glm::mat4 rotationTime        = viewMatrix * glm::translate(glm::rotate(glm::translate(glm::mat4(1), glm::vec3(0., 1., 0.)), time, glm::vec3(.0, 0., 1.)), glm::vec3(0., 1., 0.));
    glm::vec3 lightPosXViewMatrix = rotationTime * glm::vec4(1);

    program.m_Program.use();
    glUniform3f(program.uLight1Position, lightPosXViewMatrix.x, lightPosXViewMatrix.y, lightPosXViewMatrix.z);
    glUniform3f(program.uLight1Intensity, _lightIntensity.x, _lightIntensity.y, _lightIntensity.z);
}