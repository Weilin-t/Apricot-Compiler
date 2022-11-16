/*****************************************************************/
/*!
\file   Melon_Skeleton.h

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   22 October 2022
\brief  This file contains definition of skeleton information

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/*********************************************************************/
#include "Melon_Skeleton.h"

static inline glm::vec3 GetGLMVec(const aiVector3D& vec)
{
	return glm::vec3(vec.x, vec.y, vec.z);
}

static inline glm::quat GetGLMQuat(const aiQuaternion& pOrientation)
{
	return glm::quat(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
}

Bone::Bone(const std::string& _name, int _id, const aiNodeAnim* _channel) : m_Name(_name), m_ID(_id), m_LocalTransform(1.f)
{
	m_NumPositions = _channel->mNumPositionKeys;
	for (int posIndex{ 0 }; posIndex < m_NumPositions; ++posIndex) {
		aiVector3D aiPos = _channel->mPositionKeys[posIndex].mValue;
		KeyPosition data;
		data.m_position = GetGLMVec(aiPos);
		data.m_timeStamp = static_cast<float>(_channel->mPositionKeys[posIndex].mTime);

		m_Positions.push_back(data);
	}

	m_NumRotations = _channel->mNumRotationKeys;
	for (int rotIndex{ 0 }; rotIndex < m_NumRotations; ++rotIndex) {
		aiQuaternion aiQuat = _channel->mRotationKeys[rotIndex].mValue;
		KeyRotation data;
		data.m_orientation = GetGLMQuat(aiQuat);
		data.m_timeStamp = static_cast<float>(_channel->mRotationKeys[rotIndex].mTime);

		m_Rotations.push_back(data);
	}

	m_NumScalings = _channel->mNumScalingKeys;
	for (int keyIndex{ 0 }; keyIndex < m_NumScalings; ++keyIndex) {
		aiVector3D aiScale = _channel->mScalingKeys[keyIndex].mValue;
		KeyScale data;
		data.m_scale = GetGLMVec(aiScale);
		data.m_timeStamp = static_cast<float>(_channel->mScalingKeys[keyIndex].mTime);

		m_Scales.push_back(data);
	}
}
