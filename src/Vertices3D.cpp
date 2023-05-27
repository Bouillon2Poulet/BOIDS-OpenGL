#include "Vertices3D.h"

Vertices3D::Vertices3D(ShapeType type, std::string modelName)
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
    case ShapeType::model:
        _vertices = glimac::load3DModel(modelName);
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

void Vertices3D::initVAOVBO()
{
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

void Vertices3D::bindVertexArrayVAO() const
{
    glBindVertexArray(_vao);
}

void Vertices3D::addVertex(const glimac::ShapeVertex& vertex)
{
    _vertices.push_back(vertex);
}

GLuint Vertices3D::vao() const
{
    return _vao;
}
GLuint* Vertices3D::vaoRef()
{
    return &_vao;
}

GLuint Vertices3D::vbo() const
{
    return _vbo;
}
std::vector<glimac::ShapeVertex> Vertices3D::shapeVertices() const
{
    return _vertices;
}
int Vertices3D::size() const
{
    return _vertices.size();
}

void Vertices3D::vertices(std::vector<glimac::ShapeVertex> vertices)
{
    _vertices = vertices;
}