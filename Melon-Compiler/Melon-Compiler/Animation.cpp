#include "Animation.h"

Melon_Animation::Melon_Animation(const std::string& _animationPath, Model* _model)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_animationPath, aiProcess_Triangulate);
	assert(scene && scene->mRootNode);

	if (!scene->mAnimations)
		return;

	auto animation = scene->mAnimations[0];
	m_Duration = static_cast<float>(animation->mDuration);
	m_TicksPerSecond = static_cast<int>(animation->mTicksPerSecond);
	//aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
	//globalTransformation = globalTransformation.Inverse();
	ReadHeirarchyData(m_RootNode, scene->mRootNode);
	ReadMissingBones(animation, *_model);
}

void Melon_Animation::ReadMissingBones(const aiAnimation* _animation, Model& _model)
{

	//get info of bones in model class
	auto& boneInfoMap = _model.GetBoneInfoMap();
	int& boneCount = _model.GetBoneCount();

	//read channels (bones in animation and keyframes)
	for (int i{ 0 }; i < static_cast<int>(_animation->mNumChannels); i++)
	{
		auto channel = _animation->mChannels[i];
		std::string boneName = channel->mNodeName.data;

		if (boneInfoMap.find(boneName) == boneInfoMap.end())
		{
			boneInfoMap[boneName].m_id = boneCount;
			boneCount++;
		}
		m_Bones.push_back(Bone(channel->mNodeName.data, boneInfoMap[channel->mNodeName.data].m_id, channel));
	}

	m_BoneInfoMap = boneInfoMap;
}

glm::mat4 AssimpToGlmMat(const aiMatrix4x4& _m)
{
	glm::mat4 tmp{ 0 };
	tmp[0][0] = _m.a1; tmp[1][0] = _m.a2; tmp[2][0] = _m.a3; tmp[3][0] = _m.a4;
	tmp[0][1] = _m.b1; tmp[1][1] = _m.b2; tmp[2][1] = _m.b3; tmp[3][1] = _m.b4;
	tmp[0][2] = _m.c1; tmp[1][2] = _m.c2; tmp[2][2] = _m.c3; tmp[3][2] = _m.c4;
	tmp[0][3] = _m.d1; tmp[1][3] = _m.d2; tmp[2][3] = _m.d3; tmp[3][3] = _m.d4;
	return tmp;
}

void Melon_Animation::ReadHeirarchyData(Melon_Animation_Node& dest, const aiNode* src)
{
	assert(src);

	dest.m_name = src->mName.data;
	dest.m_transformation = AssimpToGlmMat(src->mTransformation);
	dest.m_childrenCount = src->mNumChildren;

	//copy all children
	for (int i{ 0 }; i < static_cast<int>(src->mNumChildren); i++)
	{
		Melon_Animation_Node newData;
		ReadHeirarchyData(newData, src->mChildren[i]);
		dest.m_children.push_back(newData);
	}
}
