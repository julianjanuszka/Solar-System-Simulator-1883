#include "BasicX\materials\Material.h"
using namespace BasicX;

Material::Material(String a_sName): m_sName(a_sName) { Init(); }
Material::Material(const Material& other)
{
	m_sName = other.m_sName;
	m_nMapDiffuse = other.m_nMapDiffuse;
	m_nMapNormal = other.m_nMapNormal;
	m_nMapSpecular = other.m_nMapSpecular;
	m_sMapDiffuse = other.m_sMapDiffuse;
	m_sMapNormal = other.m_sMapNormal;
	m_sMapSpecular = other.m_sMapSpecular;

	m_vKd = other.m_vKd;

	m_pSystem = other.m_pSystem;
	m_pTextureMngr = other.m_pTextureMngr;
}
Material& Material::operator=(const Material& other)
{
	if(this != &other)
	{
		Release();
		m_sName = other.m_sName;
		m_nMapDiffuse = other.m_nMapDiffuse;
		m_nMapNormal = other.m_nMapNormal;
		m_nMapSpecular = other.m_nMapSpecular;
		m_sMapDiffuse = other.m_sMapDiffuse;
		m_sMapNormal = other.m_sMapNormal;
		m_sMapSpecular = other.m_sMapSpecular;

		m_vKd = other.m_vKd;

		m_pSystem = other.m_pSystem;
		m_pTextureMngr = other.m_pTextureMngr;
	}
	return *this;
}
Material::~Material(void) { Release(); }
	
void Material::Release(void)
{
	m_pSystem = nullptr;
	m_pTextureMngr = nullptr;
}
void Material::Init(void)
{
	m_pSystem = SystemSingleton::GetInstance();
	m_pTextureMngr = TextureManager::GetInstance();
	m_nMapDiffuse = -1;
	m_nMapNormal = -1;
	m_nMapSpecular = -1;
	m_sMapDiffuse = "NULL";
	m_sMapNormal = "NULL";
	m_sMapSpecular = "NULL";
	m_vKd = vector3( 0.5f, 0.5f, 0.5f);
}
void Material::SetName(String a_sName) { m_sName = a_sName; }
String Material::GetName(void) { return m_sName; }

//Diffuse
GLuint Material::GetDiffuseMap(void) {	return m_nMapDiffuse; }
void Material::SetDiffuseMapID(GLuint a_uID) { m_nMapDiffuse = a_uID; }

void Material::SetDiffuseMapName(String a_sFileName) { m_sMapDiffuse = a_sFileName; m_vKd = vector3(1, 0, 1); }
String Material::GetDiffuseMapName(void) {	return m_sMapDiffuse; }

vector3 Material::GetDiffuse(void) { return m_vKd; }
void Material::SetDiffuse(vector3 a_Kd) { m_vKd = a_Kd; }

//Normal
GLuint Material::GetNormalMap(void) { return m_nMapNormal; }
void Material::SetNormalMapName(String a_sFileName) { m_sMapNormal = a_sFileName; }
String Material::GetNormalMapName(void) { return m_sMapNormal; }
void Material::SetNormalMapID(GLuint a_uID) { m_nMapNormal = a_uID; }

//Specular
GLuint Material::GetSpecularMap(void) { return m_nMapSpecular; }
void Material::SetSpecularMapName(String a_sFileName) { m_sMapSpecular = a_sFileName; }
String Material::GetSpecularMapName(void) { return m_sMapSpecular; }
void Material::SetSpecularMapID(GLuint a_uID) { m_nMapSpecular = a_uID; }


BTO_OUTPUT Material::LoadDiffuse(String a_sFileName)
{
	m_sMapDiffuse = a_sFileName;

	m_nMapDiffuse = m_pTextureMngr->ReturnGLIndex(
			m_pTextureMngr->LoadTexture(a_sFileName));
	if(m_nMapDiffuse == -1)
		return OUT_ERR_FILE_MISSING;

	return OUT_ERR_NONE;
}
BTO_OUTPUT Material::LoadNormal(String a_sFileName)
{
	m_sMapNormal = a_sFileName;

	m_nMapNormal = m_pTextureMngr->ReturnGLIndex(
			m_pTextureMngr->LoadTexture(a_sFileName));
	if(m_nMapNormal == -1)
		return OUT_ERR_FILE_MISSING;

	return OUT_ERR_NONE;
}
BTO_OUTPUT Material::LoadSpecular(String a_sFileName)
{
	m_sMapSpecular = a_sFileName;

	m_nMapSpecular = m_pTextureMngr->ReturnGLIndex(
			m_pTextureMngr->LoadTexture(a_sFileName));
	if(m_nMapSpecular == -1)
		return OUT_ERR_FILE_MISSING;

	return OUT_ERR_NONE;
}
BTO_OUTPUT Material::LoadMaps()
{
	//find the absolute route of the m_sName
	String sAbsoluteRoute = CopyAfterToken(m_sName, '|');
	sAbsoluteRoute = FileReader::GetAbsoluteRoute(sAbsoluteRoute);
	bool bHasRoute = (sAbsoluteRoute == m_sName);
	//Load Diffuse
	int nDiffuse;
	if (!bHasRoute) //if the route was specified we try to load from there
	{
		// try the same folder
		nDiffuse = m_pTextureMngr->LoadTexture(sAbsoluteRoute + m_sMapDiffuse);
		// if not try different folders at the same level as model
		if (nDiffuse < 0)
			nDiffuse = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Textures\\" + m_sMapDiffuse);
		if (nDiffuse < 0)
			nDiffuse = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Texture\\" + m_sMapDiffuse);
		if (nDiffuse < 0)
			nDiffuse = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Material\\" + m_sMapDiffuse);
		if (nDiffuse < 0)
			nDiffuse = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Materials\\" + m_sMapDiffuse);
		if (nDiffuse < 0) //try the fbx subfolder
		{
			String sModel = FileReader::GetFileName(m_sName);
			nDiffuse = m_pTextureMngr->LoadTexture(sAbsoluteRoute + sModel + ".fbm\\" + m_sMapDiffuse);
		}
		
		//if we could not find it try it from the default texture folder
		if (nDiffuse < 0)
			nDiffuse = m_pTextureMngr->LoadTexture(m_sMapDiffuse);
	}
	else// if route was not specified we load from the default texture folder
	{
		nDiffuse = m_pTextureMngr->LoadTexture(m_sMapDiffuse);
	}
	//--------------------------------------------------------------------------------
	//Load Normal
	int nNormal;
	if (!bHasRoute) //if the route was specified we try to load from there
	{
		// try the same folder
		nNormal = m_pTextureMngr->LoadTexture(sAbsoluteRoute + m_sMapNormal);
		// if not try different folders at the same level as model
		if (nNormal < 0)
			nNormal = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Textures\\" + m_sMapNormal);
		if (nNormal < 0)
			nNormal = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Texture\\" + m_sMapNormal);
		if (nNormal < 0)
			nNormal = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Material\\" + m_sMapNormal);
		if (nNormal < 0)
			nNormal = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Materials\\" + m_sMapNormal);
		if (nNormal < 0) //try the fbx subfolder
		{
			String sModel = FileReader::GetFileName(m_sName);
			nNormal = m_pTextureMngr->LoadTexture(sAbsoluteRoute + sModel + ".fbm\\" + m_sMapNormal);
		}
		//if we could not find it try it from the default texture folder
		if (nNormal < 0)
			nNormal = m_pTextureMngr->LoadTexture(m_sMapNormal);
	}
	else// if route was not specified we load from the default texture folder
	{
		nNormal = m_pTextureMngr->LoadTexture(m_sMapNormal);
	}
	//--------------------------------------------------------------------------------
	//Load Specular
	int nSpecular;
	if (!bHasRoute) //if the route was specified we try to load from there
	{
		// try the same folder
		nSpecular = m_pTextureMngr->LoadTexture(sAbsoluteRoute + m_sMapSpecular);
		// if not try different folders at the same level as model
		if (nSpecular < 0)
			nSpecular = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Textures\\" + m_sMapSpecular);
		if (nSpecular < 0)
			nSpecular = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Texture\\" + m_sMapSpecular);
		if (nSpecular < 0)
			nSpecular = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Material\\" + m_sMapSpecular);
		if (nSpecular < 0)
			nSpecular = m_pTextureMngr->LoadTexture(sAbsoluteRoute + "Materials\\" + m_sMapSpecular);
		if (nSpecular < 0) //try the fbx subfolder
		{
			String sModel = FileReader::GetFileName(m_sName);
			nSpecular = m_pTextureMngr->LoadTexture(sAbsoluteRoute + sModel + ".fbm\\" + m_sMapSpecular);
		}
		//if we could not find it try it from the default texture folder
		if (nSpecular < 0)
			nSpecular = m_pTextureMngr->LoadTexture(m_sMapSpecular);
	}
	else// if route was not specified we load from the default texture folder
	{
		nSpecular = m_pTextureMngr->LoadTexture(m_sMapSpecular);
	}
	//----------------------------------------------------------------------------------

	//Diffuse
	m_nMapDiffuse = m_pTextureMngr->ReturnGLIndex( nDiffuse	);

	//Normal
	m_nMapNormal = m_pTextureMngr->ReturnGLIndex( nNormal );

	//Specular
	m_nMapSpecular = m_pTextureMngr->ReturnGLIndex( nSpecular );

	if(m_nMapNormal == -1 || m_nMapDiffuse == -1)
		return OUT_ERR_FILE_MISSING;
	
	return OUT_ERR_NONE;
}