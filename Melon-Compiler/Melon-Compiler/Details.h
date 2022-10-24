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

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>

#include "Melon_Mesh.h"
#include "Melon_Skeleton.h"

//struct to return to the file
struct ModelHeader
{
    uint32_t m_MeshCount = 0;             //no. of meshes in model
    int m_BoneCount = 0;
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

    auto& GetBoneInfoMap(void) { return m_BoneInfoMap; }
    int& GetBoneCount(void) { return m_BoneCounter; }

private:
    void SetVertexBoneDataDefault(Vertex& _v);
    void SetVertexBoneData(Vertex& _v, int _boneID, float _weight);
    void ExtractBoneWeightForVertices(std::vector<Vertex>& _vertices, aiMesh* _mesh);

private:
    void                    LoadModel(std::string const& _path);
    void                    ProcessNode(aiNode* _node, const aiScene* _scene);
    Mesh                    ProcessMesh(aiMesh* _mesh, const aiScene* _scene);

    std::vector<Mesh>       m_Meshes;           //32 bytes

    std::map<std::string, BoneInfo> m_BoneInfoMap;
    int m_BoneCounter = 0;

} Model;
