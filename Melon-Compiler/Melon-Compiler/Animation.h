/*****************************************************************/
/*!
\file   Animation.h

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   27 October 2022
\brief  This file contains stored animation information

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/*********************************************************************/
#ifndef ANIMATION
#define ANIMATION

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include "Model.h"

typedef struct Melon_Animation_Node {
	glm::mat4 m_transformation { 0 };
	std::string m_name = "";
	int m_childrenCount = 0;
	std::vector<Melon_Animation_Node> m_children = {};

} Melon_Animation_Node;

typedef class Melon_Animation {
public:
	Melon_Animation() = default;

	Melon_Animation(const std::string& _animationPath, Model* _model);

	~Melon_Animation() {}

	int& GetTicksPerSecond() { return m_TicksPerSecond; }
	float& GetDuration() { return m_Duration; }
	Melon_Animation_Node& GetRootNode() { return m_RootNode; }
	std::map<std::string, BoneInfo>& GetBoneIDMap() { return m_BoneInfoMap; }
	std::vector<Bone>& GetBones() { return m_Bones; }

	void SetDuration(float _duration) { m_Duration = _duration; }
	void SetTicks(int _ticks) { m_TicksPerSecond = _ticks; }
	void SetRootNode(glm::mat4 _trans, std::string _name, int _childrenCount,
		std::vector<Melon_Animation_Node> _children) {
		m_RootNode.m_transformation = _trans;
		m_RootNode.m_name = _name;
		m_RootNode.m_childrenCount = _childrenCount;
		m_RootNode.m_children = _children;
	}
private:
	/******************************************************************************/
	/*!
	    \brief    Read all bones used in animation
	    \param    _animation
	    \param    _model
	*/
	/******************************************************************************/
	void ReadMissingBones(const aiAnimation* _animation, Model& _model);

	/******************************************************************************/
	/*!
	    \brief    Recursively find all bones used in animation
	    \param    dest
	    \param    src
	*/
	/******************************************************************************/
	void ReadHeirarchyData(Melon_Animation_Node& dest, const aiNode* src);

private:

	float								m_Duration{ 0 };
	int									m_TicksPerSecond{ 0 };
	std::vector<Bone>					m_Bones;
	std::map<std::string, BoneInfo>		m_BoneInfoMap;
	Melon_Animation_Node				m_RootNode;

} Melon_Animation;


#endif // !ANIMATION
