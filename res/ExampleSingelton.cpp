#include "ExampleSingleton.h"
using namespace Simplex;
//  ExampleSingleton
ExampleSingleton* ExampleSingleton::m_pInstance = nullptr;
void ExampleSingleton::Init(void)
{
	m_nData = 0;
}
void ExampleSingleton::Release(void)
{
	m_lData.clear();
}
ExampleSingleton* ExampleSingleton::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new ExampleSingleton();
	}
	return m_pInstance;
}
void ExampleSingleton::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
ExampleSingleton::ExampleSingleton(){Init();}
ExampleSingleton::ExampleSingleton(ExampleSingleton const& other){ }
ExampleSingleton& ExampleSingleton::operator=(ExampleSingleton const& other) { return *this; }
ExampleSingleton::~ExampleSingleton(){Release();};
//Accessors
void ExampleSingleton::SetData(int a_nData){ m_nData = a_nData; }
int ExampleSingleton::GetData(void){ return m_nData; }
void ExampleSingleton::SetDataOnVector(int a_nData){ m_lData.push_back(a_nData);}
int& ExampleSingleton::GetDataOnVector(int a_nIndex)
{
	int nIndex = static_cast<int>(m_lData.size());
	assert(a_nIndex >= 0 && a_nIndex < nIndex);
	return m_lData[a_nIndex];
}
//--- Non Standard Singleton Methods

