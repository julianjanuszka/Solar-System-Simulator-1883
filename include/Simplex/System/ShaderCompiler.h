/*----------------------------------------------
From: http://www.opengl-tutorial.org/
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/

#ifndef __SHADERCOMPILER_H_
#define __SHADERCOMPILER_H_

#include <GL\glew.h>
#include <GL\wglew.h>
#include "Simplex\system\Definitions.h" //ReEng basic Definitions

/*
USAGE: Will load the specified files as vertex and fragment shaders
ARGUMENTS:
-	const char * vertex_file_path -> vertex shader file
-	const char * fragment_file_path -> fragment shader file
OUTPUT: opengl identifier of the loaded shader (0 if error)
*/
namespace Simplex
{

SimplexDLL GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

} //namespace Simplex

#endif //__SHADER_H__
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
