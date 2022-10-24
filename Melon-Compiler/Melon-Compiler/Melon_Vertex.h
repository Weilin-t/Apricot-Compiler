/*****************************************************************/
/*!
\file   Melon_Vertex.h

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   22 October 2022
\brief  This file contains vertex definitions for vertex

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/
#ifndef MELON_VERTEX
#define MELON_VERTEX

#define MAX_BONE_INFLUENCE 4

typedef struct Vertex
{
    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec2 m_texCoords;
    glm::vec3 m_tangent;
    glm::vec3 m_bitangent;

    //bone indexes which will influence this vertex
    int m_boneIDs[MAX_BONE_INFLUENCE];

    //weights from each bone
    float m_weights[MAX_BONE_INFLUENCE];
}Vertex;

#endif