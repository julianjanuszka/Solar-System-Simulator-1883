#include "BasicX\Light\LightManager.h"
using namespace BasicX;
//  LightManager
LightManager* LightManager::m_pInstance = nullptr;
void LightManager::Init(void)
{
	m_uLightCount = 0;
	m_lLight.clear();
	m_fAmbient = 0.1f;

	AddLight(vector3(0.0f), vector3(1.0f), 0.1f );//Ambient
	AddLight();//Point light 1
}
void LightManager::Release(void)
{
	m_uLightCount = static_cast<int>(m_lLight.size());
	for(uint uLight = 0; uLight < m_uLightCount; uLight++)
	{
		Light* temp = m_lLight[uLight];
		if(temp)
		{
			delete m_lLight[uLight];
			m_lLight[uLight] = nullptr;
		}
	}
	m_uLightCount = 0;
	m_lLight.clear();
}
LightManager* LightManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new LightManager();
	}
	return m_pInstance;
}
void LightManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
LightManager::LightManager(){Init();}
LightManager::LightManager(LightManager const& other){}
LightManager& LightManager::operator=(LightManager const& other) {	return *this; }
LightManager::~LightManager(){Release();};
//--- Non Standard Singleton Methods
void LightManager::AddLight( vector3 a_v4Position, vector3 a_v3Color, float a_vIntensity)
{
	Light* pLight = new Light(a_v4Position, a_v3Color, a_vIntensity);
	m_lLight.push_back(pLight);
	m_uLightCount++;
}
Light* LightManager::GetLight(uint a_nLightIndex)
{
	if(a_nLightIndex < 0 || a_nLightIndex >= m_uLightCount)
		return nullptr;
	
	return m_lLight[a_nLightIndex];
}

void LightManager::SetPosition(vector3 a_v4Position, uint a_nLightIndex)
{
	m_lLight[a_nLightIndex]->SetPosition(a_v4Position);
}
vector3 LightManager::GetPosition(uint a_nLightIndex)
{
	return m_lLight[a_nLightIndex]->GetPosition();
}

void LightManager::SetColor(vector3 a_v3Color, uint a_nLightIndex)
{
	m_lLight[a_nLightIndex]->SetColor(a_v3Color);
}
vector3 LightManager::GetColor(uint a_nLightIndex)
{
	return m_lLight[a_nLightIndex]->GetColor();
}

void LightManager::SetIntensity(float a_fIntensity, uint a_nLightIndex)
{
	m_lLight[a_nLightIndex]->SetIntensity(a_fIntensity);
}
float LightManager::GetIntensity(uint a_nLightIndex)
{
	return m_lLight[a_nLightIndex]->GetIntensity();
}