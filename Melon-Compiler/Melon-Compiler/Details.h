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
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;

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
    uint32_t m_VerticesCount = 0;
    uint32_t m_IndicesCount = 0;
};


typedef class Mesh
{
public:
    Mesh(void) = default;
    Mesh(std::vector<Vertex> _vertices, std::vector<uint32_t> _indices);

    size_t GetVerticesSize(void) const { return m_Vertices.size(); }
    size_t GetIndicesSize(void) const { return m_Indices.size(); }

    std::vector<Vertex> GetVertices(void) const { return m_Vertices; }
    std::vector<uint32_t> GetIndices(void) const { return m_Indices; }

    friend std::ostream& operator<< (std::ostream& _os, const Mesh& _mesh);

public:
    void PushbackVertices(Vertex _v) { m_Vertices.push_back(_v); }
    void PushbackIndices(uint32_t _i) { m_Indices.push_back(_i); }

public:

    MeshHeader                      m_MeshHeader;   //16 bytes

private:

    std::vector<Vertex>             m_Vertices;     //32 bytes
    std::vector<uint32_t>           m_Indices;      //32 bytes

} Mesh;


//struct to return to the file
struct ModelHeader
{
    uint32_t m_MeshCount = 0;             //no. of meshes in model
};

typedef class Model
{
public:
    Model(void) = default;
    Model(std::string const& _path);

    //bool GetGamma(void) { return m_GammaCorrection; }

    size_t GetMeshesSize(void) { return m_Meshes.size(); }

    const Model& ExportModel(void) const;

    std::vector<Mesh> GetMeshes(void) const { return m_Meshes; }

    ModelHeader             m_ModelHeader;

public:
    void PushbackMesh(Mesh _tmp) { m_Meshes.push_back(_tmp); }

private:
    void                    LoadModel(std::string const& _path);
    void                    ProcessNode(aiNode* _node, const aiScene* _scene);
    Mesh                    ProcessMesh(aiMesh* _mesh, const aiScene* _scene);

    std::vector<Mesh>       m_Meshes;           //32 bytes

} Model;
