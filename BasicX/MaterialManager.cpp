#include "BasicX\materials\MaterialManager.h"
using namespace BasicX;
//  MaterialManager
MaterialManager* MaterialManager::m_pInstance = nullptr;
MaterialManager* MaterialManager::GetInstance(void)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new MaterialManager();
	}
	return m_pInstance;
}
MaterialManager::MaterialManager(void){Init();}
MaterialManager::MaterialManager(MaterialManager const& other){}
MaterialManager& MaterialManager::operator=(MaterialManager const& other) {	return *this; }
MaterialManager::~MaterialManager(void){Release();};
void MaterialManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//--- Non Standard Singleton Methods
void  MaterialManager::Release(void)
{
	int nMaterials = static_cast<int>(m_materialList.size());
	for(int i = 0; i < nMaterials; i++)
	{
		Material* temp = m_materialList[i];
		if(temp)
		{
			delete temp;
			temp = nullptr;
		}
	}
	m_materialList.clear();
	m_pSystem = nullptr;
}
void MaterialManager::Init(void)
{
	m_pSystem = SystemSingleton::GetInstance();
}
int MaterialManager::AddMaterial(Material input)
{
	int nMaterial = IdentifyMaterial(input.GetName());
	if(nMaterial == -1)
	{
		Material* pMaterial = new Material(input);
		m_materialList.push_back(pMaterial);
		nMaterial = m_materialList.size() -1;
		m_map[pMaterial->GetName()] = nMaterial;
	}
	ReloadMaps();
	return nMaterial;
}
int MaterialManager::AddMaterial(String a_sName)
{
	int nMaterials = static_cast<int>(m_materialList.size());
	//Look for the material in the vector of materials, if a match is found return that material's index
	int nMaterial = IdentifyMaterial(a_sName);
	if (nMaterial != -1)
		return nMaterial;

	//if no material was found create a new material and add it to the vector
	Material* pMaterial = new Material(a_sName);
	m_materialList.push_back(pMaterial);
	m_map[pMaterial->GetName()] = static_cast<int>(m_materialList.size() -1);

	//return the newly added material's index
	return m_materialList.size() -1;
}
int MaterialManager::AddMaterial(String a_sName, String a_sDiffuse, String a_sNormal, String a_sSpecular)
{
	int nMaterial = IdentifyMaterial(a_sName);
	if (nMaterial >= 0)
		return nMaterial;
	Material oMaterial(a_sName);
	if (a_sDiffuse != "")
		oMaterial.SetDiffuseMapName(a_sDiffuse);
	if (a_sNormal != "")
		oMaterial.SetDiffuseMapName(a_sNormal);
	if (a_sSpecular != "")
		oMaterial.SetDiffuseMapName(a_sSpecular);
	return AddMaterial(oMaterial);
}
int MaterialManager::IdentifyMaterial(String a_sName)
{
	auto var = m_map.find(a_sName);
	if(var != m_map.end())
		return var->second;
	
	//int nMaterials = GetMaterialCount();
	//for(int i = 0; i < nMaterials; i++)
	//{
	//	if(m_lMaterial[i]->Name == a_sName)
	//	{
	//		return i;
	//	}
	//}
	return -1;
}
int MaterialManager::GetMaterialCount(void)
{
	return static_cast<int>(m_materialList.size());
}
void MaterialManager::ReloadMaps()
{
	int nMaterials = GetMaterialCount();
	for(int i = 0; i < nMaterials; i++)
	{
		m_materialList[i]->LoadMaps();
	}
	return;
}
Material MaterialManager::GetMaterialCopy(String a_sName)
{
	int nIndex = IdentifyMaterial(a_sName);
	Material newMaterial(a_sName);
	if(nIndex >=0)
		newMaterial = *m_materialList[nIndex];
	return newMaterial;
}
Material* MaterialManager::GetMaterial(String a_sName)
{
	int nIndex = IdentifyMaterial(a_sName);
	if (nIndex >= 0)
		return m_materialList[nIndex];
	return nullptr;
}

Material* MaterialManager::GetMaterial(uint a_nIndex)
{
	return m_materialList[a_nIndex];
}

void MaterialManager::SetDiffuseMapName(String a_sFileName, int a_nIndex)
{
	if (a_nIndex < 0)
		a_nIndex = static_cast<int>(m_materialList.size() - 1);

	if (a_nIndex >= 0 && a_nIndex < static_cast<int>(m_materialList.size()))
	{
		m_materialList[a_nIndex]->SetDiffuseMapName(a_sFileName);
	}
}

void MaterialManager::SetNormalMapName(String a_sFileName, int a_nIndex)
{
	if (a_nIndex < 0)
		a_nIndex = static_cast<int>(m_materialList.size() - 1);

	if (a_nIndex >= 0 && a_nIndex < static_cast<int>(m_materialList.size()))
	{
		m_materialList[a_nIndex]->SetNormalMapName(a_sFileName);
	}
}

void MaterialManager::SetSpecularMapName(String a_sFileName, int a_nIndex)
{
	if (a_nIndex < 0)
		a_nIndex = static_cast<int>(m_materialList.size() - 1);

	if (a_nIndex >= 0 && a_nIndex < static_cast<int>(m_materialList.size()))
	{
		m_materialList[a_nIndex]->SetSpecularMapName(a_sFileName);
	}
}

GLuint MaterialManager::GetDiffuseMap(uint a_nIndex)
{
	if (a_nIndex >= m_materialList.size())
		return 0;
	return m_materialList[a_nIndex]->GetDiffuseMap();
}
GLuint MaterialManager::GetNormalMap(uint a_nIndex)
{
	if (a_nIndex >= m_materialList.size())
		return 0;
	return m_materialList[a_nIndex]->GetNormalMap();
}
GLuint MaterialManager::GetSpecularMap(uint a_nIndex)
{
	if (a_nIndex >= m_materialList.size())
		return 0;
	return m_materialList[a_nIndex]->GetSpecularMap();
}

String MaterialManager::GetDiffuseMapName(int a_nIndex)
{
	if (a_nIndex < 0)
		a_nIndex = static_cast<int>(m_materialList.size() - 1);

	String sName = "";

	if (a_nIndex >= 0 && a_nIndex < static_cast<int>(m_materialList.size()))
	{
		sName = m_materialList[a_nIndex]->GetDiffuseMapName();
	}
	return sName;
}

String MaterialManager::GetNormalMapName(int a_nIndex)
{
	if (a_nIndex < 0)
		a_nIndex = static_cast<int>(m_materialList.size() - 1);

	String sName = "";

	if (a_nIndex >= 0 && a_nIndex < static_cast<int>(m_materialList.size()))
	{
		sName = m_materialList[a_nIndex]->GetNormalMapName();
	}
	return sName;
}

String MaterialManager::GetSpecularMapName(int a_nIndex)
{
	if (a_nIndex < 0)
		a_nIndex = static_cast<int>(m_materialList.size() - 1);

	String sName = "";

	if (a_nIndex >= 0 && a_nIndex < static_cast<int>(m_materialList.size()))
	{
		sName = m_materialList[a_nIndex]->GetSpecularMapName();
	}
	return sName;
}
int MaterialManager::DuplicateMaterial(String a_sMaterialToDuplicate, String a_sDesiredName)
{
	static int uUnique = 0;
	while (IdentifyMaterial(a_sDesiredName) >= 0)
	{
		a_sDesiredName = std::to_string(uUnique) + "_" + a_sDesiredName;
		uUnique++;
	}
	Material oMaterial = GetMaterialCopy(a_sMaterialToDuplicate);
	oMaterial.SetName(a_sDesiredName);
	return AddMaterial(oMaterial);
}