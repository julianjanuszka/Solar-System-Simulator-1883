/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
----------------------------------------------*/
#ifndef __IMGUIOBJECT_H_
#define __IMGUIOBJECT_H_

// #define USINGSIMPLEX

#ifdef USINGSIMPLEX
//"Using namespace" to use all the classes in the dll
#include "Simplex\SimplexApplication.h"
using namespace Simplex; //Using namespace to use all the classes in the dll
#else
#include "BasicX\BasicXApplication.h"
using namespace BasicX; //Using namespace to use all the classes in the dll
#endif

#include "imgui\imgui.h"

struct ImGuiObject
{
	ImGuiIO& io = ImGui::GetIO(); //IO from ImGui

	int m_nShader = 0; //Shader handler
	int m_nTex = 0; //Text
	int m_nProjMtx = 0; //Projection Matrix
	uint m_uVBO = 0; //Vertex Buffered Object
	uint m_uVAO = 0; //Vertex Array Object
	uint m_uElements = 0; //elements handle

	int m_nVertHandle = 0; //Vertex Shader
	int m_nFragHandle = 0; //Fragment Shader

	int m_nPosition = 0; //Attribute location for position
	int m_nUV = 0; //Attribute location for UV
	int m_nColor = 0; //Attribute location for color

	uint m_nClock; //Clock to use for the gui
	double m_dTimeTotal = 0.0f; //Time
	bool m_bMousePressed[3] = { false, false, false }; //flags for mouse
	GLuint m_uFontTexture = 0; //Font texture
};

#endif //__IMGUIOBJECT_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/