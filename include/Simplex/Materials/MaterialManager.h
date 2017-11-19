/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
Modified: 2017/06
----------------------------------------------*/
#ifndef __MATERIALMANAGERSINGLETON_H_
#define __MATERIALMANAGERSINGLETON_H_

#include "Simplex\System\SystemSingleton.h"
#include "Simplex\materials\Material.h"
#include <map>


namespace Simplex
{

//MaterialManager singleton
class SimplexDLL MaterialManager
{
	/* 
		The material vector is public for accessing speed reasons its more secure to have it as private
		and provide the right accessors for it
	*/
	std::map<String,int> m_map; //Map of the materials
	SystemSingleton* m_pSystem; //System class Pointer
	static MaterialManager* m_pInstance; // Singleton Pointer

public:
	std::vector<Material*> m_materialList; //Materials Vector
	

	/*
	USAGE: Singleton Accessor
	ARGUMENTS:
	OUTPUT:
	*/
	static MaterialManager* GetInstance();
	
	/*
	USAGE: Singleton Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);

	/*
	USAGE: Identifies the material, if found return its index -1 otherwise
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyMaterial(String a_sName);

	/*
	USAGE: returns the index number of the material if it created a new one, otherwise it returns the index
	ARGUMENTS:
	OUTPUT:
	*/
	int AddMaterial(String a_sName);
	
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int AddMaterial(Material a_InputMaterial);

	/*
	USAGE: Adds a new material, if the name exists already in the pile it returns that material ID with no
	changes
	ARGUMENTS:
	OUTPUT:
	*/
	int AddMaterial(String a_sName, String a_sDiffuse, String a_sNormal = "", String a_sSpecular = "");

	/*
	USAGE: Return the number of materials in the vector
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetMaterialCount(void);

	/*
	USAGE: Tries to load all the textures for all of the materials
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ReloadMaps(void);

	/*
	USAGE: Gets a copy of the material specified by name
	ARGUMENTS:
	OUTPUT:
	*/
	Material GetMaterialCopy(String a_sName);

	/*
	USAGE: Returns the memory location containing the material specified by the name
	ARGUMENTS:
	OUTPUT:
	*/
	Material* GetMaterial(String a_sName);

	/*
	USAGE: Returns the memory location containing the material specified by the index
	ARGUMENTS:
	OUTPUT:
	*/
	Material* GetMaterial(uint a_nIndex);

	/*
	USAGE: Sets the Diffuse map name of the specified material
	ARGUMENTS:
		String a_sFileName -> name of the texture file "File.png"
		int a_nIndex = -1 -> index of the material to modify, -1 for last added material
	OUTPUT:
	*/
	void SetDiffuseMapName(String a_sFileName, int a_nIndex = -1);
	
	/*
	USAGE: Sets the Normal map name of the specified material
	ARGUMENTS:
		String a_sFileName -> name of the texture file "File.png"
		int a_nIndex = -1 -> index of the material to modify, -1 for last added material
	OUTPUT:
	*/
	void SetNormalMapName(String a_sFileName, int a_nIndex = -1);

	/*
	USAGE: Sets the Specular map name of the specified material
	ARGUMENTS:
	String a_sFileName -> name of the texture file "File.png"
	int a_nIndex = -1 -> index of the material to modify, -1 for last added material
	OUTPUT:
	*/
	void SetSpecularMapName(String a_sFileName, int a_nIndex = -1);
	
	/*
	USAGE: Gets the OpenGL textureID of the material under a_nIndex
	ARGUMENTS:
		uint a_nIndex -> Index of the material
	OUTPUT:
		GLuint -> Inquired index
	*/
	GLuint GetDiffuseMap(uint a_nIndex);

	/*
	USAGE: Gets the OpenGL textureID of the material under a_nIndex
	ARGUMENTS:
		uint a_nIndex -> Index of the material
	OUTPUT:
		GLuint -> Inquired index
	*/
	GLuint GetNormalMap(uint a_nIndex);

	/*
	USAGE: Gets the OpenGL textureID of the material under a_nIndex
	ARGUMENTS:
		uint a_nIndex -> Index of the material
	OUTPUT:
		GLuint -> Inquired index
	*/
	GLuint GetSpecularMap(uint a_nIndex);

	/*
	USAGE: Gets the Diffuse map name of the specified material
	ARGUMENTS:
		int a_nIndex = -1 -> index of the material to modify, -1 for last added material
	OUTPUT: name of the diffuse map of the specified material
	*/
	String GetDiffuseMapName(int a_nIndex = -1);

	/*
	USAGE: Gets the Diffuse map name of the specified material
	ARGUMENTS:
	int a_nIndex = -1 -> index of the material to modify, -1 for last added material
	OUTPUT: name of the diffuse map of the specified material
	*/
	String GetNormalMapName(int a_nIndex = -1);

	/*
	USAGE: Gets the Diffuse map name of the specified material
	ARGUMENTS:
	int a_nIndex = -1 -> index of the material to modify, -1 for last added material
	OUTPUT: name of the diffuse map of the specified material
	*/
	String GetSpecularMapName(int a_nIndex = -1);

	/*
	USAGE: Duplicates the material specified my name and adds it to the vector of materials
	ARGUMENTS:
		String a_sMaterialToDuplicate -> name of material to duplicate
		String a_sDesiredName -> name of material
	OUTPUT: index of the new material
	*/
	int DuplicateMaterial(String a_sMaterialToDuplicate, String a_sDesiredName);

private:
	
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	MaterialManager(void);

	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	MaterialManager(MaterialManager const& other);
	
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	MaterialManager& operator=(MaterialManager const& other);
	
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MaterialManager(void);

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
};

} //namespace Simplex

#endif //_MATERIALMANAGERSINGLETON_H
  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */