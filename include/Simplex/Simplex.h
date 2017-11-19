/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/04
Update: 2017/07
----------------------------------------------*/
#ifndef __SIMPLEXFRAMEWORK_H_
#define __SIMPLEXFRAMEWORK_H_

#pragma warning( disable : 4251 )

#include "Simplex\system\Definitions.h" //ReEng basic Definitions
#include "Simplex\System\SystemSingleton.h" //System related methods

#include "Simplex\system\Window.h" //WinAPI encapsulated methods
#include "Simplex\system\FileReader.h" //Reads an object and returns lines as strings
#include "Simplex\system\Folder.h" //Sets the working directory
#include "Simplex\system\GLSystem.h" //OpenGL 3.X initialization

#include "Simplex\system\ShaderManager.h" //Shader Manager, loads and manages different shader files
#include "Simplex\system\ShaderCompiler.h" //Compiles the shader objects

#include "Simplex\light\LightManager.h" //Manages the light sources of the world

#include "Simplex\materials\MaterialManager.h" //Manages the materials
#include "Simplex\materials\TextureManager.h" //Manages the Textures, loads, display and release

#include "Simplex\Animation\Animation.h" //Manages the animations in a model
#include "Simplex\Animation\Frame.h" //Manages the transformations of a model in a frame of time
#include "Simplex\Animation\Sequence.h" //Manages the starting and ending point of an animation
#include "Simplex\Animation\State.h" //Manages the current state of the model

#include "Simplex\Mesh\Text.h" //Singleton for drawing Text on the screen
#include "Simplex\Mesh\Mesh.h"//Mesh class
#include "Simplex\Mesh\MeshManager.h"//Mesh Singleton
#include "Simplex\Mesh\Group.h"//Group class
#include "Simplex\Mesh\Model.h"//Model Class

#include "Simplex\Physics\RigidBody.h"//RigidBody Class

#include "Simplex\Physics\Entity.h"//Entity Class
#include "Simplex\Physics\EntityManager.h"//Entity Manager Singleton

#include "Simplex\Camera\CameraManager.h" //Creates and manages the camera object for the world

#include "Simplex\Physics\Octant.h" //Octant for Octree

namespace Simplex
{
/*
USAGE: Releases all ReEngine Singletons
ARGUMENTS: ---
OUTPUT: ---
*/
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
	EntityManager::ReleaseInstance();
};

} //namespace Simplex

#endif //__SIMPLEXFRAMEWORK_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */