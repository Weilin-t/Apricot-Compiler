/*****************************************************************/
/*!
\file   FileSerializer.h

\author Tan Weilin, Weilin
\par    Email: weilin.t@digipen.edu
\date   23 September 2022
\brief  This file contains declaration for file serializer

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
*/ 
/*********************************************************************/
#pragma once

#include <fstream>
#include <iterator>
#include <string>
#include <filesystem>

class FileDetails {
public:

	FileDetails(std::string _filename) : m_Filename{ _filename } {}
	
	std::string GetFilename(void)
	{
		return m_Filename;
	}

	friend std::ostream& operator<<(std::ostream& _os, const FileDetails file)
	{
		_os << file.m_Filename << std::endl;
		return _os;
	}

	void SerializeFile(std::string _folderpath);

private:

	std::string m_Filename;
};


class SerializeFolder {

public:
	//initialize folder with folder path
	SerializeFolder(std::string _folderpath) : m_Folderpath{ _folderpath } {}

	//loop through folder for all files
	void ScanFolder(void);

	void SerializeFiles(void);

private:


	std::string m_Folderpath;
	std::vector <FileDetails> m_FilesInFolder;
};
