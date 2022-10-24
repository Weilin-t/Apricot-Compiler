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

struct BoneInfo
{
    //id in finalbonematrices
    int m_id;

    //offset matrix transforms vertex from model space to bone space
    glm::mat4 m_offset;
};


#endif
    