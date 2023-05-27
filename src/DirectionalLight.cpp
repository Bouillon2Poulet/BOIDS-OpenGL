#include "DirectionalLight.h"

void DirectionalLight::update(const myProgram& program)
{
    program.m_Program.use();
    glUniform3f(program.uLight2Direction, _direction.x, _direction.y, _direction.z);
    glUniform3f(program.uLight2Intensity, _lightIntensity.x, _lightIntensity.y, _lightIntensity.z);
}