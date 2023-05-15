#pragma once

#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

class FreeflyCamera {
private:
    glm::vec3 m_Position = {
        0,
        0,
        0,
    };
    float m_Phi   = p6::PI;
    float m_Theta = 0.f;

    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

    glm::vec3 _arpenteurPosition;

    inline void computeDirectionVectors()
    {
        m_FrontVector = glm::vec3(cos(m_Theta) * sin(m_Phi), sin(m_Theta), cos(m_Theta) * cos(m_Phi));
        m_LeftVector  = glm::vec3(sin(m_Phi + p6::PI / 2.f), 0, cos(m_Phi + p6::PI / 2.f));
        m_UpVector    = glm::cross(m_FrontVector, m_LeftVector);
    }

public:
    void updateArpenteurPosition(const glm::vec3& arpenteurPosition)
    {
        _arpenteurPosition = arpenteurPosition;
    }

    glm::vec3 position()
    {
        return m_Position;
    }

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

        // if (ctx.key_is_pressed(GLFW_KEY_DOWN))
        // {
        //     moveFront(-.5f);
        // }
        // if (ctx.key_is_pressed(GLFW_KEY_UP))
        // {
        //     moveFront(.5f);
        // }

        // if (ctx.mouse_dragged && ctx.mouse_button_is_pressed(p6::Button(0)))
        // {
        //     ctx.mouse_dragged = [&](p6::MouseDrag drag) {
        //         rotateLeft(drag.delta.x * 100);
        //         rotateUp(drag.delta.y * 100);
        //     };
        // }
    }
    inline FreeflyCamera()
    {
        computeDirectionVectors();
    }

    inline void moveFront(float distance)
    {
        m_Position += distance * m_FrontVector;
    }
    inline void moveLeft(float distance)
    {
        m_Position += distance * m_LeftVector;
    }

    inline void rotateLeft(float degrees)
    {
        m_Phi -= p6::degrees_to_radians(degrees).value;
        computeDirectionVectors();
    }
    inline void rotateUp(float degrees)
    {
        m_Theta -= p6::degrees_to_radians(degrees).value;
    }

    inline glm::mat4 getViewMatrix()
    {
        computeDirectionVectors();
        return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
    }
};