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
	//ML_DEBUG(true, "Serializing %s File...\n", m_Filename);
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
		
		//write header, size of meshes
		//std::cout << "Writing header mesh count " << _model.m_ModelHeader.m_MeshCount << std::endl;
		newFile.write((const char*)(&_model.m_ModelHeader), sizeof(_model.m_ModelHeader));

		for (const auto& mesh : _model.GetMeshes())
		{
			//std::cout << "Writing header of vertices count " << mesh.m_MeshHeader.m_VerticesCount << std::endl;
			//std::cout << "Writing header of indices count " << mesh.m_MeshHeader.m_IndicesCount << std::endl;
			
			//write each mesh header
			newFile.write((const char*)(&mesh.m_MeshHeader), sizeof(mesh.m_MeshHeader));

			newFile << std::endl;

			//write all vertices
			//for (const auto& vert : mesh.GetVertices())
			//	newFile.write((const char*)(&vert), sizeof(vert));

			////write all indices
			//for (const auto& indices : mesh.GetIndices())
			//	newFile.write((const char*)(indices), sizeof(vert));

			//write all vertices
			newFile.write((const char*)(&mesh.GetVertices()[0]), sizeof(Vertex) * mesh.GetVerticesSize());

			newFile << std::endl;

			//write all indices
			newFile.write((const char*)(&mesh.GetIndices()[0]), sizeof(uint32_t) * mesh.GetIndicesSize());

			newFile << std::endl;
		}
		//newFile.write(reinterpret_cast<const char*>(&_model), sizeof(_model));
		newFile.close();
	}
	else
		std::cout << "Failed to generate file " << _folderpath << m_Filename << MELON_EXTENSION << std::endl;

}
