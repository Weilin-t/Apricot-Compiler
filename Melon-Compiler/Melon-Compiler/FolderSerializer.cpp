/*****************************************************************/
/*!
\file   FolderSerializer.cpp

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   24 September 2022
\brief  This file contains definition for folder serializing

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/
/*********************************************************************/
#include "Asserts.h"
#include "FolderSerializer.h"

#include <iostream>

/******************************************************************************/
/*!
    \brief    gets all the files in folder
*/
/******************************************************************************/
void SerializeFolder::ScanFolder(void)
{
	for (const auto& file : std::filesystem::directory_iterator(m_Folderpath))
	{
		if (file.is_directory())
			continue;

		ML_ASSERT((file.path().filename().extension() != ".fbx"), "File extension %ws not supported!\n",
			file.path().filename().extension().c_str());


		m_FilesInFolder.push_back(FileDetails(file.path().stem().string()));
	}

#if 0
	for (auto& file : m_FilesInFolder)
		std::cout << file.GetFilename() << std::endl;
#endif
}

/******************************************************************************/
/*!
    \brief    does the converting from fbx to melon
*/
/******************************************************************************/
void SerializeFolder::SerializeFiles(void)
{
#if 0
	//normal file serializer
	for (auto file : m_FilesInFolder)
		file.SerializeFile(m_Folderpath);
#endif

	//read and grab all data in files
	//one file to have "one model"
	for (auto file : m_FilesInFolder)
		m_vecModels.push_back(Model(m_Folderpath + file.GetFilename() + ".fbx", false));

	for (int i{ 0 }; i < m_FilesInFolder.size(); i++)
	{
		//grab all data and serialize file
		m_FilesInFolder[i].GenerateFile(m_Folderpath + "Generated\\", m_vecModels[i].ExportModel());
	}


#if 0
	//vector of all the imported files model data
	for (auto f : m_vecModels)
		f.ExportModel();
#endif
}
