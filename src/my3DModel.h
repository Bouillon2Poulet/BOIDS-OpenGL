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
    GLuint      _texture;

public:
    my3DModel(const std::string& modelName, const glm::vec3& position, const float radius)
        : _vertices(ShapeType::model, modelName), _position(position), _radius(radius)
    {
        auto textureImage = p6::load_image_buffer("./assets/"+modelName+"/"+modelName+".jpg");
        glGenTextures(1, &_texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
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