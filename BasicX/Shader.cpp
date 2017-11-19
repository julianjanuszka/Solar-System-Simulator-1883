#include "BasicX\System\Shader.h"
using namespace BasicX;
void Shader::Init(void)
{
	//m_sProgramName;
	//m_sVertexShaderName;
	//m_sFragmentShaderName;
	//m_nProgram;

	m_sProgramName = "";
	m_sVertexShaderName = "";
	m_sFragmentShaderName = "";
	m_nProgram = -1;
}
void Shader::Swap(Shader& other)
{
	std::swap( m_sProgramName, other.m_sProgramName);
	std::swap( m_sVertexShaderName, other.m_sVertexShaderName);
	std::swap( m_sFragmentShaderName, other.m_sFragmentShaderName);
	std::swap( m_nProgram, other.m_nProgram);
}
void Shader::Release(void)
{
	if(m_nProgram >= 0 )
	{
		glDeleteProgram(m_nProgram);
		m_nProgram = -1;
	}
}

//The Big 3
Shader::Shader(void) { Init(); }
Shader::Shader(const Shader& other)
{
	m_sProgramName = other.m_sProgramName;
	m_sVertexShaderName = other.m_sVertexShaderName;
	m_sFragmentShaderName = other.m_sFragmentShaderName;
	m_nProgram = other.m_nProgram;
}
Shader& Shader::operator=(const Shader& other)
{
	if(this != &other)
	{
		Release();
		Shader temp(other);
		Swap(temp);
	}
	return *this;
}
Shader::~Shader(void)
{
	//Release();
}

GLuint Shader::CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName)
{
	if(a_sName != "")
		m_sProgramName = a_sName;
	else
		m_sProgramName = a_sVertexShader + "||" + a_sFragmentShader;
	
	m_sVertexShaderName = a_sVertexShader;
	m_sFragmentShaderName = a_sFragmentShader;
	m_nProgram = LoadShaders( m_sVertexShaderName.c_str(), m_sFragmentShaderName.c_str() );

	return m_nProgram;
}

//Attributes
String Shader::GetProgramName() { return m_sProgramName; }
String Shader::GetVertexShaderName() { return m_sVertexShaderName; }
String Shader::GetFragmentShaderName() { return m_sFragmentShaderName; }
int Shader::GetProgramID() { return m_nProgram; }
