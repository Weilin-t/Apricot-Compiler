/*****************************************************************/
/*!
\file   Melon_Skeleton.h

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   22 October 2022
\brief  This file contains declaration of skeleton information

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/
#ifndef MELON_SKELETON
#define MELON_SKELETON

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <assimp/anim.h>

typedef struct BoneInfo
{
    //id in finalbonematrices
    int m_id;

    //offset matrix transforms vertex from model space to bone space
    glm::mat4 m_offset;
} BoneInfo;

//individual bone details
typedef struct KeyPosition
{
    glm::vec3 m_position;
    float m_timeStamp;
} KeyPosition;

typedef struct KeyRotation
{
    glm::quat m_orientation;
    float m_timeStamp;
} KeyRotation;

typedef struct KeyScale
{
    glm::vec3 m_scale;
    float m_timeStamp;
} KeyScale;

typedef class Bone {
public:
    Bone(const std::string& _name, int _id, const aiNodeAnim* _channel);  
    Bone() = default;
    //update bone information

public:
    glm::mat4& GetLocalTransform() { return m_LocalTransform; }
    std::string& GetBoneName() { return m_Name; }
    int& GetBoneID() { return m_ID; }

    int& GetNumPos() { return m_NumPositions; }
    int& GetNumRot() { return m_NumRotations; }
    int& GetNumScale() { return m_NumScalings; }

    std::vector<KeyPosition>& GetPos() { return m_Positions; }
    std::vector<KeyRotation>& GetRot() { return m_Rotations; }
    std::vector<KeyScale>& GetScale() { return m_Scales; }

private:
    std::vector<KeyPosition> m_Positions;
    std::vector<KeyRotation> m_Rotations;
    std::vector<KeyScale> m_Scales;

    int m_NumPositions = 0;
    int m_NumRotations = 0;
    int m_NumScalings = 0;

    glm::mat4 m_LocalTransform;
    std::string m_Name;
    int m_ID;
} Bone;

#endif
    