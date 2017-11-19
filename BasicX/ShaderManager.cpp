#include "BasicX\System\ShaderManager.h"
using namespace BasicX;
//  ShaderManager
ShaderManager* ShaderManager::m_pInstance = nullptr;
void ShaderManager::Init(void)
{
	m_uShaderCount = 0;
	//printf("Shaders: ");

	//Compile Color shader
	Folder* pFolder = Folder::GetInstance();

	//Compile Text shader
	CompileShader(pFolder->GetFolderShaders() + "Text.vs", pFolder->GetFolderShaders() + "Text.fs", "Text");

	//Compile Basic shader
	CompileShader(pFolder->GetFolderShaders() + "Basic.vs", pFolder->GetFolderShaders() + "Basic.fs", "Basic");

	//Compile Skybox shader
	CompileShader(pFolder->GetFolderShaders() + "Skybox.vs", pFolder->GetFolderShaders() + "Skybox.fs", "Skybox");

	//Compile Wireframe shader
	CompileShader(pFolder->GetFolderShaders() + "Simplex.vs", pFolder->GetFolderShaders() + "Wireframe.fs", "Wireframe");

	//Compile Simplex shader
	CompileShader(pFolder->GetFolderShaders() + "Simplex.vs", pFolder->GetFolderShaders() + "Simplex.fs", "Simplex");

	printf("\n");
}
void ShaderManager::Release(void)
{
	int nShaders = static_cast<int>(m_vShader.size());
	for(int nShader = 0; nShader < nShaders; nShader++)
	{
		m_vShader[nShader].Release();
	}

	m_vShader.clear();
}
ShaderManager* ShaderManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new ShaderManager();
	}
	return m_pInstance;
}
void ShaderManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
ShaderManager::ShaderManager(){Init();}
ShaderManager::ShaderManager(ShaderManager const& other){}
ShaderManager& ShaderManager::operator=(ShaderManager const& other) {	return *this; }
ShaderManager::~ShaderManager(){Release();};
//--- Non Standard Singleton Methods
GLuint ShaderManager::CompileShader(String a_sVertexShader, String a_sFragmentShader, String a_sName)
{
	int nShader = IdentifyShader(a_sName);
	if(nShader != -1)
		return nShader;

	Shader vShader;
	printf("Compiling shader: %s\n", a_sName.c_str());
	nShader = vShader.CompileShader(a_sVertexShader, a_sFragmentShader, a_sName);
	m_vShader.push_back(vShader);
	m_map[vShader.GetProgramName()] = m_uShaderCount;
	m_uShaderCount++;

	return nShader;
}
int ShaderManager::IdentifyShader(String a_sName)
{
	auto var = m_map.find(a_sName);
	if(var != m_map.end())
		return var->second;
	return -1;
}
GLuint ShaderManager::GetShaderID(String a_sName)
{
	int nIndex = IdentifyShader(a_sName);
	if(nIndex == -1)
		return 0;
	else
		return m_vShader[nIndex].GetProgramID();
}

GLuint ShaderManager::GetShaderID(uint a_uIndex)
{
	if(a_uIndex < 0 || a_uIndex >= m_uShaderCount)
		return 0;

	return m_vShader[a_uIndex].GetProgramID();
}