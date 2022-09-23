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

#include "Compiler.h"
#include "FileSerializer.h"

int main(void)
{
	//read config file to find all .fbx
	SerializeFolder folder("..\\Assets\\");
	folder.ScanFolder();
	folder.SerializeFiles();
	
	//generates all the .mel, compressed fbx files


	return 0;
}