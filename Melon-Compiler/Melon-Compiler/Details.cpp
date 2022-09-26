/*****************************************************************/
/*!
\file   Compiler.cpp

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   22 September 2022
\brief  This file contains definitions for compiler

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/

#include "Details.h"
#include "Asserts.h"
#include <iostream>

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<uint32_t> _indices)
	: m_Vertices{_vertices}, m_Indices { _indices }
{
    m_MeshHeader.m_VerticesCount = static_cast<uint32_t>(m_Vertices.size());
    m_MeshHeader.m_IndicesCount = static_cast<uint32_t>(m_Indices.size());
}

Model::Model(std::string const& _path)
{
	LoadModel(_path);
}

void Model::LoadModel(std::string const& _path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(_path
        , aiProcess_Triangulate                // Make sure we get triangles rather than nvert polygons             ///yes
        | aiProcess_LimitBoneWeights           // 4 weights for skin model max
        | aiProcess_GenUVCoords                // Convert any type of mapping to uv mapping
        | aiProcess_TransformUVCoords          // preprocess UV transformations (scaling, translation ...)
        | aiProcess_FindInstances              // search for instanced meshes and remove them by references to one master
        | aiProcess_CalcTangentSpace           // calculate tangents and bitangents if possible                 ///yes
        | aiProcess_JoinIdenticalVertices      // join identical vertices/ optimize indexing
        | aiProcess_RemoveRedundantMaterials   // remove redundant materials
        | aiProcess_FindInvalidData            // detect invalid model data, such as invalid normal vectors
        | aiProcess_PreTransformVertices       // pre-transform all vertices
        | aiProcess_FlipUVs                    // flip the V to match the Vulkans way of doing UVs              ///yes
        | aiProcess_OptimizeMeshes
    );

    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        ML_DEBUG("ERROR::ASSIMP:: %s", importer.GetErrorString());
        return;
    }
    // retrieve the directory path of the filepath
     std::string m_Directory = _path.substr(0, _path.find_last_of('/'));

    // process ASSIMP's root node recursively
    ProcessNode(scene->mRootNode, scene);

    //update mesh size
    m_ModelHeader.m_MeshCount = static_cast <uint32_t>(m_Meshes.size());
}


void Model::ProcessNode(aiNode* _node, const aiScene* _scene)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < _node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = _scene->mMeshes[_node->mMeshes[i]];
        m_Meshes.push_back(ProcessMesh(mesh, _scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < _node->mNumChildren; i++)
    {
        ProcessNode(_node->mChildren[i], _scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* _mesh, const aiScene* _scene)
{
    UNREFERENCED_PARAMETER(_scene);         //for textures
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    //std::vector<Texture> textures;

    float minX = 0, maxX = 0;
    float minY = 0, maxY = 0;
    float minZ = 0, maxZ = 0;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < _mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

        if (_mesh->mVertices[i].x < minX)
            minX = _mesh->mVertices[i].x;
        if (_mesh->mVertices[i].x > maxX)
            maxX = _mesh->mVertices[i].x;

        if (_mesh->mVertices[i].x < minY)
            minY = _mesh->mVertices[i].x;
        if (_mesh->mVertices[i].x > maxY)
            maxY = _mesh->mVertices[i].x;

        if (_mesh->mVertices[i].x < minZ)
            minZ = _mesh->mVertices[i].x;
        if (_mesh->mVertices[i].x > maxZ)
            maxZ = _mesh->mVertices[i].x;

        // positions
        vector.x = _mesh->mVertices[i].x;
        vector.y = _mesh->mVertices[i].y;
        vector.z = _mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (_mesh->HasNormals())
        {
            vector.x = _mesh->mNormals[i].x;
            vector.y = _mesh->mNormals[i].y;
            vector.z = _mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if (_mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = _mesh->mTextureCoords[0][i].x;
            vec.y = _mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
            // tangent
            vector.x = _mesh->mTangents[i].x;
            vector.y = _mesh->mTangents[i].y;
            vector.z = _mesh->mTangents[i].z;
            vertex.tangent = vector;
            // bitangent
            vector.x = _mesh->mBitangents[i].x;
            vector.y = _mesh->mBitangents[i].y;
            vector.z = _mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    //normalize all vertices
    glm::mat4 normalizer = glm::mat4(1.0f);
    normalizer = glm::scale(normalizer, { 1 / (maxX - minX), 1 / (maxY - minY) , 1 / (maxZ - minZ) });

    for (auto& vert : vertices)
    {
        vert.position = normalizer * glm::vec4{ vert.position, 1.0 };
    }


    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
    {
        aiFace face = _mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }


    return Mesh(vertices, indices);
}

const Model& Model::ExportModel(void) const
{
    return *this;

#if 0
    //printing test
    for (auto& mesh : m_Meshes)
    {
        //std::cout << mesh << std::endl;
        std::cout << "Mesh size: " << sizeof(mesh) << std::endl;
    }
#endif
    
}

/******************************************************************************/
/*!
    \brief    for printing, prints all details in mesh
    \param    _os
    \param    _mesh
    \return   
*/
/******************************************************************************/
std::ostream& operator<<(std::ostream& _os, const Mesh& _mesh)
{
    for (const auto& v : _mesh.m_Vertices)
    {
        _os << "Vertex: " << "pos " << glm::to_string(v.position)
            << std::endl << "norm " << glm::to_string(v.normal)
            << std::endl << "tangent " << glm::to_string(v.tangent)
            << std::endl << "bitan" << glm::to_string(v.bitangent)
            << std::endl << "texcoord " << glm::to_string(v.texCoords)
            << std::endl;
    }

    _os << "mesh indices: ";

    for (auto i : _mesh.m_Indices)
    {
        _os << i << " ";
    }

    return _os;
}
