/*----------------------------------------------
Adapted from http://www.swiftless.com/tutorials/opengl4/1-opengl-window.html
into a class Date: 2015/06
Modified: 2017/06
----------------------------------------------*/

#ifndef __GLSystemSingleton_H_
#define __GLSystemSingleton_H_

#include "Simplex\system\Window.h"

#include <GL\glew.h>
#include <GL\wglew.h>

namespace Simplex
{

//GLSystem singleton
class SimplexDLL GLSystem
{
	//--Members
	HDC   m_hDC = NULL;			// Private GDI Device Context
	float m_fGLVersion = 0.0f;	// OpenGL version

public:
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	HRESULT InitGLDevice(HWND g_hWnd);
	/*
	USAGE: Generates a new render target and return the identifier
	ARGUMENTS:
	OUTPUT:
	*/
	bool GenerateRenderTarget(GLuint& a_nFrameBuffer, GLuint& a_nDepthBuffer, GLuint& a_nTextureIndex);
	/*
	USAGE: Generates a new render target and return the identifier
	ARGUMENTS:
	OUTPUT:
	*/
	bool UpdateRenderTarget(GLuint& a_nFrameBuffer, GLuint& a_nDepthBuffer, GLuint& a_nTextureIndex, int a_nWidth = -1, int a_nHeight = -1);
	/*
	USAGE: Singleton Accessor, returns the singleton of this class
	ARGUMENTS: ---
	OUTPUT:
	*/
	static GLSystem* GetInstance(void);
	/*
	USAGE: Releases the singleton of this class
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/*
	USAGE: Returns the OpenGL rendering context device
	ARGUMENTS: ---
	OUTPUT:
	*/
	HDC GetDeviceContext(GLvoid);
	/*
	USAGE: Returns the OpenGL Version the program is using
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetGLVersion(void);
	/*
	USAGE: SwapsvOpenGL buffer
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void GLSwapBuffers(void);

private:
	//--Methods
	/*
	USAGE:Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLSystem(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	GLSystem(GLSystem const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	GLSystem& operator=(GLSystem const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~GLSystem(void);
	/*
	USAGE: Release Memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Initialize variables
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	
	static GLSystem* m_pInstance; // Singleton
};

} //namespace Simplex

#include "ShaderCompiler.h"

#endif /*__GLSystemSingleton_H__*/
  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */