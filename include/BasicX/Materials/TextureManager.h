/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __TEXTUREMANAGERSINGLETON_H_
#define __TEXTUREMANAGERSINGLETON_H_

#include "BasicX\materials\Texture.h"
#include <vector>
#include <map>

namespace BasicX
{

class BasicXDLL TextureManager
{
	std::map<String,int> m_map;//indexer

public:
	std::vector<Texture*> m_textureList; //Vector of Textures

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static TextureManager* GetInstance(); //Singleton Accessor
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	static void ReleaseInstance();	//Singleton Destructor
	
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyTexure(String sName); //Returns the ID number of the texture, -1 if it does not exist.
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int LoadTexture(String sName);	//Loads a texture and returns the ID of where its stored in the vector

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	void SaveTexture(String a_sTextureName = "ScreenShot");
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetTextureCount(void); //Returns the number of texures in the vector
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GLuint ReturnGLIndex(uint a_nIndex); //Returns the OpenGL Buffer ID in the vector location of the provided Index
private:
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static TextureManager* m_pInstance; //Singleton
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	TextureManager(void); //Constructor	
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	TextureManager(const TextureManager& other); //Copy Constructor
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	TextureManager& operator=(const TextureManager& other);//Copy Assignment Operator
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~TextureManager(void); //Destructor

	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void); //Release the fields in the class
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void); //Initialize variables
};

}
#endif __TEXTUREMANAGERSINGLETON_H_