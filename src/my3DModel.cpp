#include "my3DModel.h"

my3DModel::my3DModel(const std::string& modelName, const std::string res)
    : _name(modelName), _res(res)
{
    loadObj(modelName, res);
    for (auto& shape : _shapes)
    {
        shape.initVAOVBO();
    }
}

void my3DModel::draw(const myProgram& program) const
{
    for (int i = 0; i < _shapes.size(); i++)
    {
        const tinyobj::material_t material = _materials[i];
        glUniform3fv(program.uMaterial.uDiffuse, 1, _materials[i].diffuse);
        glUniform3fv(program.uMaterial.uSpecular, 1, _materials[i].specular);
        glUniform1f(program.uMaterial.uShininess, _materials[i].shininess);

        _shapes[i].bindVertexArrayVAO();
        glDrawArrays(GL_TRIANGLES, 0, _shapes[i].shapeVertices().size());
        glBindVertexArray(0);
    }
}

void my3DModel::loadObj(const std::string& modelName, const std::string res)
{
    load3DModel(modelName, res);

    // Load diffuse texture
    auto textureImage = p6::load_image_buffer("./models/" + modelName + "/" + modelName + ".jpg");
    glGenTextures(1, &_diffuseTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), textureImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void my3DModel::load3DModel(const std::string modelName, const std::string res)

{
    // Loading
    tinyobj::attrib_t                attribTemp;
    std::vector<tinyobj::material_t> materialTemp;

    std::vector<tinyobj::shape_t> shapesTemp;

    std::string resString = (res.empty()) ? "" : "_";

    std::string objPath = "models/" + modelName + "/" + modelName + resString + res + ".obj";
    std::cout << objPath << std::endl;
    int a;
    std::cin >> a;
    std::string mtlPath = "models/" + modelName + "/";

    std::string err;
    std::string warn;

    bool ret = tinyobj::LoadObj(&attribTemp, &shapesTemp, &_materials, &err, &warn, objPath.c_str(), mtlPath.c_str());
    std::cout << err << std::endl;
    if (!ret)
    {
        std::cout << "ERREUR CHARGEMENT MODELE" << std::endl;
    }
    // -> ShapeVertex

    // Pour chaque forme dans le fichier .obj
    for (const auto& shape : shapesTemp)
    {
        Vertices3D                       temp;
        std::vector<glimac::ShapeVertex> vertices;

        // Pour chaque face dans la forme
        for (const auto& index : shape.mesh.indices)
        {
            glimac::ShapeVertex vertex;
            const auto          posIndex      = 3 * index.vertex_index;
            const auto          normIndex     = 3 * index.normal_index;
            const auto          texCoordIndex = 2 * index.texcoord_index;

            if (posIndex + 2 < attribTemp.vertices.size())
            {
                vertex.position = {
                    attribTemp.vertices[posIndex + 0],
                    attribTemp.vertices[posIndex + 1],
                    attribTemp.vertices[posIndex + 2]};
            }
            if (normIndex + 2 < attribTemp.normals.size())
            {
                vertex.normal = {
                    attribTemp.normals[normIndex + 0],
                    attribTemp.normals[normIndex + 1],
                    attribTemp.normals[normIndex + 2]};
            }
            if (texCoordIndex + 1 < attribTemp.texcoords.size())
            {
                vertex.texCoords = {
                    attribTemp.texcoords[texCoordIndex + 0],
                    attribTemp.texcoords[texCoordIndex + 1]};
            }
            vertices.push_back(vertex);
        }
        temp.vertices(vertices);
        _shapes.push_back(temp);
    }
}

void my3DModel::loadMtlFile(const char* filePath, std::vector<Material>& materials)
{
    std::FILE* file = std::fopen(filePath, "r");
    if (!file)
    {
        std::fprintf(stderr, "Failed to open file %s\n", filePath);
        std::exit(EXIT_FAILURE);
    }

    Material currentMaterial;

    char line[1024];
    while (std::fgets(line, sizeof(line), file))
    {
        char prefix[256];
        std::sscanf(line, "%255s", prefix);

        if (std::strcmp(prefix, "newmtl") == 0)
        {
            // Start a new material
            if (!currentMaterial.name.empty())
            {
                materials.push_back(currentMaterial);
            }
            currentMaterial = Material();
            std::sscanf(line, "%*s %s", &currentMaterial.name[0]);
        }
        else if (std::strcmp(prefix, "Ns") == 0)
        {
            std::sscanf(line, "%*s %f", &currentMaterial.shininess);
        }
        else if (std::strcmp(prefix, "Ka") == 0)
        {
            std::sscanf(line, "%*s %f %f %f", &currentMaterial.ambientColor.x, &currentMaterial.ambientColor.y, &currentMaterial.ambientColor.z);
        }
        else if (std::strcmp(prefix, "Kd") == 0)
        {
            std::sscanf(line, "%*s %f %f %f", &currentMaterial.diffuseColor.x, &currentMaterial.diffuseColor.y, &currentMaterial.diffuseColor.z);
        }
        else if (std::strcmp(prefix, "Ks") == 0)
        {
            std::sscanf(line, "%*s %f %f %f", &currentMaterial.specularColor.x, &currentMaterial.specularColor.y, &currentMaterial.specularColor.z);
        }
        // Ignore all other prefixes
    }

    // Add the last material
    if (!currentMaterial.name.empty())
    {
        materials.push_back(currentMaterial);
    }

    std::fclose(file);
}

void my3DModel::activateTexture(const myProgram& program)
{
    glUniform1i(program.uTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture);
}