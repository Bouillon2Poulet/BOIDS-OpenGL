#pragma once

#include <assimp/Importer.hpp>
#include <vector>
#include "Mesh.h"
// #include "ShapeVertex.h"
#include "Vertices3D.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "p6/p6.h"

class Mesh {
public:
    Mesh() = default;

    ~Mesh() = default;

    inline bool LoadMesh(const std::string& Filename)
    {
        // // Release the previously loaded mesh (if it exists)
        // Clear();

        bool             Ret = false;
        Assimp::Importer Importer;

        const aiScene* pScene = Importer.ReadFile(("./../models/" + Filename).c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
        std::cout << aiGetErrorString() << std::endl;
        int a;
        std::cin >> a;
        if (pScene)
        {
            Ret = InitFromScene(pScene, Filename);
        }
        else
        {
            printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
        }

        return Ret;
    }

    inline bool InitFromScene(const aiScene* pScene, const std::string& Filename)
    {
        m_Entries.resize(pScene->mNumMeshes);
        m_Textures.resize(pScene->mNumMaterials);

        // Initialize the meshes in the scene one by one
        for (unsigned int i = 0; i < m_Entries.size(); i++)
        {
            const aiMesh* paiMesh = pScene->mMeshes[i];
            InitMesh(i, paiMesh);
        }

        // return InitMaterials(pScene, Filename);
        return 1;
    }

    void InitMesh(unsigned int Index, const aiMesh* paiMesh)
    {
        m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

        std::vector<glimac::ShapeVertex> vertices;
        std::vector<GLint>               indices;

        const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

        for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
        {
            const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
            const aiVector3D* pNormal   = paiMesh->HasNormals() ? &(paiMesh->mNormals[i]) : &Zero3D;
            const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

            vertices.push_back(glimac::ShapeVertex(glm::vec3(pPos->x, pPos->y, pPos->z), glm::vec3(pNormal->x, pNormal->y, pNormal->z), glm::vec2(pTexCoord->x, pTexCoord->y)));
        }
        for (unsigned int i = 0; i < paiMesh->mNumFaces; i++)
        {
            const aiFace& Face = paiMesh->mFaces[i];
            assert(Face.mNumIndices == 3);
            indices.push_back(Face.mIndices[0]);
            indices.push_back(Face.mIndices[1]);
            indices.push_back(Face.mIndices[2]);
        }

        std::vector<GLint> verticesAsGLint;

        for (const auto& it : vertices)
        {
            verticesAsGLint.push_back(it.position.x);
            verticesAsGLint.push_back(it.position.y);
            verticesAsGLint.push_back(it.position.z);

            verticesAsGLint.push_back(it.normal.x);
            verticesAsGLint.push_back(it.normal.y);
            verticesAsGLint.push_back(it.normal.z);

            verticesAsGLint.push_back(it.texCoords.x);
            verticesAsGLint.push_back(it.texCoords.y);
        }
        m_Entries[Index].Init(verticesAsGLint, indices);
    }

    void Render()
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        for (unsigned int i = 0; i < m_Entries.size(); i++)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), 0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (GLvoid*)offsetof(glimac::ShapeVertex, normal));
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (GLvoid*)offsetof(glimac::ShapeVertex, texCoords));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

            // const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

            // if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex])
            // {
            //     m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
            // }

            glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }

    // bool InitMaterials(const aiScene* pScene, const std::string& Filename)
    // {
    //     for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
    //     {
    //         const aiMaterial* pMaterial = pScene->mMaterials[i];

    //         // m_Textures[i] = NULL;
    //         if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    //         {
    //             aiString Path;

    //             if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
    //             {
    //                 // std::string FullPath = Dir + "/" + Path.data;
    //                 m_Textures[i] = new p6::Texture(GL_TEXTURE_2D, FullPath.c_str());

    //                 if (!m_Textures[i]->Load())
    //                 {
    //                     printf("Error loading texture '%s'\n", FullPath.c_str());
    //                     delete m_Textures[i];
    //                     m_Textures[i] = NULL;
    //                     Ret           = false;
    //                 }
    //             }
    //         }
    //         if (!m_Textures[i])
    //         {
    //             m_Textures[i] = new Texture(GL_TEXTURE_2D, "../Content/white.png");
    //             Ret           = m_Textures[i]->Load();
    //         }
    //     }
    //     return Ret;
    // }
    // void Clear();

private:
#define INVALID_MATERIAL 0xFFFFFFFF

    struct MeshEntry {
        MeshEntry() = default;

        ~MeshEntry() = default;

        bool Init(const std::vector<GLint>& Vertices, const std::vector<GLint> Indices)
        {
            glGenBuffers(1, &VB);
            glBindBuffer(GL_ARRAY_BUFFER, VB);
            glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(GLint), Vertices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            const GLuint SHADER_VERTEX_POS      = 0;
            const GLuint SHADER_VERTEX_NORM     = 1;
            const GLuint SHADER_VERTEX_TEXCOORD = 2;

            glGenVertexArrays(1, &IB);
            glBindVertexArray(IB);
            glEnableVertexAttribArray(SHADER_VERTEX_POS);
            glEnableVertexAttribArray(SHADER_VERTEX_NORM);
            glEnableVertexAttribArray(SHADER_VERTEX_TEXCOORD);
            glBindBuffer(GL_ARRAY_BUFFER, VB);
            glVertexAttribPointer(SHADER_VERTEX_POS, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), nullptr);
            glVertexAttribPointer(SHADER_VERTEX_NORM, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (GLvoid*)offsetof(glimac::ShapeVertex, normal));
            glVertexAttribPointer(SHADER_VERTEX_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (GLvoid*)offsetof(glimac::ShapeVertex, texCoords));
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            return 1;
        };

        GLuint       VB{};
        GLuint       IB{};
        unsigned int NumIndices{};
        unsigned int MaterialIndex{};
    };

    std::vector<MeshEntry>   m_Entries;
    std::vector<p6::Texture> m_Textures;
    std::vector<Vertices3D>  m_vertices;
};
