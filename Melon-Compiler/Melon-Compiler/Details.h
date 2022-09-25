/*****************************************************************/
/*!
\file   Details.h

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   22 September 2022
\brief  This file contains the compiler declarations

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/
#pragma once

#include <cstdint>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define MAX_BONE_INFLUENCE 4

typedef struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    glm::vec2 texCoords;

    //bone indexes which will influence this vertex
    int boneIDs[MAX_BONE_INFLUENCE];

    //weights from each bone
    float weights[MAX_BONE_INFLUENCE];
}Vertex;

#if 0
//for future implementation
typedef struct Texture
{
    uint32_t id;
    std::string type;
    std::string path;
}Texture;
#endif


struct MeshHeader
{
    uint32_t m_VerticesCount;
    uint32_t m_IndicesCount;
};


typedef class Mesh
{
public:
    Mesh(std::vector<Vertex> _vertices, std::vector<uint32_t> _indices);

    size_t GetVerticesSize(void) { return m_Vertices.size(); }
    size_t GetIndicesSize(void) { return m_Indices.size(); }

    friend std::ostream& operator<< (std::ostream& _os, const Mesh& _mesh);

public:

    MeshHeader                      m_MeshHeader;   //16 bytes

private:

    std::vector<Vertex>             m_Vertices;     //32 bytes
    std::vector<uint32_t>           m_Indices;      //32 bytes

} Mesh;


//struct to return to the file
struct ModelHeader
{
    uint32_t m_MeshCount;             //no. of meshes in model
};

typedef class Model
{
public:
    Model(void) = default;
    Model(std::string const& _path, bool _gamma = false);

    //bool GetGamma(void) { return m_GammaCorrection; }

    size_t GetMeshesSize(void) { return m_Meshes.size(); }

    Model ExportModel(void);

private:
    void                    LoadModel(std::string const& _path);
    void                    ProcessNode(aiNode* _node, const aiScene* _scene);
    Mesh                    ProcessMesh(aiMesh* _mesh, const aiScene* _scene);

    ModelHeader             m_ModelHeader;
    std::vector<Mesh>       m_Meshes;           //32 bytes
    //bool                    m_GammaCorrection;

} Model;