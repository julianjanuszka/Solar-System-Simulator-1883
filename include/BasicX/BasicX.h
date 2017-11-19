/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/04
----------------------------------------------*/
#ifndef __BASICXFRAMEWORK_H_
#define __BASICXFRAMEWORK_H_

#pragma warning( disable : 4251 )

#include "BasicX\System\Definitions.h" //ReEng basic Definitions
#include "BasicX\System\SystemSingleton.h" //System related methods

#include "BasicX\System\Window.h" //WinAPI encapsulated methods
#include "BasicX\System\FileReader.h" //Reads an object and returns lines as strings
#include "BasicX\System\Folder.h" //Sets the working directory
#include "BasicX\System\GLSystem.h" //OpenGL 2.0 and 3.0 initialization

#include "BasicX\System\ShaderManager.h" //Shader Manager, loads and manages different shader files
#include "BasicX\System\ShaderCompiler.h" //Compiles the shader objects

#include "BasicX\Light\LightManager.h" //Manages the light sources of the world

#include "BasicX\materials\MaterialManager.h" //Manages the materials
#include "BasicX\materials\TextureManager.h" //Manages the Textures, loads, display and release

#include "BasicX\Mesh\Text.h" //Singleton for drawing Text on the screen
#include "BasicX\Mesh\Mesh.h"//Mesh class
#include "BasicX\Mesh\MeshManager.h"//Mesh Singleton

#include "BasicX\Camera\CameraManager.h" //Creates and manages the camera object for the world

/*
 ReleaseAllSingletons
USAGE: Releases all ReEngine Singletons
ARGUMENTS: ---
OUTPUT: ---
*/
namespace BasicX
{
	static void ReleaseAllSingletons(void)
	{
		LightManager::ReleaseInstance();
		MaterialManager::ReleaseInstance();
		TextureManager::ReleaseInstance();
		CameraManager::ReleaseInstance();
		Folder::ReleaseInstance();
		GLSystem::ReleaseInstance();
		ShaderManager::ReleaseInstance();
		SystemSingleton::ReleaseInstance();
		Text::ReleaseInstance();
		MeshManager::ReleaseInstance();
	}
}
#endif //__BASICXFRAMEWORK_H_