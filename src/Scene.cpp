#include "Scene.h"
#include <string.h>
#include <vector>
#include "Arpenteur.h"
#include "Fish.h"
#include "FishGang.h"
#include "Obstacle.h"
#include "Vertices3D.h"
#include "my3DModel.h"

void Scene::draw(p6::Context& ctx)
{
    // ctx.background(_backgroundColor);

    _program.m_Program.use();

    sendOpacityToShader(1.);
    for (auto& food : _allFoods)
    {
        food.draw(_program, _projMatrix, _camera.getViewMatrix());
    }

    for (auto& fish : _fishGangs)
    {
        std::cout << fish.name() << std::endl;
        fish.draw(ctx, _program, _projMatrix);
    }

    // _arpenteur.draw(_program, _projMatrix);

    for (auto& obstacle : _obstacles)
    {
        obstacle.draw(_program, _projMatrix);
    }

    sendOpacityToShader(0.3);
    displayBoundingBoxIfNecessary();
}

void Scene::displayBoundingBoxIfNecessary()
{
    if (displayBoundingBox())
    {
        drawBoundingBox();
    }
}
void Scene::update(p6::Context& ctx)
{
    // _pointLight.update(ctx.time(), _camera.getViewMatrix(), _program);
    // _directionalLight.update(ctx.time(), _camera.getViewMatrix(), _program);
    // _camera.updateArpenteurPosition(_arpenteur.position());

    // for (unsigned int i = 0; i < _fishGangs.size(); i++)
    // {
    //     _fishGangs[i].update(_maxDistanceFromCenter, _allFoods[i], _camera.getViewMatrix());
    //     _allFoods[i].update(_maxDistanceFromCenter);
    // }
    // _arpenteur.update(ctx, _camera.getViewMatrix(), _maxDistanceFromCenter);
    // _camera.handleDeplacement(ctx);
    // _boundingBoxMatrices.updateBB(_camera.getViewMatrix(), _maxDistanceFromCenter);
}

void Scene::drawDepth()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);

    _shadowMapFBO.BindForWriting();
    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_BACK);
    _shaderSh.use();

    glm::vec3 sun = {0.25, 0.5, 0.25};

    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view  = glm::lookAt(sun, glm::vec3(0), {0, 1, 0});
    // glm::mat4 view = glm::lookAt(posCam, glm::vec3(0), {0 , 1, 0});

    glm::mat4 projection = glm::ortho<float>(-0.25, 0.25, -0.25, 0.25, 0, 1);

    _shaderSh.set("projection", projection);
    _shaderSh.set("model", model);
    _shaderSh.set("view", view);

    for (auto& obstacle : _obstacles)
    {
        obstacle.update(_camera.getViewMatrix());
        obstacle.draw();
    }

    glm::mat4 DepthMVP = (projection * view * model);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 1280, 720);

    _shader.use();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);

    glUniform1i(glGetUniformLocation(_shader.id(), "gShadowMap"), 0);
    _shadowMapFBO.BindForReading(GL_TEXTURE0);

    model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view  = glm::lookAt(glm::vec3(1, 0, 0), glm::vec3(0), {0, 1, 0});

    _shader.set("model", model);
    _shader.set("view", view);

    _shader.set("DepthMVP", DepthMVP);

    for (auto& obstacle : _obstacles)
    {
        obstacle.draw();
    }
}

Scene::Scene(const p6::Context& ctx)
    : _maxDistanceFromCenter(glm::vec3(10)), _arpenteur(_maxDistanceFromCenter), _projMatrix(glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 100.f)), _boundingBox(ShapeType::cube), _shader(p6::load_shader("shaders/loic/shadow_render.vs.glsl", "shaders/loic/shadow_render.fs.glsl")), _shaderSh(p6::load_shader("shaders/loic/shadow_map.vs.glsl", "shaders/loic/shadow_map.fs.glsl")), _cam(p6::load_shader("shaders/loic/camera.vs.glsl", "shaders/loic/camera.fs.glsl"))
{
    _shadowMapFBO.Init(1280, 720);
    _shader.set("projection", _projMatrix);
    _shaderSh.set("projection", _projMatrix);
    _cam.set("projection", _projMatrix);

    // Init FishGang and Foods n°1

    std::cout << "CONSTRUCTEUR SCENE\n";
    // createFishGangAndFoods(FishType::tuna, 3);
    createFishGangAndFoods(FishType::koi, 50, 1.f);
    // createFishGangAndFoods(FishType::shark, 3);

    _obstacles.push_back(Obstacle("coral", {0, -4.2, 0.9}, .7));
    _obstacles.push_back(Obstacle("ground", {0., -8., -0.}, 0.31f));
    // Init allFoods
}

void Scene::drawBoundingBox()
{
    _boundingBoxMatrices.sendMatricesToShader(_program, _projMatrix);
    _boundingBox.bindVertexArrayVAO();
    glDrawArrays(GL_TRIANGLES, 0, _boundingBox.size());
    glBindVertexArray(0);
}

bool Scene::displayBoundingBox()
{
    return _displayBoundingBox;
};

std::vector<FishGang>* Scene::fishGangsPtr()
{
    return &_fishGangs;
}

bool* Scene::displayBoundingBoxPtr()
{
    return &_displayBoundingBox;
}

glm::vec3* Scene::maxDistanceFromCenterPtr()
{
    return &_maxDistanceFromCenter;
}

glm::vec3 Scene::randomPosInBoundingBox()
{
    return {p6::random::number(-_maxDistanceFromCenter.x, _maxDistanceFromCenter.x), p6::random::number(-_maxDistanceFromCenter.y, _maxDistanceFromCenter.y), p6::random::number(-_maxDistanceFromCenter.z, _maxDistanceFromCenter.z)};
}

void Scene::createFishGangAndFoods(FishType type, int nbFishes, float radius)
{
    _fishGangs.emplace_back(type, nbFishes, _maxDistanceFromCenter, radius);
    _allFoods.emplace_back(type, _maxDistanceFromCenter);
}
