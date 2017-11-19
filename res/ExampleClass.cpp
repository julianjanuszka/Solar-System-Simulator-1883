#include "ExampleClass.h"
using namespace Simplex;
//  ExampleClass
void ExampleClass::Init(void)
{
	m_nData = 0;
}
void ExampleClass::Swap(ExampleClass& other)
{
	std::swap(m_nData, other.m_nData);
	std::swap(m_lData, other.m_lData);
}
void ExampleClass::Release(void)
{
	m_lData.clear();
}
//The big 3
ExampleClass::ExampleClass(){Init();}
ExampleClass::ExampleClass(ExampleClass const& other)
{
	m_nData = other.m_nData;
	m_lData = other.m_lData;
}
ExampleClass& ExampleClass::operator=(ExampleClass const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		ExampleClass temp(other);
		Swap(temp);
	}
	return *this;
}
ExampleClass::~ExampleClass(){Release();};
//Accessors
void ExampleClass::SetData(int a_nData){ m_nData = a_nData; }
int ExampleClass::GetData(void){ return m_nData; }
void ExampleClass::SetDataOnVector(int a_nData){ m_lData.push_back(a_nData);}
int& ExampleClass::GetDataOnVector(int a_nIndex)
{
	int nIndex = static_cast<int>(m_lData.size());
	assert(a_nIndex >= 0 && a_nIndex < nIndex);
	return m_lData[a_nIndex];
}
//--- Non Standard Singleton Methods

