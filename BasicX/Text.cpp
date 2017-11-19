#include "BasicX\Mesh\Text.h"
using namespace BasicX;
#define BUFFER_OFFSET(i) ((char *) NULL + (i))
//  Text
Text* Text::m_pInstance = nullptr;
void Text::Init(void)
{
	m_sText = "";
	m_sTextPrev = "";
	m_sFont;

	m_bBinded = false;
	m_uVertexCount = 0;
	m_uMaterialIndex = -1;

	m_vao = 0;
	m_VBO = 0;
	
	m_nShader = 0;

	m_pSystem = SystemSingleton::GetInstance();
	m_pMatMngr = MaterialManager::GetInstance();
	m_pShaderMngr = ShaderManager::GetInstance();
	m_nShader = m_pShaderMngr->GetShaderID("Text");//Compile Text shader
	m_v3Head = ZERO_V3;
	SetFont("Font.png");	
	CompileOpenGL3X();
}
void Text::Release(void)
{
	m_pMatMngr = nullptr;
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_vao > 0)
		glDeleteVertexArrays(1, &m_vao);

	m_lVertexPos.clear();
	m_lVertexCol.clear();
	m_lVertexUV.clear();
}
void Text::SetFont(String a_sTextureName)
{
	if (a_sTextureName == m_sFont)
		return;

	m_sFont = a_sTextureName;
	int nMaterials = m_pMatMngr->GetMaterialCount();
	int nMaterial = m_pMatMngr->AddMaterial(m_sFont);
	if (nMaterials != m_pMatMngr->GetMaterialCount())
	{
		m_pMatMngr->m_materialList[nMaterial]->SetDiffuseMapName(m_sFont);
		m_pMatMngr->ReloadMaps();
	}
	m_uMaterialIndex = nMaterial;
}
Text* Text::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Text();
	}
	return m_pInstance;
}
void Text::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
Text::Text(){	Init(); }
Text::Text(Text const& other){ }
Text& Text::operator=(Text const& other){ return *this; }
Text::~Text(){ Release(); };
//Methods
void Text::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	// Create a vertex array object
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Create and initialize a buffer object for each shape.
	glGenBuffers(1, &m_VBO);

	m_bBinded = true;

	return;
}
void Text::Render(void)
{
	float fSize = 7.0f;
	bool bChange = false;
	if (m_sText != m_sTextPrev || m_lColor != m_lColorPrev)
	{
		bChange = true;
		m_v3Head = vector3(-36.0f, 7.77f, 0);

		m_lVertexPos.clear();
		m_lVertexUV.clear();
		m_lVertexCol.clear();

		for (uint n = 0; n < m_sText.size(); n++)
		{
			AddCharacter(m_sText[n], m_lColor[n]);
		}

		m_lVertex.clear();
		m_lVertex = m_lVertexPos;
		m_lVertex.insert(m_lVertex.end(), m_lVertexCol.begin(), m_lVertexCol.end());
		m_lVertex.insert(m_lVertex.end(), m_lVertexUV.begin(), m_lVertexUV.end());
	}

	m_uVertexCount = m_lVertexPos.size();

	if (m_uVertexCount == 0)
		return;

	if (!m_bBinded)
		return;

	GLuint nShader = m_nShader;
	// Use the buffer and shader
	glUseProgram(nShader);
	glBindVertexArray(m_vao);
	// Get the GPU variables by their name and hook them to CPU variables

	GLuint Position_b = glGetAttribLocation(nShader, "Position_b");
	GLuint UV_b = glGetAttribLocation(nShader, "UV_b");
	GLuint Color_b = glGetAttribLocation(nShader, "Color_b");

	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint TextureID = glGetUniformLocation(nShader, "TextureID");
	
	float fRatio = static_cast<float>(m_pSystem->GetWindowWidth()) / static_cast<float>(m_pSystem->GetWindowHeight());
	
	//matrix4 mProjection = glm::ortho(-fSize, fSize, -fSize + fSize / 10.0f, fSize / 10.0f, 0.1f, 1.1f);
	matrix4 mProjection = glm::ortho(-fSize, fSize, -fSize, fSize, 0.1f, 1.1f);
	matrix4 mView = glm::lookAt(vector3(0.0f, 0.0f, 1.0f), ZERO_V3, AXIS_Y);

	//Final Projection of the Camera
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(mProjection * mView));
	
	// Bind our texture in Texture Unit 0
	int nMaterialIndex = m_uMaterialIndex;
	if (m_pMatMngr->m_materialList[nMaterialIndex]->GetDiffuseMapName() != "NULL")
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_pMatMngr->m_materialList[nMaterialIndex]->GetDiffuseMap());
		glUniform1i(TextureID, 0);
	}

	//vertex
	glEnableVertexAttribArray(Position_b);
	glEnableVertexAttribArray(UV_b);
	glEnableVertexAttribArray(Color_b);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	if (bChange)
	{
		glBufferData(GL_ARRAY_BUFFER, 3 * m_uVertexCount * sizeof(vector3), &m_lVertex[0], GL_DYNAMIC_DRAW);
	}
	glVertexAttribPointer(Position_b, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribPointer(Color_b, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_uVertexCount * sizeof(vector3)));
	glVertexAttribPointer(UV_b, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2 * m_uVertexCount * sizeof(vector3)));

	//Color and draw
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);

	glDisable(GL_TEXTURE0);

	glDisableVertexAttribArray(Position_b);
	glDisableVertexAttribArray(UV_b);
	glDisableVertexAttribArray(Color_b);

	m_sTextPrev = m_sText;
	m_sText = "";
	m_lColorPrev = m_lColor;
	m_lColor.clear();

	glBindVertexArray(0);
}
void Text::Reset(void)
{
	m_v3Head = vector3(-26, 0, 0);

	m_lVertexPos.clear();
	m_lVertexUV.clear();
	m_lVertexCol.clear();

	m_uVertexCount = 0;

	m_lColor.clear();
	m_sText = "";
}
void Text::AddString(String a_sString, vector3 a_v3Color)
{
	m_sText += a_sString;
	
	for (uint n = 0; n < a_sString.size(); n++)
	{
		m_lColor.push_back(a_v3Color);
	}
}
void Text::AddCharacter(char a_cInput, vector3 a_v3Color)
{
	vector3 vOffset = vector3(0.19f, 0.75f, 0.0f);
	//vector3 vOffset = vector3(0.525f / 2.0f, 0.820f, 0.0f);
	//vector3 vOffset = vector3(1.00f, 1.00f, 0.0f);
	if (a_cInput == '\n')
	{
		m_v3Head.x = -36.0f;
		m_v3Head.y -= vOffset.y;
		return;
	}

	int nIndex = static_cast<int>(a_cInput);
	if (nIndex == 9)
	{
		uint tabToSpace = 5;
		for (uint i = 0; i < tabToSpace; ++i)
		{
			AddCharacter(' ', a_v3Color);
		}
		return;
	}
	nIndex -= 32;
	if (nIndex < 0 || nIndex > 94)
		nIndex = 0;

	int nColumn = nIndex % 10;
	int nRow = static_cast<int>(nIndex / 10);

	m_lVertexPos.push_back(vector3(0.0f + (vOffset.x * m_v3Head.x), 0.0f + (vOffset.y * m_v3Head.y), 0.0f));
	m_lVertexPos.push_back(vector3(vOffset.x + (vOffset.x * m_v3Head.x), 0.0f + (vOffset.y * m_v3Head.y), 0.0f));
	m_lVertexPos.push_back(vector3(0.0f + (vOffset.x * m_v3Head.x), vOffset.y + (vOffset.y * m_v3Head.y), 0.0f));

	m_lVertexPos.push_back(vector3(0.0f + (vOffset.x * m_v3Head.x), vOffset.y + (vOffset.y * m_v3Head.y), 0.0f));
	m_lVertexPos.push_back(vector3(vOffset.x + (vOffset.x * m_v3Head.x), 0.0f + (vOffset.y * m_v3Head.y), 0.0f));
	m_lVertexPos.push_back(vector3(vOffset.x + (vOffset.x * m_v3Head.x), vOffset.y + (vOffset.y * m_v3Head.y), 0.0f));

	vector3 vUV = vector3(0.1f, 0.1f, 0.0f);

	m_lVertexUV.push_back(vector3(0.0f + vUV.x * nColumn, 0.9f - vUV.y * nRow, 0.0f));
	m_lVertexUV.push_back(vector3(0.1f + vUV.x * nColumn, 0.9f - vUV.y * nRow, 0.0f));
	m_lVertexUV.push_back(vector3(0.0f + vUV.x * nColumn, 1.0f - vUV.y * nRow, 0.0f));

	m_lVertexUV.push_back(vector3(0.0f + vUV.x * nColumn, 1.0f - vUV.y * nRow, 0.0f));
	m_lVertexUV.push_back(vector3(0.1f + vUV.x * nColumn, 0.9f - vUV.y * nRow, 0.0f));
	m_lVertexUV.push_back(vector3(0.1f + vUV.x * nColumn, 1.0f - vUV.y * nRow, 0.0f));

	m_lVertexCol.push_back(a_v3Color);
	m_lVertexCol.push_back(a_v3Color);
	m_lVertexCol.push_back(a_v3Color);

	m_lVertexCol.push_back(a_v3Color);
	m_lVertexCol.push_back(a_v3Color);
	m_lVertexCol.push_back(a_v3Color);

	m_v3Head.x += 1.0f;

	if (m_v3Head.x > 36)
	{
		m_v3Head.x = -36.0f;
		m_v3Head.y -= vOffset.y;
	}
}