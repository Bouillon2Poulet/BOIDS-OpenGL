#pragma once

#include <p6/p6.h>
#include <chrono>
#include "ShapeVertex.h"

enum class ShapeType {
    sphere,
    cone,
    cube,
    model
};

class Vertices3D {
private:
    GLuint                           _vao{};
    GLuint                           _vbo{};
    std::vector<glimac::ShapeVertex> _vertices{};
    ShapeType                        _shapetype{};

public:
    Vertices3D() = default;
    Vertices3D(ShapeType type, std::string modelName = "");

    void initVAOVBO();
    void bindVertexArrayVAO() const;

    void addVertex(const glimac::ShapeVertex& vertex);

    GLuint                           vao() const;
    GLuint*                          vaoRef();
    GLuint                           vbo() const;
    std::vector<glimac::ShapeVertex> shapeVertices() const;
    int                              size() const;
    void                             vertices(std::vector<glimac::ShapeVertex> vertices);
};