#include "BasicX\Light\Light.h"

using namespace BasicX;

void Light::Init(void)
{
	m_v4Position = vector3(0.0f);
	m_vColor = vector3(1,1,1);
	m_fIntensity = 10;
}
void Light::Swap(Light& other)
{
	std::swap(m_v4Position, other.m_v4Position);
	std::swap(m_vColor, other.m_vColor);
	std::swap(m_fIntensity, other.m_fIntensity);
}
void Light::Release(void)
{
}

//The Big 3
Light::Light(void) { Init(); }
Light::Light( vector3 a_v4Position, vector3 a_v3Color, float a_vIntensity)
{
	m_v4Position = a_v4Position;
	m_vColor = a_v3Color;
	m_fIntensity = a_vIntensity;
}
Light::Light(const Light& other)
{
	m_v4Position = other.m_v4Position;
	m_vColor = other.m_vColor;
	m_fIntensity = other.m_fIntensity;
}
Light& Light::operator=(const Light& other)
{
	if(this != &other)
	{
		Release();
		Light temp(other);
		Swap(temp);
	}
	return *this;
}
Light::~Light(void)
{
	Release();
}

//Attributes
void Light::SetPosition(vector3 a_v4Position) { m_v4Position = a_v4Position; }
vector3 Light::GetPosition(void) { return m_v4Position; }

void Light::SetColor(vector3 a_v3Color) { m_vColor = a_v3Color; }
vector3 Light::GetColor(void) { return m_vColor; }

void Light::SetIntensity(float a_fIntensity) { m_fIntensity = a_fIntensity; }
float Light::GetIntensity(void) { return m_fIntensity; }
