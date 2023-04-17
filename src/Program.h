#pragma once
#include "p6/p6.h"

struct Program {
    p6::Shader m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uOpacity;

    Program()
        : m_Program{p6::load_shader(std::filesystem::current_path().string() + "./../src/shaders/3D.vs.glsl", std::filesystem::current_path().string() + "./../src/shaders/normals.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uOpacity      = glGetUniformLocation(m_Program.id(), "uOpacity");
    }
};