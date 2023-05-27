#include "ShapeVertex.h"

std::vector<glimac::ShapeVertex> glimac::sphere_vertices(float radius, size_t discLat, size_t discLong) // NOLINT(bugprone-easily-swappable-parameters, readability-inconsistent-declaration-parameter-name)
{
    const auto fDiscLat  = static_cast<float>(discLat);
    const auto fDiscLong = static_cast<float>(discLong);

    const float phi   = 2.f * glm::pi<float>() / fDiscLat;
    const float theta = glm::pi<float>() / fDiscLong;

    std::vector<glimac::ShapeVertex> data;

    // Construit l'ensemble des vertex
    for (size_t j = 0; j <= discLong; ++j)
    {
        const auto fj = static_cast<float>(j);

        const float cosTheta = std::cos(-glm::pi<float>() / 2.f + fj * theta);
        const float sinTheta = std::sin(-glm::pi<float>() / 2.f + fj * theta);

        for (size_t i = 0; i <= discLat; ++i)
        {
            const auto          fi = static_cast<float>(i);
            glimac::ShapeVertex vertex{};

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

std::vector<glimac::ShapeVertex> glimac::cone_vertices(float height, float radius, size_t discLat, size_t discHeight) // NOLINT(bugprone-easily-swappable-parameters, readability-inconsistent-declaration-parameter-name)
{
    const auto fDiscLat    = static_cast<float>(discLat);
    const auto fDiscHeight = static_cast<float>(discHeight);

    const float phi = 2.f * glm::pi<float>() / fDiscLat;
    const float h   = height / fDiscHeight;

    std::vector<glimac::ShapeVertex> data;

    // Construit l'ensemble des vertex
    for (size_t j = 0; j <= discHeight; ++j)
    {
        for (size_t i = 0; i < discLat; ++i)
        {
            const auto fj = static_cast<float>(j);
            const auto fi = static_cast<float>(i);

            glimac::ShapeVertex vertex{};

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

    std::vector<glimac::ShapeVertex> vertices{};
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

std::vector<glimac::ShapeVertex> glimac::cube_vertices(float sideLength)
{
    const float halfSide = sideLength / 2.f;

    std::vector<glimac::ShapeVertex> data;

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

std::vector<glimac::ShapeVertex> glimac::load3DModel(const std::string modelName)
{
    // Loading
    tinyobj::attrib_t                attrib;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;

    std::string objPath = "models/" + modelName + "/" + modelName + ".obj";

    std::string err;
    std::string warn;
    bool        ret;

    ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, &warn, objPath.c_str());

    if (!ret)
    {
        std::cout << "ERREUR CHARGEMENT MODELE" << std::endl;
    }
    // -> ShapeVertex

    std::vector<glimac::ShapeVertex> vertices;

    // Pour chaque forme dans le fichier .obj
    for (const auto& shape : shapes)
    {
        // Pour chaque face dans la forme
        for (const auto& index : shape.mesh.indices)
        {
            glimac::ShapeVertex vertex;
            const auto          posIndex      = 3 * index.vertex_index;
            const auto          normIndex     = 3 * index.normal_index;
            const auto          texCoordIndex = 2 * index.texcoord_index;

            if (posIndex + 2 < attrib.vertices.size())
            {
                vertex.position = {
                    attrib.vertices[posIndex + 0],
                    attrib.vertices[posIndex + 1],
                    attrib.vertices[posIndex + 2]};
            }
            if (normIndex + 2 < attrib.normals.size())
            {
                vertex.normal = {
                    attrib.normals[normIndex + 0],
                    attrib.normals[normIndex + 1],
                    attrib.normals[normIndex + 2]};
            }
            if (texCoordIndex + 1 < attrib.texcoords.size())
            {
                vertex.texCoords = {
                    attrib.texcoords[texCoordIndex + 0],
                    attrib.texcoords[texCoordIndex + 1]};
            }
            vertices.push_back(vertex);
        }
    }
    return vertices;
}