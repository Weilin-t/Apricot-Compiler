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
	//read config file to find all .fbx
	SerializeFolder folder("..\\Assets\\");
	folder.ScanFolder();
	folder.SerializeFiles();
	
	//generates all the .mel, compressed fbx files



	//try to reacess the data generated to get the info
	std::ifstream in("..\\Assets\\Generated\\Cube.melon");
	if (in.good())
	{
		Model model;
		while (in.read(reinterpret_cast<char*>(&model), sizeof(model)));
		{
			for (auto& mesh : model.m_Meshes)
				std::cout << mesh << std::endl;
		}
	}
	else
	{
		std::cout << "Failed to open file" << std::endl;
	}

	return 0;
}
