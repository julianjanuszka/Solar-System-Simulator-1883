/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __TEXTURECLASS_H_
#define __TEXTURECLASS_H_

#include "Simplex\System\SystemSingleton.h"
#include "Simplex\system\FileReader.h"
#include "FreeImage\FreeImage.h"

namespace Simplex
{

class SimplexDLL Texture
{
	GLuint m_nTextureID = 0;
	SystemSingleton* m_pSystem = nullptr;
	String m_sName = "NULL";
	String m_sFileName = "NULL";
	String m_sAbsoluteRoute = "";

public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	Texture(void); //Constructor
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Texture(const Texture& other); //Copy Constructor
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Texture& operator=(const Texture& other); //Copy Assignment Operator
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
	~Texture(void); //Destructor

	/*
	USAGE: Loads the specified file onto this texture
	ARGUMENTS:
		String a_sFileName -> name of the file, if path not define will look
		under the textures folder
	OUTPUT: success
	*/
	bool LoadTexture(String a_sFileName);
//Accessors
	/*
	USAGE: Returns the OpenGL Identifier
	ARGUMENTS: ---
	OUTPUT:
	*/
	GLuint GetGLTextureID(void);

	//__declspec(property(get = GetGLTextureID)) GLuint GLTextureID;
	/*
	USAGE: Returns the name of the texture
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetName(void);
	//__declspec(property(get = GetTextureName)) String TextureName;
	/*
	USAGE: Returns the filename of the texture
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFileName(void);
	//__declspec(property(get = GetTextureFileName)) String TextureFileName;
	/*
	USAGE: Returns the file folder of the texture
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetAbsoluteRoute(void);

private:
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void); //Initializes the variables
};

EXPIMP_TEMPLATE template class SimplexDLL std::vector<Texture>;
EXPIMP_TEMPLATE template class SimplexDLL std::vector<Texture*>;

} //namespace Simplex

#endif //_TEXTURECLASS_H

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/