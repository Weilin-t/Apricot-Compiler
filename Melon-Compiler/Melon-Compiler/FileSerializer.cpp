/*****************************************************************/
/*!
\file   FileSerializer.cpp

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   23 September 2022
\brief  This file contains definition for file serialization

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/
#include "FileSerializer.h"
#include "Asserts.h"

#include <iostream>

void FileDetails::SerializeFile(std::string _filepath)
{
	m_ModelCreated = Model(_filepath);
	m_AnimationCreated = Melon_Animation(_filepath, &m_ModelCreated);

	//Update model header to show if animation
	m_ModelCreated.m_ModelHeader.m_Animation = 
		(m_AnimationCreated.GetRootNode().m_name == "") ? 0 : 1;
}



/******************************************************************************/
/*!
    \brief    Store loaded buffer into a new file
    \param    _folderpath
    \param    buffer
*/
/******************************************************************************/
void FileDetails::GenerateFile(std::string _folderpath, Model _model)
{
	std::ofstream newFile(_folderpath + m_Filename + MELON_EXTENSION, std::ios::out | std::ios::binary);

	if (newFile.good())
	{
		//write header, size of meshes
		newFile.write((const char*)(&_model.m_ModelHeader), sizeof(_model.m_ModelHeader));

		for (const auto& mesh : _model.GetMeshes())
		{
			//write each mesh header
			newFile.write((const char*)(&mesh.m_MeshHeader), sizeof(mesh.m_MeshHeader));

			newFile << std::endl;

			//write all vertices
			newFile.write((const char*)(&mesh.GetVertices()[0]), sizeof(Vertex) * mesh.GetVerticesSize());

			newFile << std::endl;

			//write all indices
			newFile.write((const char*)(&mesh.GetIndices()[0]), sizeof(uint32_t) * mesh.GetIndicesSize());

			newFile << std::endl;
		}

		newFile << std::endl;
		//write bone info
		for (auto& bone : _model.GetBoneInfoMap())
		{
			//write size of string
			int sizestring = static_cast<int>(bone.first.size());

			newFile.write((const char*)(&sizestring), sizeof(int));
			newFile.write((const char*)(&bone.first[0]), sizeof(char) * sizestring);
			newFile.write((const char*)(&bone.second), sizeof(bone.second));
			newFile << std::endl;
		}

		newFile << std::endl;

		//animation details
		if (*&_model.m_ModelHeader.m_Animation == 1)
		{
			newFile.write((const char*)(&m_AnimationCreated.GetDuration()), sizeof(float));
			newFile.write((const char*)(&m_AnimationCreated.GetTicksPerSecond()), sizeof(int));
			
			newFile << std::endl;

			//write size of bones
			int vecBonesSize = static_cast<int>(m_AnimationCreated.GetBones().size());
			newFile.write((const char*)(&vecBonesSize), sizeof(int));

			//write vec of bones
			for (int i{ 0 }; i < vecBonesSize; i++)
			{
				newFile.write((const char*)(&m_AnimationCreated.GetBones()[i].GetBoneID()), sizeof(int));

				newFile << std::endl;

				int sizestring = static_cast<int>(m_AnimationCreated.GetBones()[i].GetBoneName().size());
				newFile.write((const char*)(&sizestring), sizeof(int));
				newFile.write((const char*)(&m_AnimationCreated.GetBones()[i].GetBoneName()[0]), sizeof(char) *
					sizestring);

				newFile << std::endl;
				//std::cout << m_AnimationCreated.GetBones()[i].GetBoneName() << std::endl;

				newFile.write((const char*)(&m_AnimationCreated.GetBones()[i].GetLocalTransform()), sizeof(glm::mat4));

				//pos
				newFile.write((const char*)(&m_AnimationCreated.GetBones()[i].GetNumPos()), sizeof(int));
				newFile.write((const char*)(&m_AnimationCreated.GetBones()[i].GetPos()[0]), sizeof(KeyPosition)
					* m_AnimationCreated.GetBones()[i].GetNumPos());
				
				//rot
				newFile.write((const char*)(&m_AnimationCreated.GetBones()[i].GetNumRot()), sizeof(int));
				newFile.write((const char*)(&m_AnimationCreated.GetBones()[i].GetRot()[0]), sizeof(KeyRotation)
					* m_AnimationCreated.GetBones()[i].GetNumRot());
				
				//scale
				newFile.write((const char*)(&m_AnimationCreated.GetBones()[i].GetNumScale()), sizeof(int));
				newFile.write((const char*)(&m_AnimationCreated.GetBones()[i].GetScale()[0]), sizeof(KeyScale)
					* m_AnimationCreated.GetBones()[i].GetNumScale());
				
				newFile << std::endl;
			}

			//write boneinfomap

			//write rootnode details
			RecursiveWriteNodes(newFile, m_AnimationCreated.GetRootNode());
			

			//newFile.write((const char*)(&m_AnimationCreated.GetRootNode().m_transformation), sizeof(glm::mat4));
			//
			//int sizestring = static_cast<int>(m_AnimationCreated.GetRootNode().m_name.size());
			//newFile.write((const char*)(&sizestring), sizeof(int));
			//newFile.write((const char*)(&m_AnimationCreated.GetRootNode().m_name[0]), sizeof(char) * sizestring);
			//
			//newFile.write((const char*)(&m_AnimationCreated.GetRootNode().m_childrenCount), sizeof(int));
			//
			//newFile.write((const char*)(&m_AnimationCreated.GetRootNode().m_children[0]), 
			//	sizeof(Melon_Animation_Node) *
			//	m_AnimationCreated.GetRootNode().m_childrenCount);

			newFile << std::endl;
		}

		newFile.close();
	}
	else
		std::cout << "Failed to generate file " << _folderpath << m_Filename << MELON_EXTENSION << std::endl;

}


void FileDetails::RecursiveWriteNodes(std::ofstream& _newFile, Melon_Animation_Node& _node)
{
	_newFile.write((const char*)(&_node.m_transformation), sizeof(glm::mat4));

	int sizestring = static_cast<int>(_node.m_name.size());
	_newFile.write((const char*)(&sizestring), sizeof(int));
	_newFile.write((const char*)(&_node.m_name[0]), sizeof(char) * sizestring);

	_newFile.write((const char*)(&_node.m_childrenCount), sizeof(int));
	
	for (int i{ 0 }; i < _node.m_childrenCount; i++)
	{
		RecursiveWriteNodes(_newFile, _node.m_children[i]);
	}
}
