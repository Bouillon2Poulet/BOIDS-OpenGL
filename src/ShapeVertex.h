#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <string>
#include <vector>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "tiny_obj_loader.h"

namespace glimac {

struct ShapeVertex {
    glm::vec3 position{};
    glm::vec3 normal{};
    glm::vec2 texCoords{};

    ShapeVertex() = default;
    ShapeVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords)
        : position(position), normal(normal), texCoords(texCoords) {}
};

std::vector<ShapeVertex> sphere_vertices(float radius, size_t discLat, size_t discLong);
std::vector<ShapeVertex> cone_vertices(float height, float radius, size_t discLat, size_t discHeight);
std::vector<ShapeVertex> cube_vertices(float sideLength);
std::vector<ShapeVertex> load3DModel(const std::string modelName);
}; // namespace glimac