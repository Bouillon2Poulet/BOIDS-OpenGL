#pragma once
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "myProgram.h"
#include "p6/p6.h"

class DirectionalLight {
private:
    glm::vec3 _lightIntensity = {0, 0, 1};
    glm::vec3 _direction      = {1.f, 1.f, 0.f};

public:
    void update(const myProgram& program);
};