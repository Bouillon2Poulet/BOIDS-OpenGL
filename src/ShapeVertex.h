#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include "glm/fwd.hpp"

namespace glimac {

struct ShapeVertex {
    glm::vec3 position{};
    glm::vec3 normal{};
    glm::vec2 texCoords{};

    ShapeVertex() = default;
    ShapeVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords)
        : position(position), normal(normal), texCoords(texCoords) {}
};

inline std::vector<ShapeVertex> sphere_vertices(float radius, size_t discLat, size_t discLong) // NOLINT(bugprone-easily-swappable-parameters, readability-inconsistent-declaration-parameter-name)
{
    // Équation paramétrique en (r, phi, theta) de la sphère
    // avec r >= 0, -PI / 2 <= theta <= PI / 2, 0 <= phi <= 2PI
    //
    // x(r, phi, theta) = r * sin(phi) * cos(theta)
    // y(r, phi, theta) = r * sin(theta) *
    // z(r, phi, theta) = r * cos(phi) * cos(theta)
    //
    // Discrétisation:
    // phi = 2PI / discLat, theta = PI / discLong
    //
    // x(r, i, j) = r * sin(i * phi) * cos(-PI / 2 + j * theta)
    // y(r, i, j) = r * sin(-PI / 2 + j * theta)
    // z(r, i, j) = r * cos(i * phi) * cos(-PI / 2 + j * theta)
    //
    // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
    // par un Index Buffer Object, que nous verrons dans les prochains TDs

    const auto fDiscLat  = static_cast<float>(discLat);
    const auto fDiscLong = static_cast<float>(discLong);

    const float phi   = 2.f * glm::pi<float>() / fDiscLat;
    const float theta = glm::pi<float>() / fDiscLong;

    std::vector<ShapeVertex> data;

    // Construit l'ensemble des vertex
    for (size_t j = 0; j <= discLong; ++j)
    {
        const auto fj = static_cast<float>(j);

        const float cosTheta = std::cos(-glm::pi<float>() / 2.f + fj * theta);
        const float sinTheta = std::sin(-glm::pi<float>() / 2.f + fj * theta);

        for (size_t i = 0; i <= discLat; ++i)
        {
            const auto  fi = static_cast<float>(i);
            ShapeVertex vertex{};

            vertex.texCoords.x = fi / fDiscLat;
            vertex.texCoords.y = 1.f - fj / fDiscLong;

            vertex.normal.x = std::sin(fi * phi) * cosTheta;
            vertex.normal.y = sinTheta;
            vertex.normal.z = std::cos(fi * phi) * cosTheta;

            vertex.position = radius * vertex.normal;

            data.push_back(vertex);
        }
    }
    return data;
}

inline std::vector<ShapeVertex> cone_vertices(float height, float radius, size_t discLat, size_t discHeight) // NOLINT(bugprone-easily-swappable-parameters, readability-inconsistent-declaration-parameter-name)
{
    // Equation paramétrique en (r, phi, h) du cône
    // avec r >= 0, -PI / 2 <= theta <= PI / 2, 0 <= h <= height
    //
    // x(r, phi, h) = r (height - h) sin(phi) / height
    // y(r, phi, h) = h
    // z(r, phi, h) = r (height - h) cos(phi) / height
    //
    // Discrétisation:
    // phi = 2PI / discLat, h = height / discHeight
    //
    // x(r, i, j) = r * (height - j * h) * sin(i * phi) / height
    // y(r, i, j) = j * h
    // z(r, i, j) = r * (height - j * h) * cos(i * phi) / height
    //
    // Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
    // par un Index Buffer Object, que nous verrons dans les prochains TDs

    const auto fDiscLat    = static_cast<float>(discLat);
    const auto fDiscHeight = static_cast<float>(discHeight);

    const float phi = 2.f * glm::pi<float>() / fDiscLat;
    const float h   = height / fDiscHeight;

    std::vector<ShapeVertex> data;

    // Construit l'ensemble des vertex
    for (size_t j = 0; j <= discHeight; ++j)
    {
        for (size_t i = 0; i < discLat; ++i)
        {
            const auto fj = static_cast<float>(j);
            const auto fi = static_cast<float>(i);

            ShapeVertex vertex{};

            vertex.texCoords.x = fi / fDiscLat;
            vertex.texCoords.y = fj / fDiscHeight;

            vertex.position.x = radius * (height - fj * h) * std::sin(fi * phi) / height;
            vertex.position.y = fj * h;
            vertex.position.z = radius * (height - fj * h) * std::cos(fi * phi) / height;

            vertex.normal.x = std::sin(fi * phi);
            vertex.normal.y = radius / height;
            vertex.normal.z = std::cos(fi * phi);
            vertex.normal   = glm::normalize(vertex.normal);

            data.push_back(vertex);
        }
    }

    std::vector<ShapeVertex> vertices{};
    // Construit les vertex finaux en regroupant les données en triangles :
    // Pour une longitude donnée, les deux triangles formant une face sont de la forme :
    // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
    // avec i sur la bande correspondant à la longitude
    for (size_t j = 0; j < discHeight; ++j)
    {
        const size_t offset = j * discLat;
        for (size_t i = 0; i < discLat; ++i)
        {
            vertices.push_back(data[offset + i]);
            vertices.push_back(data[offset + (i + 1) % discLat]);
            vertices.push_back(data[offset + discLat + (i + 1) % discLat]);
            vertices.push_back(data[offset + i]);
            vertices.push_back(data[offset + discLat + (i + 1) % discLat]);
            vertices.push_back(data[offset + i + discLat]);
        }
    }

    return vertices;
}

inline std::vector<ShapeVertex> cube_vertices(float sideLength)
{
    const float halfSide = sideLength / 2.f;

    std::vector<ShapeVertex> data;

    // face -X
    data.push_back({{-halfSide, -halfSide, -halfSide}, {-1.f, 0.f, 0.f}, {0.f, 0.f}});
    data.push_back({{-halfSide, -halfSide, halfSide}, {-1.f, 0.f, 0.f}, {1.f, 0.f}});
    data.push_back({{-halfSide, halfSide, halfSide}, {-1.f, 0.f, 0.f}, {1.f, 1.f}});

    data.push_back({{-halfSide, -halfSide, -halfSide}, {-1.f, 0.f, 0.f}, {0.f, 0.f}});
    data.push_back({{-halfSide, halfSide, halfSide}, {-1.f, 0.f, 0.f}, {1.f, 1.f}});
    data.push_back({{-halfSide, halfSide, -halfSide}, {-1.f, 0.f, 0.f}, {0.f, 1.f}});

    // face +X
    data.push_back({{halfSide, -halfSide, -halfSide}, {1.f, 0.f, 0.f}, {0.f, 0.f}});
    data.push_back({{halfSide, halfSide, halfSide}, {1.f, 0.f, 0.f}, {1.f, 1.f}});
    data.push_back({{halfSide, -halfSide, halfSide}, {1.f, 0.f, 0.f}, {1.f, 0.f}});

    data.push_back({{halfSide, -halfSide, -halfSide}, {1.f, 0.f, 0.f}, {0.f, 0.f}});
    data.push_back({{halfSide, halfSide, -halfSide}, {1.f, 0.f, 0.f}, {0.f, 1.f}});
    data.push_back({{halfSide, halfSide, halfSide}, {1.f, 0.f, 0.f}, {1.f, 1.f}});

    // face -Y
    data.push_back({{-halfSide, -halfSide, -halfSide}, {0.f, -1.f, 0.f}, {0.f, 0.f}});
    data.push_back({{halfSide, -halfSide, halfSide}, {0.f, -1.f, 0.f}, {1.f, 1.f}});
    data.push_back({{-halfSide, -halfSide, halfSide}, {0.f, -1.f, 0.f}, {1.f, 0.f}});

    data.push_back({{-halfSide, -halfSide, -halfSide}, {0.f, -1.f, 0.f}, {0.f, 0.f}});
    data.push_back({{halfSide, -halfSide, -halfSide}, {0.f, -1.f, 0.f}, {0.f, 1.f}});
    data.push_back({{halfSide, -halfSide, halfSide}, {0.f, -1.f, 0.f}, {1.f, 1.f}});

    // face +Y
    data.push_back({{-halfSide, halfSide, -halfSide}, {0.f, 1.f, 0.f}, {0.f, 0.f}});
    data.push_back({{-halfSide, halfSide, halfSide}, {0.f, 1.f, 0.f}, {1.f, 0.f}});
    data.push_back({{halfSide, halfSide, halfSide}, {0.f, 1.f, 0.f}, {1.f, 1.f}});

    data.push_back({{-halfSide, halfSide, -halfSide}, {0.f, 1.f, 0.f}, {0.f, 0.f}});
    data.push_back({{halfSide, halfSide, halfSide}, {0.f, 1.f, 0.f}, {1.f, 1.f}});
    data.push_back({{halfSide, halfSide, -halfSide}, {0.f, 1.f, 0.f}, {0.f, 1.f}});

    // face -Z
    data.push_back({{-halfSide, -halfSide, -halfSide}, {0.f, 0.f, -1.f}, {0.f, 0.f}});
    data.push_back({{-halfSide, halfSide, -halfSide}, {0.f, 0.f, -1.f}, {1.f, 0.f}});
    data.push_back({{halfSide, halfSide, -halfSide}, {0.f, 0.f, -1.f}, {1.f, 1.f}});

    data.push_back({{-halfSide, -halfSide, -halfSide}, {0.f, 0.f, -1.f}, {0.f, 0.f}});
    data.push_back({{halfSide, halfSide, -halfSide}, {0.f, 0.f, -1.f}, {1.f, 1.f}});
    data.push_back({{halfSide, -halfSide, -halfSide}, {0.f, 0.f, -1.f}, {0.f, 1.f}});

    // face +Z
    data.push_back({{-halfSide, -halfSide, halfSide}, {0.f, 0.f, 1.f}, {0.f, 0.f}});
    data.push_back({{halfSide, -halfSide, halfSide}, {0.f, 0.f, 1.f}, {1.f, 0.f}});
    data.push_back({{halfSide, halfSide, halfSide}, {0.f, 0.f, 1.f}, {1.f, 1.f}});

    data.push_back({{-halfSide, -halfSide, halfSide}, {0.f, 0.f, 1.f}, {0.f, 0.f}});
    data.push_back({{halfSide, halfSide, halfSide}, {0.f, 0.f, 1.f}, {1.f, 1.f}});
    data.push_back({{-halfSide, halfSide, halfSide}, {0.f, 0.f, 1.f}, {0.f, 1.f}});

    return data;
}
}; // namespace glimac