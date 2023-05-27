#include "CubeMap.h"

CubeMap::CubeMap()
    : _model("cubeMap", "")
{
    _animTextures.resize(240);
    loadAnimTextures();
}

void CubeMap::loadAnimTextures()
{
    for (int i = 0; i < 240; i++)
    {
        // Convert i to correct string
        std::string index = std::to_string(i);
        if (i < 100)
        {
            index.insert(0, "0");
            if (i < 10)
            {
                index.insert(0, "0");
            }
        }

        // Load diffuse texture
        auto textureImage = p6::load_image_buffer("./models/cubeMap/anim/cubeMap" + index + ".jpg");

        glGenTextures(1, &_animTextures[i]);
        glBindTexture(GL_TEXTURE_2D, _animTextures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void CubeMap::activateRightAnimTexture(const myProgram& program, float time)
{
    glUniform1i(program.uTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    int index = static_cast<int>(time * 50) % 240;
    glBindTexture(GL_TEXTURE_2D, _animTextures[index]);
}

void CubeMap::draw(const myProgram& program, const glm::mat4& projMatrix, const glm::mat4& viewMatrix, float time)
{
    _matrices.updateObstacle(viewMatrix, {}, 50);
    activateRightAnimTexture(program, time);
    _matrices.sendMatricesToShader(program, projMatrix);
    _model.draw(program);
}