#pragma once

#include <p6/p6.h>
#include <chrono>
#include "ShapeVertex.h"

enum class ShapeType {
    sphere,
    cone,
    cube
};

class Vertices3D {
private:
    GLuint                           _vao{};
    GLuint                           _vbo{};
    std::vector<glimac::ShapeVertex> _vertices{};
    ShapeType                        _shapetype;

public:
    Vertices3D(ShapeType type)
        : _shapetype(type)
    {
        switch (_shapetype)
        {
        case ShapeType::cone:
            _vertices = glimac::cone_vertices(1., .5, 4., 4.);
            break;
        case ShapeType::sphere:
            _vertices = glimac::sphere_vertices(1., .5, 4.);
            break;
        case ShapeType::cube:
            _vertices = glimac::cube_vertices(1.);
            break;
        }
        const GLuint SHADER_VERTEX_POS      = 0;
        const GLuint SHADER_VERTEX_NORM     = 1;
        const GLuint SHADER_VERTEX_TEXCOORD = 2;

        // VBO
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glimac::ShapeVertex), _vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // VAO
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        glEnableVertexAttribArray(SHADER_VERTEX_POS);
        glEnableVertexAttribArray(SHADER_VERTEX_NORM);
        glEnableVertexAttribArray(SHADER_VERTEX_TEXCOORD);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

        glVertexAttribPointer(SHADER_VERTEX_POS, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), nullptr);
        glVertexAttribPointer(SHADER_VERTEX_NORM, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (GLvoid*)offsetof(glimac::ShapeVertex, normal));
        glVertexAttribPointer(SHADER_VERTEX_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (GLvoid*)offsetof(glimac::ShapeVertex, texCoords));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    inline void bindVertexArrayVAO()
    {
        glBindVertexArray(_vao);
    }

    // inline ~Vertices3D()
    // {
    //     glDeleteVertexArrays(1, &_vao);
    //     glDeleteBuffers(1, &_vbo);
    // }

    Vertices3D(const Vertices3D& toCopy)
    {
        _vao      = toCopy._vao;
        _vbo      = toCopy._vbo;
        _vertices = _vertices;
    }

    inline GLuint vao() const
    {
        return _vao;
    }
    inline GLuint* vaoRef()
    {
        return &_vao;
    }

    inline GLuint vbo() const
    {
        return _vbo;
    }
    inline std::vector<glimac::ShapeVertex> shapeVertices() const
    {
        return _vertices;
    }
    inline int size() const
    {
        return _vertices.size();
    }
};