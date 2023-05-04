#pragma once

#include "Matrices.h"
#include "Vertices3D.h"
#include "glm/fwd.hpp"
class my3DModel {
private:
    Vertices3D _vertices;
    glm::vec3  _position{};
    float      _radius;
    Matrices   _matrices;

public:
    my3DModel(const std::string& modelName, const glm::vec3& position, const float radius)
        : _vertices(ShapeType::model, modelName), _position(position), _radius(radius)
    {
    }

    void draw(const Program& program, const glm::mat4& projMatrix)
    {
        _matrices.sendMatricesToShader(program, projMatrix);
        _vertices.bindVertexArrayVAO();
        glDrawArrays(GL_TRIANGLES, 0, _vertices.shapeVertices().size());
    }

    void update(const glm::mat4& viewMatrix)
    {
        _matrices.updateEnvironment(viewMatrix, _position, _radius);
    }
};