#pragma once

#include "Matrices.h"
#include "MovementVariables.h"
#include "Vertices3D.h"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "my3DModel.h"
#include "myProgram.h"

class Arpenteur {
private:
    MovementVariables _mvtVariables;
    Vertices3D        _vertices3D;
    float             _width = 1.f;

    p6::Color _color  = {1.f, .5f, .5f};
    float     _radius = .05f;

    my3DModel _submarine;
    Matrices  _submarineMatrices{};
    my3DModel _turbine;
    Matrices  _turbineMatrices{};
    float     _turbineAngleAsDegree = 0.f;

public:
    Arpenteur();
    void update(const p6::Context& ctx, const glm::mat4& viewMatrix, const glm::vec3& cameraDirection, const glm::vec3& maxDistanceFromCenter);
    void checkInput(const p6::Context& ctx, const glm::vec3& cameraDirection, const glm::vec3& maxDistanceFromCenter);
    void draw(const myProgram& program, const glm::mat4& projMatrix);

    glm::vec3 position();
};