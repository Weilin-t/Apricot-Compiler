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

#include "Details.h"

#include <iostream>

int main(void)
{
	//std::cout << std::filesystem::current_path() << "\n";
	
	//read config file to find all .fbx
	std::ifstream config("cp_config.txt", std::ios::in);

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
		std::cout << "Failed to load config file\n";

#if 0
	//try to reacess the data generated to get the info
	std::ifstream in("assets\\level\\Cube.melon", std::ios::binary | std::ios::in);
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
		}

		std::cout << "=================================================\n";

		std::cout << "model info " << model.m_ModelHeader.m_MeshCount << 
			" mesh headers vertices " << model.GetMeshes()[0].m_MeshHeader.m_VerticesCount <<
			" mesh header indices " << model.GetMeshes()[0].m_MeshHeader.m_IndicesCount << std::endl;

		for (auto& m : model.GetMeshes())
		{
			std::cout << m << std::endl;
			std::cout << "-------------------------------------------\n";
		}

	}
	else
	{
		std::cout << "Failed to open file" << std::endl;
	}

	in.close();
#endif

	return 0;
}
