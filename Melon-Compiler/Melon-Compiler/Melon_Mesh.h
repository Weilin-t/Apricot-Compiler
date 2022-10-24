/*****************************************************************/
/*!
\file   Melon_Mesh.h

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   22 October 2022
\brief  This file contains mesh definitions

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/
#ifndef MELON_MESH
#define MELON_MESH

#include <vector>
#include <cstdint>
#include <ostream>

#include "Melon_Vertex.h"

struct MeshHeader
{
    uint32_t m_VerticesCount = 0;
    uint32_t m_IndicesCount = 0;
};


typedef class Mesh
{
public:
    Mesh(void) = default;
    Mesh(std::vector<Vertex> _vertices, std::vector<uint32_t> _indices) : m_Vertices{ _vertices }, m_Indices{ _indices }
    {
        m_MeshHeader.m_VerticesCount = static_cast<uint32_t>(m_Vertices.size());
        m_MeshHeader.m_IndicesCount = static_cast<uint32_t>(m_Indices.size());
    }

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


#endif
