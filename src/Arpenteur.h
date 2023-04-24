#pragma once

#include "Drawing.h"
#include "Matrices.h"
#include "MovementVariables.h"
#include "Program.h"
#include "Vertices3D.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"

class Arpenteur {
private:
    MovementVariables _mvtVariables;
    Matrices          _matrices{};
    Vertices3D        _vertices3D;
    float             _width = 1.f;

    p6::Color _color  = {1.f, .5f, .5f};
    float     _radius = .05f;

public:
    Arpenteur(const glm::vec3& maxDistanceFromCenter)
        : _mvtVariables(maxDistanceFromCenter), _vertices3D(ShapeType::cube)
    {
    }
    inline void update(const p6::Context& ctx, const glm::mat4& viewMatrix, const glm::vec3& maxDistanceFromCenter) // Only take ctx.mouse() as a param
    {
        // KEY
        if (ctx.key_is_pressed(GLFW_KEY_A))
        {
            _mvtVariables._position.x -= 0.1;
            if (_mvtVariables._position.x - _width / 2 < -maxDistanceFromCenter.x / 2)
                _mvtVariables._position.x = (-maxDistanceFromCenter.x + _width) / 2;
        }
        if (ctx.key_is_pressed(GLFW_KEY_D))
        {
            _mvtVariables._position.x += 0.1;
            if (_mvtVariables._position.x + _width / 2 > maxDistanceFromCenter.x / 2)
                _mvtVariables._position.x = (maxDistanceFromCenter.x - _width) / 2;
        }
        if (ctx.key_is_pressed(GLFW_KEY_S))
        {
            _mvtVariables._position.z += 0.1;
            if (_mvtVariables._position.z - _width / 2 < -maxDistanceFromCenter.z / 2)
                _mvtVariables._position.z = (-maxDistanceFromCenter.z + _width) / 2;
        }
        if (ctx.key_is_pressed(GLFW_KEY_W))
        {
            _mvtVariables._position.z -= 0.1;
            if (_mvtVariables._position.z + _width / 2 > maxDistanceFromCenter.z / 2)
                _mvtVariables._position.z = (maxDistanceFromCenter.z - _width) / 2;
        }

        _matrices.updateArpenteur(viewMatrix, _mvtVariables._position);
    }
    inline void draw(const Program& program, const glm::mat4& projMatrix)
    {
        _matrices.sendMatricesToShader(program, projMatrix);
        std::cout << _mvtVariables._position.x << "," << _mvtVariables._position.y << "," << _mvtVariables._position.z << std::endl;
        _vertices3D.bindVertexArrayVAO();
        glDrawArrays(GL_TRIANGLES, 0, _vertices3D.shapeVertices().size());
        glBindVertexArray(0);
    }

    inline glm::vec3 position()
    {
        return _mvtVariables._position;
    }
};