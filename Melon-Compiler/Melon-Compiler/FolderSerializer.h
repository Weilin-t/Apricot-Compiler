/*****************************************************************/
/*!
\file   FolderSerializer.h

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   24 September 2022
\brief  This file contains declaration for folder serializing

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/
#pragma once

#include "FileSerializer.h"

class FolderReader {

public:
	//initialize folder with folder path
	FolderReader(std::string _folderpath) : m_Folderpath{ _folderpath } {}

	//loop through folder for all files
	void ScanFolder(std::string _folderpath);

	std::string GetFolderPath(void) { return m_Folderpath; }

private:
	//void SerializeFile(std::string _filepath);
	void SerializeFile(std::filesystem::path _filepath);

private:

	std::string m_Folderpath;
	std::vector <FileDetails> m_FilesInFolder;
};
