#pragma once
#include "p6/p6.h"

struct myDebugDepthQuadProgram {
    p6::Shader m_Program;

    GLuint u;
    // GLuint uModel;

    myDebugDepthQuadProgram()
        : m_Program{p6::load_shader("shaders/DebugDepthQuad.vs.glsl", "shaders/DebugDepthQuad.fs.glsl")}
    {
        // m_Program.use();
        // uLightProjection    = glGetUniformLocation(m_Program.id(), "uLightProjection");
    }
};