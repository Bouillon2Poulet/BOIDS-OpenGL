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
    GLint                uMVPMatrix;
    GLint                uMVMatrix;
    GLint                uNormalMatrix;
    GLint                uOpacity;
    GLint                uTexture;

    GLint uLight1Position;
    GLint uLight1Intensity;
    GLint uLight2Direction;
    GLint uLight2Intensity;

    myProgram()
        : m_Program{p6::load_shader("shaders/3D.vs.glsl", "shaders/normals.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uOpacity      = glGetUniformLocation(m_Program.id(), "uOpacity");
        uTexture      = glGetUniformLocation(m_Program.id(), "uTexture");

        // uMaterial.uAmbient    = glGetUniformLocation(m_Program.id(), "uAmbient");
        uMaterial.uDiffuse   = glGetUniformLocation(m_Program.id(), "uDiffuse");
        uMaterial.uSpecular  = glGetUniformLocation(m_Program.id(), "uSpecular");
        uMaterial.uShininess = glGetUniformLocation(m_Program.id(), "uShininess");

        uLight1Position  = glGetUniformLocation(m_Program.id(), "uLight1Position");
        uLight1Intensity = glGetUniformLocation(m_Program.id(), "uLight1Intensity");
        uLight2Direction = glGetUniformLocation(m_Program.id(), "uLight2Direction");
        uLight2Intensity = glGetUniformLocation(m_Program.id(), "uLight2Intensity");
    }
};