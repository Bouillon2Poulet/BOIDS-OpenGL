#pragma once

#include <filesystem>
#include "Matrices.h"
#include "Vertices3D.h"
#include "glm/fwd.hpp"
#include "myProgram.h"
#include "myTexture.h"
#include "tiny_obj_loader.h"

class my3DModel {
private:
    // MODEL
    GLuint _diffuseTexture;
    // tinyobj::attrib_t                _attrib;
    std::vector<Vertices3D>          _shapes;
    std::vector<tinyobj::material_t> _materials;
    GLuint                           _vao{};
    GLuint                           _vbo{};

    // Vertices3D _vertices;

    glm::vec3 _position{};
    float     _radius;
    Matrices  _matrices;
    // myTexture _texture; // Material

public:
    my3DModel(const std::string& modelName, const glm::vec3& position, const float radius)
        : _position(position), _radius(radius)
    {
        loadObj(modelName);
        for (auto& shape : _shapes)
        {
            shape.initVAOVBO();
        }
        // loadVAOVBO();
    }

    void draw(const myProgram& program, const glm::mat4& projMatrix)
    {
        std::cout << _position.x << "//" << _position.y << "//" << _position.z << std::endl;
        _matrices.sendMatricesToShader(program, projMatrix);
        // bindVertexArrayVAO();
        activateTexture(program);

        for (int i = 0; i < _shapes.size(); i++)
        {
            std::cout << "!" << std::endl;
            const tinyobj::material_t& material = _materials[i];
            std::cout << "!!" << std::endl;

            // // glUniform3fv(program.uMaterial.uAmbient, 1, &material.ambient[0]);
            glUniform3fv(program.uMaterial.uDiffuse, 1, &material.diffuse[0]);
            glUniform3fv(program.uMaterial.uSpecular, 1, &material.specular[0]);
            glUniform1f(program.uMaterial.uShininess, material.shininess);

            _shapes[i].bindVertexArrayVAO();
            glDrawArrays(GL_TRIANGLES, 0, _shapes[i].shapeVertices().size());
            // glDrawArrays(GL_TRIANGLES, 0, _vertices.shapeVertices().size());
            glBindVertexArray(0);
        }
    }

    void update(const glm::mat4& viewMatrix)
    {
        _matrices.updateEnvironment(viewMatrix, _position, _radius);
    }

    inline void bindVertexArrayVAO()
    {
        glBindVertexArray(_vao);
    }

    inline void activateTexture(const myProgram& program)
    {
        glUniform1i(program.uTexture, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _diffuseTexture);
    }

    // inline void loadVAOVBO()
    // {
    //     const GLuint SHADER_VERTEX_POS      = 0;
    //     const GLuint SHADER_VERTEX_NORM     = 1;
    //     const GLuint SHADER_VERTEX_TEXCOORD = 2;

    //     std::vector<tinyobj::real_t> allDatas;
    //     for (size_t i = 0; i < _attrib.vertices.size() / 3; i++)
    //     {
    //         Vertices
    //         allDatas.push_back(_attrib.vertices[3 * i + 0]);
    //         allDatas.push_back(_attrib.vertices[3 * i + 1]);
    //         allDatas.push_back(_attrib.vertices[3 * i + 2]);

    //         Normals
    //         allDatas.push_back(_attrib.normals[3 * i + 0]);
    //         allDatas.push_back(_attrib.normals[3 * i + 1]);
    //         allDatas.push_back(_attrib.normals[3 * i + 2]);

    //         Texcoords
    //         allDatas.push_back(_attrib.texcoords[2 * i + 0]);
    //         allDatas.push_back(_attrib.texcoords[2 * i + 1]);
    //     }

    //     VBO
    //     glGenBuffers(1, &_vbo);
    //     glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(tinyobj::real_t) * allDatas.size(), allDatas.data(), GL_STATIC_DRAW);
    //     glBindBuffer(GL_ARRAY_BUFFER, 0);

    //     VAO
    //     glGenVertexArrays(1, &_vao);
    //     glBindVertexArray(_vao);

    //     glEnableVertexAttribArray(SHADER_VERTEX_POS);
    //     glEnableVertexAttribArray(SHADER_VERTEX_NORM);
    //     glEnableVertexAttribArray(SHADER_VERTEX_TEXCOORD);

    //     glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    //     glVertexAttribPointer(SHADER_VERTEX_POS, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(tinyobj::real_t), allDatas.data());
    //     glVertexAttribPointer(SHADER_VERTEX_NORM, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(tinyobj::real_t), allDatas.data() + 3);
    //     glVertexAttribPointer(SHADER_VERTEX_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(tinyobj::real_t), allDatas.data() + 6);

    //     glBindBuffer(GL_ARRAY_BUFFER, 0);
    //     glBindVertexArray(0);
    // }

    void loadObj(const std::string& modelName)
    {
        // Loading
        // std::string objPath = "models/" + modelName + "/" + modelName + ".obj";
        // std::string mtlPath = "models/" + modelName + "/";

        // std::string       err, warn;
        // tinyobj::attrib_t attribTemp;

        load3DModel(modelName);
        // bool        ret = tinyobj::LoadObj(&attribTemp, &_shapes, &_materials, &err, &warn, objPath.c_str(), mtlPath.c_str());

        // if (!ret)
        // {
        //     std::cerr << "ERREUR CHARGEMENT MODELE : " << err << std::endl;
        // }

        // Load diffuse texture
        auto textureImage = p6::load_image_buffer("./models/" + modelName + "/" + modelName + ".jpg");
        glGenTextures(1, &_diffuseTexture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _diffuseTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    inline void load3DModel(const std::string modelName)

    {
        // Loading
        tinyobj::attrib_t                attribTemp;
        std::vector<tinyobj::material_t> materialsTemp;
        std::vector<tinyobj::shape_t>    shapesTemp;

        std::string objPath = "models/" + modelName + "/" + modelName + ".obj";
        std::string mtlPath = "models/" + modelName + "/";

        std::string err;
        std::string warn;

        bool ret = tinyobj::LoadObj(&attribTemp, &shapesTemp, &_materials, &err, &warn, objPath.c_str(), mtlPath.c_str());
        std::cout << err << std::endl;
        if (!ret)
        {
            std::cout << "ERREUR CHARGEMENT MODELE" << std::endl;
        }
        // -> ShapeVertex

        // Pour chaque forme dans le fichier .obj
        for (const auto& shape : shapesTemp)
        {
            Vertices3D                       temp;
            std::vector<glimac::ShapeVertex> vertices;

            // Pour chaque face dans la forme
            for (const auto& index : shape.mesh.indices)
            {
                glimac::ShapeVertex vertex;
                const auto          posIndex      = 3 * index.vertex_index;
                const auto          normIndex     = 3 * index.normal_index;
                const auto          texCoordIndex = 2 * index.texcoord_index;

                if (posIndex + 2 < attribTemp.vertices.size())
                {
                    vertex.position = {
                        attribTemp.vertices[posIndex + 0],
                        attribTemp.vertices[posIndex + 1],
                        attribTemp.vertices[posIndex + 2]};
                }
                if (normIndex + 2 < attribTemp.normals.size())
                {
                    vertex.normal = {
                        attribTemp.normals[normIndex + 0],
                        attribTemp.normals[normIndex + 1],
                        attribTemp.normals[normIndex + 2]};
                }
                if (texCoordIndex + 1 < attribTemp.texcoords.size())
                {
                    vertex.texCoords = {
                        attribTemp.texcoords[texCoordIndex + 0],
                        attribTemp.texcoords[texCoordIndex + 1]};
                }
                vertices.push_back(vertex);
            }
            temp.vertices(vertices);
            _shapes.push_back(temp);
        }
    }
};