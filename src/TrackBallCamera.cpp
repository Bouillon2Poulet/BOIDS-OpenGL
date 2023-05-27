#include "TrackballCamera.h"

void TrackballCamera::moveFront(float delta)
{
    m_Distance -= delta;
}
void TrackballCamera::rotateLeft(float degrees)
{
    m_AngleX -= degrees;
}
void TrackballCamera::rotateUp(float degrees)
{
    m_AngleY -= degrees;
}

void TrackballCamera::updateArpenteurPosition(const glm::vec3& arpenteurPosition)
{
    _arpenteurPosition = arpenteurPosition;
}

glm::mat4 TrackballCamera::getViewMatrix(const glm::vec3& arpenteurPosition)
{
    glm::mat4 firstTranslation  = glm::translate(glm::mat4(1), -arpenteurPosition);
    glm::mat4 rotationX         = glm::rotate(glm::mat4(1), (p6::degrees_to_radians(m_AngleX)).value, glm::vec3(0, 1, 0));
    glm::mat4 rotationY         = glm::rotate(glm::mat4(1), (p6::degrees_to_radians(m_AngleY)).value, glm::vec3(1, 0, 0));
    glm::mat4 secondTranslation = glm::translate(glm::mat4(1), glm::vec3(0, 0, m_Distance));
    _viewMatrix                 = secondTranslation * rotationY * rotationX * firstTranslation;
    return _viewMatrix;
}

void TrackballCamera::handleDeplacement(p6::Context& ctx)
{
    // KEY
    if (ctx.key_is_pressed(GLFW_KEY_LEFT))
    {
        rotateLeft(1.);
    }
    if (ctx.key_is_pressed(GLFW_KEY_RIGHT))
    {
        rotateLeft(-1.);
    }
    if (ctx.key_is_pressed(GLFW_KEY_DOWN))
    {
        rotateUp(-1.f);
    }
    if (ctx.key_is_pressed(GLFW_KEY_UP))
    {
        rotateUp(1.f);
    }
}
glm::vec3 TrackballCamera::position() const
{
    return _viewMatrix * glm::vec4(0, 0, 0, 1); // La position de la caméra correspond à la dernière colonne de la matrice de vue.
}

glm::vec3 TrackballCamera::getForwardVector() const
{
    glm::mat4 rotationX = glm::rotate(glm::mat4(1), (p6::degrees_to_radians(m_AngleX)).value, glm::vec3(0, 1, 0));
    glm::mat4 rotation  = rotationX;
    return -1.f * (glm::vec3(glm::inverse(rotation) * glm::vec4(0, 0, 1, 0)));
}