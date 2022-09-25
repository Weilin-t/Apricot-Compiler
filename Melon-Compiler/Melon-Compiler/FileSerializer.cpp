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

/*
*  UNUSED
*/
void FileDetails::SerializeFile(std::string _folderpath)
{
	ML_DEBUG(true, "Serializing %s File...\n", m_Filename);
	std::ifstream input(_folderpath + m_Filename + ".fbx", std::ios::in | std::ios::binary);
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});


	input.close();


	//GenerateFile(_folderpath + "Generated\\", buffer);
#if 0
	//checking buffer
	for (const auto& buff : buffer)
		std::cout << buff;
#endif
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
#if 0
	std::ofstream newFile(_folderpath + m_Filename + MELON_EXTENSION, std::ios::out | std::ios::binary);
	std::copy(buffer.cbegin(), buffer.cend(),
		std::ostream_iterator<unsigned char>(newFile));

	newFile.close();
#endif

	std::ofstream newFile(_folderpath + m_Filename + MELON_EXTENSION, std::ios::out | std::ios::binary);

	if (newFile.good())
	{
		//get string length
		//newFile.write(buffer.c_str(), buffer.size());
		//newFile.write(reinterpret_cast<const char*>(&_model), sizeof(_model));
	}
	else
		std::cout << "Failed to generate file " << _folderpath << m_Filename << MELON_EXTENSION << std::endl;

	newFile.close();
}
