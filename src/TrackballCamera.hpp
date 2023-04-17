#pragma once

#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class TrackballCamera {
private:
    float m_Distance = -2.f;
    float m_AngleX   = 0.f;
    float m_AngleY   = 0.f;

public:
    inline void moveFront(float delta)
    {
        m_Distance -= delta;
    }
    inline void rotateLeft(float degrees)
    {
        m_AngleX -= degrees;
    }
    inline void rotateUp(float degrees)
    {
        m_AngleY -= degrees;
    }

    inline glm::mat4 getViewMatrix() const
    {
        glm::mat4 translation = glm::translate(glm::mat4(1), glm::vec3(.0f, .0f, m_Distance));
        glm::mat4 rotationX   = glm::rotate(glm::mat4(1), (p6::degrees_to_radians(m_AngleX)).value, glm::vec3(0, 1, 0));
        glm::mat4 rotationY   = glm::rotate(glm::mat4(1), (p6::degrees_to_radians(m_AngleY)).value, glm::vec3(1, 0, 0));

        return translation * rotationY * rotationX;
    }

    public:
    void handleDeplacement(p6::Context& ctx)
    {
        // KEY
        if (ctx.key_is_pressed(GLFW_KEY_LEFT))
        {
            rotateLeft(.5);
        }
        if (ctx.key_is_pressed(GLFW_KEY_RIGHT))
        {
            rotateLeft(-.5);
        }
        if (ctx.key_is_pressed(GLFW_KEY_DOWN))
        {
            moveFront(-.5f);
        }
        if (ctx.key_is_pressed(GLFW_KEY_UP))
        {
            moveFront(.5f);
        }

        if (ctx.mouse_dragged && ctx.mouse_button_is_pressed(p6::Button(0)))
        {
            ctx.mouse_dragged = [&](p6::MouseDrag drag) {
                rotateLeft(drag.delta.x * 100);
                rotateUp(drag.delta.y * 100);
            };
        }
    }
};