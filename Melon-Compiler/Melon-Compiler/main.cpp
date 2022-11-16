/*****************************************************************/
/*!
\file   main.cpp

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   20 September 2022
\brief  This file is the starting point of the compiler

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/

#include "FolderSerializer.h"

#include <iostream>

#if 0
void RecurisveReadNodes(std::ifstream& _in, Melon_Animation_Node& _rootNode)
{
	_in.read(reinterpret_cast<char*>(&_rootNode.m_transformation), sizeof(glm::mat4));

	std::string tmpstring;
	int tmpint = 0;
	_in.read(reinterpret_cast<char*>(&tmpint), sizeof(int));
	tmpstring.resize(tmpint);
	_in.read(reinterpret_cast<char*>(&tmpstring[0]), sizeof(char) * tmpint);
	_rootNode.m_name = tmpstring;

	//children
	_in.read(reinterpret_cast<char*>(&_rootNode.m_childrenCount), sizeof(int));
	for (int i{ 0 }; i < _rootNode.m_childrenCount; i++)
	{
		Melon_Animation_Node tmpNode;
		RecurisveReadNodes(_in, tmpNode);
		_rootNode.m_children.push_back(tmpNode);
	}
}
#endif

int main(int argc, char** argv)
{
	std::string configpath = "cp_config.txt";

	//only read the first agrv
	if (argc == 2)
		configpath = argv[1];
	else if (argc == 1)		//being explicit here
		exit(0);
	else
		std::cout << "Failed to execute compiler\n";

	//read config file to find all .fbx
	std::ifstream config(configpath, std::ios::in);

	if (config.good())
	{
		std::string filepath{};
		while (std::getline(config, filepath))
		{
			FolderReader folder(filepath);

			//generate the .melon
			folder.ScanFolder(folder.GetFolderPath());

			//remove if reading from multiple assets folder
			break;
		}

		config.close();
	}
	else
		perror(configpath.c_str());

#if 0
	//try to reacess the data generated to get the info
	std::ifstream in("assets\\star\\silly_dancing.melon", std::ios::binary | std::ios::in);
	//in.seekg(0)
	if (in.good())
	{
		Model model;
		//read model header
		if (in.read(reinterpret_cast<char*>(&model.m_ModelHeader), sizeof(model.m_ModelHeader)))
		{
			//read all mesh header and meshes
			for (uint32_t i{ 0 }; i < model.m_ModelHeader.m_MeshCount; i++)
			{
				//temp mesh
				Mesh tmpMesh;

				
				//read mesh header
				in.read(reinterpret_cast<char*>(&tmpMesh.m_MeshHeader), sizeof(tmpMesh.m_MeshHeader));

				in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


 				for (uint32_t j{ 0 }; j < tmpMesh.m_MeshHeader.m_VerticesCount; j++)
				{
					Vertex tmpVert;
					in.read(reinterpret_cast<char*>(&tmpVert), sizeof(Vertex));
					tmpMesh.PushbackVertices(tmpVert);
				}

				in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				for (uint32_t j{ 0 }; j < tmpMesh.m_MeshHeader.m_IndicesCount; j++)
				{
					uint32_t tmpInd;
					in.read(reinterpret_cast<char*>(&tmpInd), sizeof(uint32_t));
					tmpMesh.PushbackIndices(tmpInd);
				}

				in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				//append mesh to model
				model.PushbackMesh(tmpMesh);
			}


			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			//read bone info
			for (uint32_t bone_count{ 0 }; bone_count < static_cast<uint32_t>(model.m_ModelHeader.m_BoneCount); bone_count++)
			{
				//create new bone info
				int stringsize = 0;
				std::string boneName;
				BoneInfo newBoneinfo;
				in.read(reinterpret_cast<char*>(&stringsize), sizeof(int));
				boneName.resize(stringsize);
				in.read(reinterpret_cast<char*>(&boneName[0]), sizeof(char) * stringsize);
				in.read(reinterpret_cast<char*>(&newBoneinfo), sizeof(BoneInfo));

				in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				model.GetBoneInfoMap().insert({ boneName, newBoneinfo });
				//model.GetBoneInfoMap().insert(std::map<std::string, BoneInfo>::value_type(boneName, newBoneinfo));
			}

			//update model bone count
			model.GetBoneCount() = model.m_ModelHeader.m_BoneCount;
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			//check if animation
			if (model.m_ModelHeader.m_Animation == 1)
			{
				Melon_Animation animation;

				float tmpfloat;
				int tmpint;
				in.read(reinterpret_cast<char*>(&tmpfloat), sizeof(float));
				animation.SetDuration(tmpfloat);
				in.read(reinterpret_cast<char*>(&tmpint), sizeof(int));
				animation.SetTicks(tmpint);

				in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				//vec of bones
				in.read(reinterpret_cast<char*>(&tmpint), sizeof(int));
				for (int i{ 0 }; i < tmpint; i++)
				{
					Bone tmpBone;
					//bone id
					in.read(reinterpret_cast<char*>(&tmpBone.GetBoneID()), sizeof(int));
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					//bone name
					int boneNameSize = 0;
					in.read(reinterpret_cast<char*>(&boneNameSize), sizeof(int));
					tmpBone.GetBoneName().resize(boneNameSize);
					in.read(reinterpret_cast<char*>(&tmpBone.GetBoneName()[0]), sizeof(char) * boneNameSize);
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					//transform
					in.read(reinterpret_cast<char*>(&tmpBone.GetLocalTransform()), sizeof(glm::mat4));

					//pos
					in.read(reinterpret_cast<char*>(&tmpBone.GetNumPos()), sizeof(int));
					for (int j{ 0 }; j < tmpBone.GetNumPos(); j++)
					{
						KeyPosition tmpPos;
						in.read(reinterpret_cast<char*>(&tmpPos), sizeof(KeyPosition));
						tmpBone.GetPos().push_back(tmpPos);
					}

					//rot 
					in.read(reinterpret_cast<char*>(&tmpBone.GetNumRot()), sizeof(int));
					for (int j{ 0 }; j < tmpBone.GetNumRot(); j++)
					{
						KeyRotation tmpRot;
						in.read(reinterpret_cast<char*>(&tmpRot), sizeof(KeyRotation));
						tmpBone.GetRot().push_back(tmpRot);
					}

					//scale
					in.read(reinterpret_cast<char*>(&tmpBone.GetNumScale()), sizeof(int));
					for (int j{ 0 }; j < tmpBone.GetNumScale(); j++)
					{
						KeyScale tmpScale;
						in.read(reinterpret_cast<char*>(&tmpScale), sizeof(KeyScale));
						tmpBone.GetScale().push_back(tmpScale);
					}

					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					animation.GetBones().push_back(tmpBone);
				}

				RecurisveReadNodes(in, animation.GetRootNode());

				std::cout << animation.GetRootNode().m_name << std::endl;
				////root node
				//in.read(reinterpret_cast<char*>(&animation.GetRootNode().m_transformation), sizeof(glm::mat4));

				////name
				//std::string tmpstring;
				//in.read(reinterpret_cast<char*>(&tmpint), sizeof(int));
				//tmpstring.resize(tmpint);
				//in.read(reinterpret_cast<char*>(&tmpstring[0]), sizeof(char) * tmpint);
				//animation.GetRootNode().m_name = tmpstring;

				////children
				//in.read(reinterpret_cast<char*>(&animation.GetRootNode().m_childrenCount), sizeof(int));
				//for (int i{ 0 }; i < tmpint; i++)
				//{
				//	Melon_Animation_Node tmpNode;
				//	in.read(reinterpret_cast<char*>(&tmpNode), sizeof(Melon_Animation_Node));
				//	animation.GetRootNode().m_children.push_back(tmpNode);
				//}

				//std::cout << glm::to_string(tmpmat) << std::endl
				//	<< tmpstring << std::endl;

				//animation.SetRootNode(tmpmat,)
			}
		}

		//std::cout << "=================================================\n";
		//std::cout << "model info " << model.m_ModelHeader.m_MeshCount << 
		//	" mesh headers vertices " << model.GetMeshes()[0].m_MeshHeader.m_VerticesCount <<
		//	" mesh header indices " << model.GetMeshes()[0].m_MeshHeader.m_IndicesCount << std::endl;

		//for (auto& m : model.GetMeshes())
		//{
		//	std::cout << m << std::endl;
		//	std::cout << "-------------------------------------------\n";
		//}


		//for (auto s : model.GetBoneInfoMap())
		//{
		//	std::cout << s.first << "    " << s.second.m_id << "    " << glm::to_string(s.second.m_offset) << std::endl;
		//}
	}
	else
	{
		std::cout << "Failed to open file" << std::endl;
	}

	in.close();
#endif

	return 0;
}
