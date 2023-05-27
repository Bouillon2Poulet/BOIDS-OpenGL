#pragma once

#include <string>
#include "Lods.h"
#include "Matrices.h"
#include "my3DModel.h"
#include "p6/p6.h"

class CubeMap {
private:
    Matrices            _matrices;
    my3DModel           _model;
    std::vector<GLuint> _animTextures;

public:
    CubeMap();
    void loadAnimTextures();
    void activateRightAnimTexture(const myProgram& program, float time);
    void draw(const myProgram& program, const glm::mat4& projMatrix, const glm::mat4& viewMatrix, float time);
};