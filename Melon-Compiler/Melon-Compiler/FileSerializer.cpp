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

void SerializeFolder::ScanFolder(void)
{
	for (const auto& file : std::filesystem::directory_iterator(m_Folderpath))
	{
		ML_ASSERT((file.path().filename().extension() != ".fbx"), "File extension %ws not supported!\n", 
			file.path().filename().extension().c_str());

		m_FilesInFolder.push_back(FileDetails(file.path().filename().string()));
	}

#if 0
	for (auto& file : m_FilesInFolder)
		std::cout << file.GetFilename() << std::endl;
#endif
}

void SerializeFolder::SerializeFiles(void)
{
	for (auto file : m_FilesInFolder)
		file.SerializeFile(m_Folderpath);
}


void FileDetails::SerializeFile(std::string _folderpath)
{
	ML_DEBUG(true, "Serializing all Files...\n");
	std::ifstream input(_folderpath + m_Filename, std::ios::in | std::ios::binary);
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});


	input.close();

#if 0
	//checking buffer
	for (const auto& buff : buffer)
		std::cout << buff;
#endif
}
