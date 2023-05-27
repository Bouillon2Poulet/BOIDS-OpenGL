#include "Arpenteur.h"

Arpenteur::Arpenteur()
    : _mvtVariables(), _vertices3D(ShapeType::cube), _submarine("submarine", ""), _turbine("turbine", "")
{
}

void Arpenteur::update(const p6::Context& ctx, const glm::mat4& viewMatrix, const glm::vec3& cameraDirection, const glm::vec3& maxDistanceFromCenter)
{
    checkInput(ctx, cameraDirection, maxDistanceFromCenter);
    _submarineMatrices.updateFishOrArpenteur(_mvtVariables._position, _radius, cameraDirection, viewMatrix);
    _turbineMatrices.updateTurbine(_mvtVariables._position, _radius, cameraDirection, viewMatrix, _turbineAngleAsDegree);
}

void Arpenteur::checkInput(const p6::Context& ctx, const glm::vec3& cameraDirection, const glm::vec3& maxDistanceFromCenter)
{
    if (ctx.key_is_pressed(GLFW_KEY_S)) // BACK
    {
        _mvtVariables._position -= glm::normalize(cameraDirection) * 0.1f;
        if (std::abs(_mvtVariables._position.z) >= (maxDistanceFromCenter.z / 2.f) - 0.1f || std::abs(_mvtVariables._position.x) >= (maxDistanceFromCenter.x / 2.f) - 0.1f)
        {
            _mvtVariables._position += glm::normalize(cameraDirection) * 0.1f;
        }
        _turbineAngleAsDegree += 5;
    }

    if (ctx.key_is_pressed(GLFW_KEY_W)) // FRONT
    {
        _mvtVariables._position += glm::normalize(cameraDirection) * 0.1f;
        if (std::abs(_mvtVariables._position.z) >= (maxDistanceFromCenter.z / 2.f) - 0.1f || std::abs(_mvtVariables._position.x) >= (maxDistanceFromCenter.x / 2.f) - 0.1f)
        {
            _mvtVariables._position -= glm::normalize(cameraDirection) * 0.1f;
        }
        _turbineAngleAsDegree += 5;
    }

    if (ctx.key_is_pressed(GLFW_KEY_SPACE))
    {
        _mvtVariables._position.y += 0.1;
        _turbineAngleAsDegree += 5;
    }

    if (ctx.key_is_pressed(GLFW_KEY_Q))
    {
        _mvtVariables._position.y -= 0.1;
        _turbineAngleAsDegree -= 5;
    }
}
void Arpenteur::draw(const myProgram& program, const glm::mat4& projMatrix)
{
    _submarine.activateTexture(program);
    _submarineMatrices.sendMatricesToShader(program, projMatrix);
    _submarine.draw(program);
    _turbine.activateTexture(program);
    _turbineMatrices.sendMatricesToShader(program, projMatrix);
    _turbine.draw(program);
}

glm::vec3 Arpenteur::position()
{
    return _mvtVariables._position;
}