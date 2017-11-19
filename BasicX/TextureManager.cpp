#include "BasicX\materials\TextureManager.h"
using namespace BasicX;
TextureManager* TextureManager::m_pInstance = nullptr;
TextureManager* TextureManager::GetInstance(void)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new TextureManager();
	}
	return m_pInstance;
}
TextureManager::TextureManager(void) { Init(); }
TextureManager::TextureManager(const TextureManager& other) { }
TextureManager& TextureManager::operator=(const TextureManager& other) { return *this; }
TextureManager::~TextureManager(void) { Release(); }
void TextureManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//--- Non Standard Singleton Methods
void TextureManager::Release(void)
{
	int nTextures = static_cast<int>(m_textureList.size());
	for(int nTexture = 0; nTexture < nTextures; nTexture++)
	{
		Texture* mTemp = m_textureList[nTexture];
		if(mTemp != nullptr)
		{
			delete mTemp;
			mTemp = nullptr;
		}
	}
}
void TextureManager::Init(void) { }
int TextureManager::IdentifyTexure(String a_sName)
{
	String sAbsoluteRoute = FileReader::GetAbsoluteRoute(a_sName);
	bool bHasRoute = (sAbsoluteRoute != a_sName);
	if (!bHasRoute)
	{
		SystemSingleton* pSystem = SystemSingleton::GetInstance();
		String sName = pSystem->m_pFolder->GetFolderRoot();
		sName += pSystem->m_pFolder->GetFolderData();
		sName += pSystem->m_pFolder->GetFolderTextures();
		a_sName = sName + a_sName;
	}

	auto var = m_map.find(a_sName);
	if(var != m_map.end())
		return var->second;
	return -1;
}
int TextureManager::LoadTexture(String a_sName)
{
	if ("NULL" == a_sName || " " == a_sName || "null" == a_sName || "Null" == a_sName)
		return -1;
	int nTexture = IdentifyTexure(a_sName);
	if(nTexture == -1)
	{
		Texture* pTextureTemp = new Texture();
		if (pTextureTemp->LoadTexture(a_sName))
		{
			m_textureList.push_back(pTextureTemp);
			nTexture = GetTextureCount() - 1;
			m_map[pTextureTemp->GetFileName()] = nTexture;
		}
		else
		{
			if (pTextureTemp)
			{
				delete pTextureTemp;
				pTextureTemp = nullptr;
			}
			return -1;
		}
	}
	return nTexture;
}
void TextureManager::SaveTexture(String a_sTextureName)
{
	//working on this still, weird tint in the texture.
	////Texture to render to
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, n_GLTextureID);

	//http://stackoverflow.com/questions/5844858/how-to-take-screenshot-in-opengl

	// Make the BYTE array, factor of 3 because it's RBG.
	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	GLubyte* pixels = new GLubyte[4 * pSystem->GetWindowWidth() * pSystem->GetWindowHeight()];
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(0, 0, pSystem->GetWindowWidth(), pSystem->GetWindowHeight(), GL_BGRA, GL_UNSIGNED_BYTE, pixels);

	// Convert to FreeImage format & save to file
	FIBITMAP* image = FreeImage_ConvertFromRawBits(
		pixels,
		pSystem->GetWindowWidth(),
		pSystem->GetWindowHeight(),
		4 * pSystem->GetWindowWidth(),
		32, 0xFF0000, 0x00FF00, 0x0000FF, false);
	a_sTextureName = a_sTextureName + ".png";
	FreeImage_Save(FIF_PNG, image, a_sTextureName.c_str(), 0);

	// Free resources
	FreeImage_Unload(image);
	delete[] pixels;
}
//Accessors
int TextureManager::GetTextureCount(void){return static_cast<int> (m_textureList.size());}
GLuint TextureManager::ReturnGLIndex(uint a_nIndex)
{
	//if index is out of bounds return unbound
	if (a_nIndex >= m_textureList.size())
		return 0;
	//return the texture id
	return m_textureList[a_nIndex]->GetGLTextureID();
};