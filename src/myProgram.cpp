#include "myProgram.h"

myProgram::myProgram()
        : m_Program{p6::load_shader("shaders/3D.vs.glsl", "shaders/lightsFS.fs.glsl")}
    {
        uMVPMatrix    = glGetUniformLocation(m_Program.id(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.id(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.id(), "uNormalMatrix");
        uOpacity      = glGetUniformLocation(m_Program.id(), "uOpacity");
        uTexture      = glGetUniformLocation(m_Program.id(), "uTexture");

        uMaterial.uDiffuse   = glGetUniformLocation(m_Program.id(), "uDiffuse");
        uMaterial.uSpecular  = glGetUniformLocation(m_Program.id(), "uSpecular");
        uMaterial.uShininess = glGetUniformLocation(m_Program.id(), "uShininess");

        uGUILightActivation.uGUIPointLight = glGetUniformLocation(m_Program.id(), "uGUIPointLight");
        uGUILightActivation.uGUIDirectionalLight = glGetUniformLocation(m_Program.id(), "uGUIDirectionalLight");
        uGUILightActivation.uGUIAmbientLight = glGetUniformLocation(m_Program.id(), "uGUIAmbientLight");


        uLight1Position  = glGetUniformLocation(m_Program.id(), "uLight1Position");
        uLight1Intensity = glGetUniformLocation(m_Program.id(), "uLight1Intensity");
        uLight2Direction = glGetUniformLocation(m_Program.id(), "uLight2Direction");
        uLight2Intensity = glGetUniformLocation(m_Program.id(), "uLight2Intensity");
    }