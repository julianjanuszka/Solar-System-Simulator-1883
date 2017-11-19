/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
Modified: 2017/06
----------------------------------------------*/
#ifndef __TEXTSYSTEM_H_
#define __TEXTSYSTEM_H_

#include "Simplex\System\SystemSingleton.h"
#include "Simplex\System\ShaderManager.h"
#include "Simplex\Materials\MaterialManager.h"

namespace Simplex
{

//Text Class
class SimplexDLL Text
{
protected:
	bool m_bBinded = false; //Binded flag

	uint m_uMaterialIndex = 0; //Material index of this mesh
	uint m_uVertexCount = 0; //Number of vertices in this Mesh

	GLuint m_vao = 0;	//OpenGL Vertex Array Object
	GLuint m_VBO = 0;	//OpenGL Buffer (Will hold the vertex buffer pointer)
	GLuint m_nShader = 0;	//Index of the shader

	ShaderManager* m_pShaderMngr = nullptr;	//Shader Manager
	MaterialManager* m_pMatMngr = nullptr;		//Material Manager
		
	std::vector<vector3> m_lVertex; //List of vertices

	std::vector<vector3> m_lVertexPos;	//List of Vertices
	std::vector<vector3> m_lVertexCol;	//List of Colors
	std::vector<vector3> m_lVertexUV;	//List of UVS

	vector3 m_v3Head = ZERO_V3;

	static Text* m_pInstance; // Singleton pointer
	SystemSingleton* m_pSystem = nullptr;

	String m_sText = "";
	String m_sTextPrev = "";
	String m_sFont;
	std::vector<vector3> m_lColor;
	std::vector<vector3> m_lColorPrev;

public:
	/*
	USAGE: Gets/Constructs the singleton pointer
	ARGUMENTS:
	OUTPUT:
	*/
	static Text* GetInstance();
	/*
	USAGE: Destroys the singleton
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/*
	USAGE: Compiles the Mesh for OpenGL 3.X use
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompileOpenGL3X(void);
		
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Render(void);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddString(String a_sString, vector3 a_v3Color = C_WHITE);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFont(String a_sTextureName);

protected:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	Text(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	Text(Text const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	Text& operator=(Text const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Text(void);
	/*
	USAGE: Initialize the object's fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Releases the object from memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Reset(void);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCharacter(char a_cInput, vector3 a_v3Color = C_WHITE);
};

} //namespace Simplex

#endif //__TEXTSINGLETON_H_
  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */