#pragma once
#include "p6/p6.h"

struct myProgram {
    p6::Shader m_Program;

    struct MaterialInfoLocation {
        // GLint uAmbient;
        GLint uDiffuse;
        GLint uSpecular;
        GLint uShininess;
    };

    MaterialInfoLocation uMaterial;
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uOpacity;
    GLint uTexture;

    myProgram()
        : m_Program{p6::load_shader("shaders/3D.vs.glsl", "shaders/normals.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uOpacity      = glGetUniformLocation(m_Program.id(), "uOpacity");
        uTexture = glGetUniformLocation(m_Program.id(), "uTexture");

        // uMaterial.uAmbient    = glGetUniformLocation(m_Program.id(), "uAmbient");
        uMaterial.uDiffuse    = glGetUniformLocation(m_Program.id(), "uDiffuse");
        uMaterial.uSpecular    = glGetUniformLocation(m_Program.id(), "uSpecular");
        uMaterial.uShininess    = glGetUniformLocation(m_Program.id(), "uShininess");
    }
};