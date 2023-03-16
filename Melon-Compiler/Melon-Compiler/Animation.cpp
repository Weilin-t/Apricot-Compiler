#include "Animation.h"

Melon_Animation::Melon_Animation(const std::string& _animationPath, Model* _model)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_animationPath, aiProcess_Triangulate
		| aiProcess_LimitBoneWeights           // 4 weights for skin model max
		| aiProcess_GenUVCoords                // Convert any type of mapping to uv mapping
		| aiProcess_TransformUVCoords          // preprocess UV transformations (scaling, translation ...)
		| aiProcess_FindInstances              // search for instanced meshes and remove them by references to one master
		| aiProcess_CalcTangentSpace           // calculate tangents and bitangents if possible                 ///yes
		| aiProcess_JoinIdenticalVertices      // join identical vertices/ optimize indexing
		| aiProcess_RemoveRedundantMaterials   // remove redundant materials
		| aiProcess_FindInvalidData            // detect invalid model data, such as invalid normal vectors
		| aiProcess_FlipUVs                    // flip the V to match the Vulkans way of doing UVs              ///yes
		| aiProcess_OptimizeMeshes);
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

	_model->m_ModelHeader.m_HashMapBoneCount = static_cast<uint32_t>(m_BoneInfoMap.size());
}

void Melon_Animation::ReadMissingBones(const aiAnimation* _animation, Model& _model)
{
	assert(m_BoneInfoMap.size() == 0);
	assert(m_Bones.size() == 0);

	//get info of bones in model class
	auto& boneInfoMap = _model.GetBoneInfoMap();
	int   boneCount   = static_cast<int>(_model.GetBoneInfoMap().size());

	//read channels (bones in animation and keyframes)
	for (int i{ 0 }; i < static_cast<int>(_animation->mNumChannels); i++)
	{
		auto&       channel  = *_animation->mChannels[i];
		std::string boneName = channel.mNodeName.data;
		auto        FB       = boneInfoMap.find(boneName);

		if(FB == boneInfoMap.end())
		{
			boneInfoMap[boneName].m_id = boneCount;
			m_Bones.push_back(Bone{ boneName, boneCount, &channel });
			boneCount++;
		}
		else
		{
			m_Bones.push_back(Bone{ FB->first, FB->second.m_id, &channel });
		}
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
