#pragma once

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "myDebugDepthQuadProgram.h"
#include "myProgram.h"
#include "myShadowMapProgram.h"
#include "p6/p6.h"

class ShadowMap {
private:
    int       _width  = 2048;
    int       _height = 2048;
    GLuint    _shadowMapFBO{};
    GLuint    _shadowMap{};
    float     _clampColor[4] = {1.f, 1.f, 1.f, 1.f};
    glm::mat4 _lightSpaceMatrix{};

    myShadowMapProgram _program;
    myDebugDepthQuadProgram _debugDepthProgram;

public:
    inline ShadowMap(const glm::vec3& directionalLightDirection)
    {
        float nearPlane = 1.0f;
        float farPlane = 15.f;
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
        glm::mat4 lightView            = glm::lookAt(glm::vec3(0,6,0), glm::vec3(0,-1,0), glm::vec3(0, 1, 0));
        _lightSpaceMatrix = lightProjection*lightView;
        
        glGenFramebuffers(1, &_shadowMapFBO);
        glGenTextures(1, &_shadowMap);
        glBindTexture(GL_TEXTURE_2D, _shadowMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, _clampColor);

        glBindFramebuffer(GL_FRAMEBUFFER, _shadowMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _shadowMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // inline void update(const glm::mat4& lightView, const glm::mat4& projMatrix)
    // {
    //     _lightProjection = projMatrix * lightView;
    // }

    inline void useProgram()
    {
        _program.m_Program.use();
        glUniformMatrix4fv(_program.uLightProjection, 1, GL_FALSE, glm::value_ptr(_lightSpaceMatrix));
        glViewport(0,0,_width,_height);
        glBindFramebuffer(GL_FRAMEBUFFER, _shadowMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    inline void debugDepth(){
        glViewport(0,0,1920,1080);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _debugDepthProgram.m_Program.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _shadowMap);

    }
};