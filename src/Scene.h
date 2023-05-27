#pragma once

#include "Arpenteur.h"
#include "CubeMap.h"
#include "DirectionalLight.h"
#include "Fish.h"
#include "FishGang.h"
#include "FishType.h"
#include "FoodKind.h"
#include "Obstacle.h"
#include "PointLight.h"
#include "TrackballCamera.h"
#include "Vertices3D.h"
#include "my3DModel.h"
#include "myProgram.h"

class Scene {
private:
    // Objects
    std::vector<FishGang> _fishGangs{};
    std::vector<FoodKind> _allFoods{};
    Arpenteur             _arpenteur;
    TrackballCamera       _camera{};
    std::vector<Obstacle> _obstacles;
    PointLight            _pointLight;
    DirectionalLight      _directionalLight;
    CubeMap               _cubemap;
    myProgram             _program{};

    // BoundingBox
    my3DModel _boundingBox;
    Matrices  _boundingBoxMatrices;
    float     _boundingBoxOpacity = 0;

    glm::vec3 _maxDistanceFromCenter{};
    glm::mat4 _projMatrix;

public:
    // Constructor
    Scene(const p6::Context& ctx);
    void createFishGangAndFoods(FishType type, int nbFishes, float radius);

    // Update
    void update(p6::Context& ctx);
    void updateFishGangsAndFoods(const glm::mat4& viewMatrix);
    void updateObstacles(const glm::mat4& viewMatrix);
    void updateCamera(p6::Context& ctx);
    void updateLights(const float time, const glm::mat4& viewMatrix);

    // Draw
    void        draw(p6::Context& ctx);
    void        drawFishGangsAndFoods(p6::Context& ctx);
    void        drawObstacles();
    void        drawBoundingBox();
    inline void sendOpacityToShader(float opacity);

    // Pointeur
    std::vector<FishGang>* fishGangsPtr();
    glm::vec3*             maxDistanceFromCenterPtr();
    float*                 boundingBoxOpacityPtr();

    // Position
    glm::vec3 randomPosInBoundingBox();
    glm::vec3 maxDistanceFromCenter();

    // GUI
    void        GUIdisplay();
    inline void GUIdisplaySceneParameter();
};