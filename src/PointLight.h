#pragma once
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "myProgram.h"
#include "p6/p6.h"

class PointLight {
private:
    glm::vec3 _lightIntensity = {0.f, 1.f, 0.f};

public:
    void update(float time, const glm::mat4& viewMatrix, const myProgram& program);
};