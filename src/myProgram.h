#pragma once
#include "p6/p6.h"

struct myProgram {
    p6::Shader m_Program;

    struct MaterialInfoLocation {
        GLint uDiffuse;
        GLint uSpecular;
        GLint uShininess;
    };

    struct GUILightActivation{
        GLint uGUIPointLight;
        GLint uGUIDirectionalLight;
        GLint uGUIAmbientLight;
    };

    MaterialInfoLocation uMaterial;
    GUILightActivation uGUILightActivation;

    GLint                uMVPMatrix;
    GLint                uMVMatrix;
    GLint                uNormalMatrix;
    GLint                uOpacity;
    GLint                uTexture;

    GLint uLight1Position;
    GLint uLight1Intensity;
    GLint uLight2Direction;
    GLint uLight2Intensity;

    myProgram();
};