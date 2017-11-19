/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
Modified: 2016/05
----------------------------------------------*/
#ifndef __MATERIALCLASS_H_
#define __MATERIALCLASS_H_

#include "BasicX\System\SystemSingleton.h"
#include "BasicX\materials\TextureManager.h"

namespace BasicX
{

class BasicXDLL Material
{
	String m_sName = "NULL";

	SystemSingleton* m_pSystem = nullptr;
	TextureManager* m_pTextureMngr = nullptr;

	GLuint m_nMapDiffuse = 0;
	GLuint m_nMapNormal = 0;
	GLuint m_nMapSpecular = 0;

	vector3 m_vKd;

	String m_sMapDiffuse = "NULL";
	String m_sMapNormal = "NULL";
	String m_sMapSpecular = "NULL";
	
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	Material(String a_sName);
	/*
	USAGE: Copy constructor
	ARGUMENTS: other instance to copy from
	OUTPUT:
	*/
	Material(const Material& other);
	/*
	USAGE: copy assignment operator
	ARGUMENTS: other isntance to copy from
	OUTPUT:
	*/
	Material& operator=(const Material& other);
	/*
	USAGE: destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Material(void);
	
	/*
	USAGE: Releases the allocated memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	USAGE: Sets the name of the material
	ARGUMENTS:
		String a_sName -> name of the material
	OUTPUT: ---
	*/
	void SetName(String a_sName);
	
	/*
	USAGE: Gets the name of the material
	ARGUMENTS: ---
	OUTPUT: Material name
	*/
	String	GetName(void);

	/*
	USAGE: Sets the Diffuse Map file name
	ARGUMENTS:
		String a_sFileName -> sets the filename of the diffuse map
	OUTPUT: ---
	*/
	void SetDiffuseMapName(String a_sFileName);
	/*
	USAGE: Sets the OpenGL buffer identifier directly on to the material
	ARGUMENTS:
	GLuint a_uID -> OpenGL Buffer identifier
	OUTPUT: ---
	*/
	void SetDiffuseMapID(GLuint a_uID);

	/*
	USAGE: Gets the diffuse map file name
	ARGUMENTS: ---
	OUTPUT: filename
	*/
	String	GetDiffuseMapName(void);

	/*
	USAGE: Sets the Normal Map file name
	ARGUMENTS:
	String a_sFileName -> sets the filename of the diffuse map
	OUTPUT: ---
	*/
	void SetNormalMapName(String a_sFileName);

	/*
	USAGE: Sets the OpenGL buffer identifier directly on to the material
	ARGUMENTS:
	GLuint a_uID -> OpenGL Buffer identifier
	OUTPUT: ---
	*/
	void SetNormalMapID(GLuint a_uID);
	
	/*
	USAGE: Gets the normal map file name
	ARGUMENTS: ---
	OUTPUT: filename
	*/
	String	GetNormalMapName(void);

	/*
	USAGE: Sets the Specular Map file name
	ARGUMENTS:
	String a_sFileName -> sets the filename of the diffuse map
	OUTPUT: ---
	*/
	void SetSpecularMapName(String a_sFileName);

	/*
	USAGE: Sets the OpenGL buffer identifier directly on to the material
	ARGUMENTS:
	GLuint a_uID -> OpenGL Buffer identifier
	OUTPUT: ---
	*/
	void SetSpecularMapID(GLuint a_uID);
	
	/*
	USAGE: Gets the specular map file name
	ARGUMENTS: ---
	OUTPUT: filename
	*/
	String	GetSpecularMapName(void);

	/*
	USAGE: Get the OpenGL index of the Diffuse Map texture resource
	ARGUMENTS: ---
	OUTPUT: OpenGL index
	*/
	GLuint	GetDiffuseMap(void);

	/*
	USAGE: Get the OpenGL index of the Normal Map texture resource
	ARGUMENTS: ---
	OUTPUT: OpenGL index
	*/
	GLuint	GetNormalMap(void);

	/*
	USAGE: Get the OpenGL index of the Specular Map texture resource
	ARGUMENTS: ---
	OUTPUT: OpenGL index
	*/
	GLuint	GetSpecularMap(void);

	/*
	USAGE: Sets the Diffuse color through a vector3
	ARGUMENTS:
		vector3 a_Kd -> color
	OUTPUT: ---
	*/
	void SetDiffuse(vector3 a_Kd);
	
	/*
	USAGE: Gets the Diffuse vector3 color
	ARGUMENTS: ---
	OUTPUT: Diffuse color vector
	*/vector3 GetDiffuse(void);

	/*
	USAGE: Loads the Diffuse map texture into memory,
		this behaves like SetDiffuseMapName but will also create the OpenGL resources.
		OpenGL will not load resources outside of the main thread, so you need to be
		sure that you are running this from it, its always safer to set the texture
		name and then LoadMaps().
	ARGUMENTS:
		String a_sFileName -> sets the filename of the diffuse map
	OUTPUT: Success flags
	*/
	BTO_OUTPUT LoadDiffuse(String a_sFileName);

	/*
	USAGE: Loads the Normal map texture into memory,
		this behaves like SetNormalMapName but will also create the OpenGL resources.
		OpenGL will not load resources outside of the main thread, so you need to be
		sure that you are running this from it, its always safer to set the texture
		name and then LoadMaps().
	ARGUMENTS:
		String a_sFileName -> sets the filename of the diffuse map
	OUTPUT: Success flags
	*/
	BTO_OUTPUT LoadNormal(String a_sFileName);

	/*
	USAGE: Loads the Specular map texture into memory,
		this behaves like SetSpecularMapName but will also create the OpenGL resources.
		OpenGL will not load resources outside of the main thread, so you need to be
		sure that you are running this from it, its always safer to set the texture
		name and then LoadMaps().
	ARGUMENTS:
		String a_sFileName -> sets the filename of the diffuse map
	OUTPUT: Success flags
	*/
	BTO_OUTPUT LoadSpecular(String a_sFilename);

	/*
	USAGE: Loads the Diffuse, Normal and Specular maps of the file into memory
		(Allocates and binds the OpenGL Resources)
	ARGUMENTS: ---
	OUTPUT: Success flags
	*/
	BTO_OUTPUT LoadMaps(void);

private:
	/*
	USAGE: Initializes the variables of the class
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

}
#endif //_EMPTY_H