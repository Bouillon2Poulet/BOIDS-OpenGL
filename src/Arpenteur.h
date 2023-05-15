#pragma once

#include "Drawing.h"
#include "GLFW/glfw3.h"
#include "Matrices.h"
#include "MovementVariables.h"
#include "Vertices3D.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "my3DModel.h"
#include "myProgram.h"

class Arpenteur {
private:
    MovementVariables _mvtVariables;
    Matrices          _matrices{};
    Vertices3D        _vertices3D;
    float             _width = 1.f;

    p6::Color _color  = {1.f, .5f, .5f};
    float     _radius = .5f;

    my3DModel _model;

public:
    Arpenteur(const glm::vec3& maxDistanceFromCenter)
        : _mvtVariables(maxDistanceFromCenter), _vertices3D(ShapeType::cube), _model("arpenteur","")
    {
    }
    inline void update(const p6::Context& ctx, const glm::mat4& viewMatrix, const glm::vec3& maxDistanceFromCenter, glm::vec3 cameraDirection) // Only take ctx.mouse() as a param
    {
        // Get the camera direction and up vector
        cameraDirection = glm::normalize(cameraDirection) * 0.1f;
        glm::vec3 cameraUp        = glm::vec3(0, 1, 0);

        // Get the "right" vector using the cross product of camera direction and up vector
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraDirection, cameraUp));

        // KEY
        if (ctx.key_is_pressed(GLFW_KEY_A)) // LEFT
        {
            _mvtVariables._position += cameraRight * 0.1f;
            if (_mvtVariables._position.x - _width / 2 < -maxDistanceFromCenter.x / 2)
                _mvtVariables._position.x = (-maxDistanceFromCenter.x + _width) / 2;
        }
        if (ctx.key_is_pressed(GLFW_KEY_D)) // RIGHT
        {
            _mvtVariables._position -= cameraRight * 0.1f;
            if (_mvtVariables._position.x + _width / 2 > maxDistanceFromCenter.x / 2)
                _mvtVariables._position.x = (maxDistanceFromCenter.x - _width) / 2;
        }
        if (ctx.key_is_pressed(GLFW_KEY_S)) // BACK
        {
            _mvtVariables._position += glm::normalize(cameraDirection) * 0.1f;
            if (_mvtVariables._position.z - _width / 2 < -maxDistanceFromCenter.z / 2)
                _mvtVariables._position.z = (-maxDistanceFromCenter.z + _width) / 2;
        }
        if (ctx.key_is_pressed(GLFW_KEY_W)) // FRONT
        {
            _mvtVariables._position -= glm::normalize(cameraDirection) * 0.1f;
            if (_mvtVariables._position.z + _width / 2 > maxDistanceFromCenter.z / 2)
                _mvtVariables._position.z = (maxDistanceFromCenter.z - _width) / 2;
        }

        if (ctx.key_is_pressed(GLFW_KEY_SPACE))
        {
            _mvtVariables._position.y += 0.1;
        }

        if (ctx.key_is_pressed(GLFW_KEY_Q))
        {
            _mvtVariables._position.y -= 0.1;
        }

        _matrices.update(_mvtVariables._position, _radius,  -1.f*cameraDirection, viewMatrix);
    }
    inline void draw(const myProgram& program, const glm::mat4& projMatrix)
    {
        _model.activateTexture(program);
        _matrices.sendMatricesToShader(program, projMatrix);
        _model.draw(program);
    }

    inline glm::vec3 position()
    {
        return _mvtVariables._position;
    }
};