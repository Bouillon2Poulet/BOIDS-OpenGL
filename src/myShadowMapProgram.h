#pragma once
#include "p6/p6.h"

struct myShadowMapProgram {
    p6::Shader m_Program;

    GLuint uLightProjection;
    GLuint uModel;

    myShadowMapProgram()
        : m_Program{p6::load_shader("shaders/ShadowMap.vs.glsl", "shaders/ShadowMap.fs.glsl")}
    {
        m_Program.use();
        uLightProjection    = glGetUniformLocation(m_Program.id(), "uLightProjection");
        uModel    = glGetUniformLocation(m_Program.id(), "uModel");
    }
};