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

#include "Model.h"
#include "Animation.h"

constexpr auto MELON_EXTENSION = ".melon";

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

	void SerializeFile(std::string _filepath);

	void GenerateFile(std::string _folderpath, Model _model);

	Model& GetModel(void) { return m_ModelCreated; }
	Melon_Animation& GetAnimation(void) { return m_AnimationCreated; }

private:
	void RecursiveWriteNodes(std::ofstream& _newFile, Melon_Animation_Node& _node);

private:

	std::string m_Filename;

	Model m_ModelCreated;
	Melon_Animation m_AnimationCreated;
};
