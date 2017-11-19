#include "BasicX\materials\Texture.h"
using namespace BasicX;

Texture::Texture(void) { Init(); }
Texture::Texture(const Texture& other) { }
Texture& Texture::operator=(const Texture& other) { return *this; }
Texture::~Texture(void) { Release(); }

void Texture::Release(void)
{
	glDeleteTextures(1, &m_nTextureID);
}
void Texture::Init(void)
{
	m_nTextureID = 0;
	m_pSystem = SystemSingleton::GetInstance();
	m_sAbsoluteRoute = "";
}
bool Texture::LoadTexture(String a_sFileName)
{
	if (a_sFileName == "NULL")
		return false;

	String sRoute = FileReader::GetAbsoluteRoute(a_sFileName);
	if (sRoute != a_sFileName)
	{
		m_sName = FileReader::GetFileNameAndExtension(a_sFileName);
		m_sAbsoluteRoute = sRoute;
		m_sFileName = a_sFileName;
	}
	else
	{
		m_sName = a_sFileName;
		m_sFileName = m_pSystem->m_pFolder->GetFolderRoot();
		m_sFileName += m_pSystem->m_pFolder->GetFolderData();
		m_sFileName += m_pSystem->m_pFolder->GetFolderTextures();
		m_sAbsoluteRoute = m_sFileName;
		m_sFileName += m_sName;
	}
	// Check for file existence
	if (!FileReader::FileExists(m_sFileName))
		return false;

	//Based on Raul's implementation: http://www.raul-art.blogspot.com
	FREE_IMAGE_FORMAT eFormat = FreeImage_GetFileType(m_sFileName.c_str(), 0);//Detect the file format
	FIBITMAP* image = FreeImage_Load(eFormat, m_sFileName.c_str()); //Load the file as FreeImage imagefile
	image = FreeImage_ConvertTo32Bits(image); //convert to 32bits

	int w = FreeImage_GetWidth(image);
	int h = FreeImage_GetHeight(image);
#ifdef DEBUG
	std::cout << "Texture loaded " << m_sFileName.c_str() << std::endl; //Some debugging code
	std::cout << "               With size [ " << w << " * " << h << "]" << std::endl;
#endif
	GLubyte* tempGLTexture = new GLubyte[4 * w * h];//Create a new texture to hold the information onto
	char* pixeles = (char*)FreeImage_GetBits(image);//Create a pixel container
							 //FreeImage loads in BGRA format, so you need to swap some bytes (Or use GL_BGR).
	for (int nPixel = 0; nPixel < (w * h); nPixel++)
	{
		tempGLTexture[nPixel * 4 + 0] = pixeles[nPixel * 4 + 2];
		tempGLTexture[nPixel * 4 + 1] = pixeles[nPixel * 4 + 1];
		tempGLTexture[nPixel * 4 + 2] = pixeles[nPixel * 4 + 0];
		tempGLTexture[nPixel * 4 + 3] = pixeles[nPixel * 4 + 3];
	}
	FreeImage_Unload(image); //OUT_DONE with the image, unload it

	if(m_nTextureID > 0)// if the texture is already binded
	{
		glDeleteTextures(1, &m_nTextureID);
/*#if _MSC_VER == 1800 //If visual studio 2013
		 /*m_nTextureID = SOIL_load_OGL_texture
		(
			m_sFileName.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y 
		);
#elif _MSC_VER == 1900 //If visual studio 2015
		
		
//#endif*/
	}
	//else
	//{
	//	m_nTextureID = SOIL_load_OGL_texture
	//	(
	//		m_sFileName.c_str(),
	//		SOIL_LOAD_AUTO,
	//		m_nTextureID,
	//		SOIL_FLAG_INVERT_Y
	//	);
	//}

	//Now generate the OpenGL texture object 
	glGenTextures(1, &m_nTextureID); //Generate a container
	glBindTexture(GL_TEXTURE_2D, m_nTextureID); //Set the active texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)tempGLTexture); //Set the data
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	if (glGetError())
	{
		std::cout << "There was an error loading the texture" << std::endl;
		return false;
	}
	return true;
}

//Accessors
GLuint Texture::GetGLTextureID(void){return m_nTextureID;}
String Texture::GetName(void){return m_sName;}
String Texture::GetFileName(void){return m_sFileName;}
String Texture::GetAbsoluteRoute(void) { return m_sAbsoluteRoute; }
