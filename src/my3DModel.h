#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Matrices.h"
#include "Vertices3D.h"
#include "glm/fwd.hpp"
#include "my3DModel.h"
#include "myProgram.h"
#include "tiny_obj_loader.h"

struct Material {
    std::string name;
    float       shininess;
    glm::vec3   ambientColor;
    glm::vec3   diffuseColor;
    glm::vec3   specularColor;
};

class my3DModel {
private:
    // MODEL
    GLuint                           _diffuseTexture;
    std::vector<Vertices3D>          _shapes;
    std::vector<tinyobj::material_t> _materials;
    std::string                      _name;
    std::string                      _res;

public:
    my3DModel(const std::string& modelName, const std::string res);

    void draw(const myProgram& program) const;

    void loadObj(const std::string& modelName, const std::string res);
    void load3DModel(const std::string modelName, const std::string res);
    void loadMtlFile(const char* filePath, std::vector<Material>& materials);

    void activateTexture(const myProgram& program);
};