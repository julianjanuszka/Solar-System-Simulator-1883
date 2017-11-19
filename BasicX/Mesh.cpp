#include "BasicX\Mesh\Mesh.h"
using namespace BasicX;
uint Mesh::m_nIndexer = 0;
uint Mesh::m_uRenderCalls = 0;
uint Mesh::GetStaticCount(void) { return m_nIndexer; }
uint Mesh::GetRenderCallCount(void) { return m_uRenderCalls; }
void Mesh::ResetRenderCallCount(void) { m_uRenderCalls = 0; }
//  Mesh
void Mesh::Init(void)
{
	m_sName = "NULL";
	m_pOriginal = nullptr;
	m_bBinded = false;
	m_uVertexCount = 0;
	m_uMaterialIndex = -1;
	
	m_VAO = 0;
	m_VBO = 0;

	m_v3Tint = DEFAULT_V3NEG;

	m_nShader = 0;

	m_pMatMngr = MaterialManager::GetInstance();
	m_pShaderMngr = ShaderManager::GetInstance();
	m_pLightMngr = LightManager::GetInstance();
	m_nShader = m_pShaderMngr->GetShaderID("BasicX");
}
void Mesh::Swap(Mesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_pOriginal, other.m_pOriginal);
	std::swap(m_uVertexCount, other.m_uVertexCount);
	std::swap(m_uMaterialIndex, other.m_uMaterialIndex);

	std::swap(m_v3Tint, other.m_v3Tint);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);
	std::swap(m_nShader, other.m_nShader);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);
	std::swap(m_lVertexNor, other.m_lVertexNor);
	std::swap(m_lVertexTan, other.m_lVertexTan);
	std::swap(m_lVertexBin, other.m_lVertexBin);
	std::swap(m_lVertexUV, other.m_lVertexUV);

	std::swap(m_pMatMngr, other.m_pMatMngr);
	std::swap(m_pShaderMngr, other.m_pShaderMngr);
	std::swap(m_pLightMngr, other.m_pLightMngr);

	std::swap(m_sName, other.m_sName);
}
void Mesh::Release(void)
{
	m_pMatMngr = nullptr;
	m_pShaderMngr = nullptr;
	m_pLightMngr = nullptr;

	if(m_pOriginal != nullptr)
		DisconnectOpenGL3X();

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if(m_VAO > 0 )
		glDeleteVertexArrays(1, &m_VAO);
	
	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
	m_lVertexNor.clear();
	m_lVertexTan.clear();
	m_lVertexBin.clear();
	m_lVertexUV.clear();
}
//The big 3
Mesh::Mesh()
{
	Init();
	m_uID = m_nIndexer;
	m_nIndexer++;
}
Mesh::Mesh(Mesh& other)
{
	m_sName = other.m_sName;

	m_pOriginal = &other;
	m_pShaderMngr = other.m_pShaderMngr;
	m_pMatMngr = other.m_pMatMngr;
	m_pLightMngr = other.m_pLightMngr;

	m_bBinded = other.m_bBinded;

	m_uMaterialIndex = other.m_uMaterialIndex;
	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;

	m_nShader = other.m_nShader;

	m_v3Tint = other.m_v3Tint;
	m_v3Wireframe = other.m_v3Wireframe;

	m_uID = m_nIndexer;
	m_nIndexer++;
}
Mesh& Mesh::operator=(Mesh& other)
{
	if(this != &other)
	{
		Release();
		Init();
		Mesh temp(other);
		Swap(temp);
	}
	return *this;
}
void Mesh::Instantiate(Mesh* const other)
{
	if (other == nullptr)
		return;

	m_pOriginal = other;

	m_sName = other->m_sName + std::to_string(m_uID);

	m_bBinded = other->m_bBinded;
	m_uVertexCount = other->m_uVertexCount;
	m_uMaterialIndex = other->m_uMaterialIndex;

	m_VAO = other->m_VAO;
	m_VBO = other->m_VBO;

	m_nShader = other->m_nShader;

	m_v3Tint = other->m_v3Tint;
	m_v3Wireframe = other->m_v3Wireframe;

	m_pMatMngr = other->m_pMatMngr;
	m_pShaderMngr = other->m_pShaderMngr;
	m_pLightMngr = other->m_pLightMngr;
}
Mesh::~Mesh(){Release();}
//Accessors
bool Mesh::GetBinded(void){ return m_bBinded; }
void Mesh::SetMaterial(int a_nMaterialIndex)
{
	if(a_nMaterialIndex >= 0 && a_nMaterialIndex < m_pMatMngr->GetMaterialCount())
		m_uMaterialIndex = a_nMaterialIndex;
}
void Mesh::SetMaterial(String a_sMaterialName)
{
	
	int nMaterial = m_pMatMngr->IdentifyMaterial(a_sMaterialName);
	if(nMaterial != -1)
	{
		m_uMaterialIndex = nMaterial;
		SetShaderProgram();
	}
}
void Mesh::SetMaterial(String a_sMaterialName, String a_sDiffuseMapName, String a_sNormalMapName, String a_sSpecularName)
{
	m_uMaterialIndex = m_pMatMngr->AddMaterial(a_sDiffuseMapName, a_sDiffuseMapName, a_sNormalMapName, a_sSpecularName);
	SetShaderProgram();
}
int Mesh::GetVertexCount(void){ return m_uVertexCount; }
int  Mesh::GetMaterialIndex(void){return m_uMaterialIndex; }
void Mesh::AddVertexPosition(vector3 input){ m_lVertexPos.push_back(input); m_uVertexCount++; }
void Mesh::AddVertexPositionList(std::vector<vector3> a_lInput, matrix4 a_m4ModelToWorld)
{
	uint nVertexCount = a_lInput.size();
	if (a_m4ModelToWorld != IDENTITY_M4)
	{
		for (uint n = 0; n < nVertexCount; n++)
		{
			a_lInput[n] = vector3(a_m4ModelToWorld * vector4(a_lInput[n], 1.0f));
		}
	}
	m_lVertexPos.insert(m_lVertexPos.end(), a_lInput.begin(), a_lInput.end());
	m_uVertexCount += nVertexCount;
}
void Mesh::AddVertexColor(vector3 input){ m_lVertexCol.push_back(input); }
void Mesh::AddVertexColorList(std::vector<vector3> a_lInput)
{
	m_lVertexCol.insert(m_lVertexCol.end(), a_lInput.begin(), a_lInput.end());
}
void Mesh::AddVertexNormal(vector3 input){ m_lVertexNor.push_back(input); }
void Mesh::AddVertexNormalList(std::vector<vector3> a_lInput)
{
	m_lVertexNor.insert(m_lVertexNor.end(), a_lInput.begin(), a_lInput.end());
}
void Mesh::AddVertexBinormal(vector3 input){ m_lVertexBin.push_back(input); }
void Mesh::AddVertexBinormalList(std::vector<vector3> a_lInput)
{
	m_lVertexBin.insert(m_lVertexBin.end(), a_lInput.begin(), a_lInput.end());
}
void Mesh::AddVertexTangent(vector3 input){ m_lVertexTan.push_back(input); }
void Mesh::AddVertexTangentList(std::vector<vector3> a_lInput)
{
	m_lVertexTan.insert(m_lVertexTan.end(), a_lInput.begin(), a_lInput.end());
}
void Mesh::AddVertexUV(vector3 input){ m_lVertexUV.push_back(input); }
void Mesh::AddVertexUVList(std::vector<vector3> a_lInput)
{
	m_lVertexUV.insert(m_lVertexUV.end(), a_lInput.begin(), a_lInput.end());
}
void Mesh::SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName)
{
	int nShader = m_pShaderMngr->CompileShader( a_sVertexShaderName, a_sFragmentShaderName, a_sShaderName);
	if(nShader != 0)
		m_nShader = m_pShaderMngr->GetShaderID(a_sShaderName);
	return;
}
void Mesh::SetShaderProgram(String a_sShaderName)
{
	int nShader = m_pShaderMngr->GetShaderID(a_sShaderName);
	if (nShader != 0)
		m_nShader = nShader;
	return;
}
void Mesh::SetVertexList(std::vector<vector3> a_lVertex){ m_lVertexPos = a_lVertex; }
std::vector<vector3> Mesh::GetVertexList(void){ return m_lVertexPos; }
void Mesh::SetColorList(std::vector<vector3> a_lcolor) { m_lVertexCol = a_lcolor; }
std::vector<vector3> Mesh::GetColorList(void){ return m_lVertexCol; }
void Mesh::SetUVList(std::vector<vector3> a_lUV) { m_lVertexUV = a_lUV; }
std::vector<vector3> Mesh::GetUVList(void){ return m_lVertexUV; }
void Mesh::SetNormalList(std::vector<vector3> a_lNormal) { m_lVertexNor = a_lNormal; }
std::vector<vector3> Mesh::GetNormalList(void){ return m_lVertexNor; }
void Mesh::SetTangentList(std::vector<vector3> a_lTangent) { m_lVertexTan = a_lTangent; }
std::vector<vector3> Mesh::GetTangentList(void){ return m_lVertexTan; }
void Mesh::SetBitangentList(std::vector<vector3> a_lBitangent) { m_lVertexBin = a_lBitangent; }
std::vector<vector3> Mesh::GetBitangetList(void){ return m_lVertexBin; }
uint Mesh::GetUniqueIdentifier(void) { return m_uID; }
vector3 Mesh::GetTint(void){ return m_v3Tint; }
void Mesh::SetTint(vector3 a_v3Tint) { m_v3Tint = a_v3Tint; }
String Mesh::GetName(void){ return m_sName; }
void Mesh::SetName(String a_sName){ m_sName = a_sName; }
GLuint Mesh::GetShaderIndex (void){ return m_nShader; }
//Methods
void Mesh::CompleteTriangleInfo(bool a_bAverageNormals)
{
	//Complete Colors
	int nColors = static_cast<int>(m_lVertexCol.size());
	for(uint i = nColors; i < m_uVertexCount; i++)
		m_lVertexCol.push_back(vector3(1,1,1));
	
	//Complete UVs
	int nUVs = static_cast<int>(m_lVertexUV.size());
	for(uint i = nUVs; i < m_uVertexCount; i++)
		m_lVertexUV.push_back(vector3(0,0,0));
	
	//Complete normals
	int nNormals = static_cast<int>(m_lVertexNor.size());
	if(m_uVertexCount % 3 == 0)
	{
		for(uint i = nNormals; i < m_uVertexCount -1; i += 3)
		{
			vector3& v0 = m_lVertexPos[i];
			vector3& v1 = m_lVertexPos[i+1];
			vector3& v2 = m_lVertexPos[i+2];

			vector3 d0 = v1 - v0;
			vector3 d1 = v2 - v1;

			vector3 normal = glm::cross(d0, d1);
			if(normal.x == 0 && normal.y == 0 && normal.z == 0)
			{
				//All 3 components are 0 so this is a 0 vector and normal
				//needs to point somewhere, the DEFAULT_V3NEG is outside of the screen
				normal = vector3( 0.0, 0.0, 1.0);
			}
			else
			{
				normal = glm::normalize(normal);
			}

			m_lVertexNor.push_back(normal);
			m_lVertexNor.push_back(normal);
			m_lVertexNor.push_back(normal);
		}
	}
	else
	{
		for(uint i = nUVs; i < m_uVertexCount; i++)
			m_lVertexNor.push_back(vector3(0,0,1));
	}

	if(a_bAverageNormals)
	{
		for(uint i = 0; i < m_uVertexCount; i++)
		{
			std::vector<int> vIndices;
			for (uint j = i; j < m_uVertexCount; j++)
			{
				if(m_lVertexPos[i] == m_lVertexPos[j])
					vIndices.push_back(j);
			}
			int nSize = static_cast<int> (vIndices.size());
			vector3 normalAverage = ZERO_V3;
			for (int k = 0; k < nSize; k++)
			{
				normalAverage += m_lVertexNor[vIndices[k]];
			}
			if (normalAverage != ZERO_V3)
				normalAverage = glm::normalize(normalAverage);
			for (int k = 0; k < nSize; k++)
			{
				m_lVertexNor[vIndices[k]] = normalAverage;
			}
		}
	}
}
void Mesh::CalculateTangents(void)
{
	for (uint i = 0; i < m_uVertexCount; i += 3)
	{
		vector3 tangent = m_lVertexPos[i+1] - m_lVertexPos[i];
		vector3 tangent2 = m_lVertexPos[i+2] - m_lVertexPos[i+1];

		vector3 normal = glm::cross(tangent,tangent2);
		vector3 binormal = glm::cross(normal, tangent);
		
		vector3 deltaPos1 = m_lVertexPos[i+1] - m_lVertexPos[i];
		vector3 deltaPos2 = m_lVertexPos[i+2] - m_lVertexPos[i];
		
		vector3 deltaUV1 = m_lVertexUV[i+1] - m_lVertexUV[i];
		vector3 deltaUV2 = m_lVertexUV[i+2] - m_lVertexUV[i];
			
		float inv = deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x;
		if(inv != 0)
		{
			float r = 1.0f / (inv);
			{
				tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
				binormal = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;
				if( tangent.x != 0 && tangent.y != 0 && tangent.z != 0)
					tangent = glm::normalize(tangent);
				if( binormal.x != 0 && binormal.y != 0 && binormal.z != 0)
					binormal = glm::normalize(binormal);
			}
		}

		AddVertexBinormal(binormal);
		AddVertexBinormal(binormal);
		AddVertexBinormal(binormal);

		AddVertexTangent(tangent);
		AddVertexTangent(tangent);
		AddVertexTangent(tangent);
	}

	for (uint i = 0 ; i < m_uVertexCount; i++ )
	{
		vector3 & n = m_lVertexNor[i];
		vector3 & t = m_lVertexTan[i];
		vector3 & b = m_lVertexBin[i];
		
		// Gram-Schmidt orthogonalize
		t = t - n * glm::dot(n, t);
		if(t != vector3(0.0f))
			t = glm::normalize(t);
		
		// Calculate handedness
		if (glm::dot(glm::cross(n, t), b) < 0.0f)
		{
			t = t * -1.0f;
		}
	}
}
void Mesh::DisconnectOpenGL3X(void)
{
	m_VAO = 0;
	m_VBO = 0;
}
void Mesh::CompleteMesh(vector3 a_v3Color)
{
	int nColorTotal = static_cast<int>(m_lVertexCol.size());
	for(uint nColor = nColorTotal; nColor < m_uVertexCount; nColor++)
		m_lVertexCol.push_back(a_v3Color);

	int nNormalTotal = static_cast<int>(m_lVertexNor.size());
	for(uint nNormal = nNormalTotal; nNormal < m_uVertexCount; nNormal++)
		m_lVertexNor.push_back(vector3(0.0f, 0.0f, 1.0f));

	int nBinormalTotal = static_cast<int>(m_lVertexBin.size());
	for(uint nBinormal = nBinormalTotal; nBinormal < m_uVertexCount; nBinormal++)
		m_lVertexBin.push_back(vector3(0.0f, 1.0f, 0.0f));

	int nTangentTotal = static_cast<int>(m_lVertexTan.size());
	for(uint nTangent = nTangentTotal; nTangent < m_uVertexCount; nTangent++)
		m_lVertexTan.push_back(vector3(1.0f, 0.0f, 0.0f));

	int nUVTotal = static_cast<int>(m_lVertexUV.size());
	for(uint nUV = nUVTotal; nUV < m_uVertexCount; nUV++)
		m_lVertexUV.push_back(vector3(1.0f, 0.0f, 0.0f));
}
void Mesh::CompileOpenGL3X(void)
{
	if(m_bBinded)
		return;

	if(m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
		//UV
		m_lVertex.push_back(m_lVertexUV[i]);
		//Normal
		m_lVertex.push_back(m_lVertexNor[i]);
		//Bi-Normal
		m_lVertex.push_back(m_lVertexBin[i]);
		//Tangent
		m_lVertex.push_back(m_lVertexTan[i]);
	}
	glGenVertexArrays( 1, &m_VAO );//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object
	
	glBindVertexArray( m_VAO );//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 6 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));
	
	// UV attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vector3), (GLvoid*)(2 * sizeof(vector3)));
	
	// Normal attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vector3), (GLvoid*)(3 * sizeof(vector3)));
	
	// Bi-Normal attribute
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vector3), (GLvoid*)(4 * sizeof(vector3)));
	
	// Tangent attribute
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(vector3), (GLvoid*)(5 * sizeof(vector3)));

	if(m_uMaterialIndex < 0)
	{
		if(m_pMatMngr->GetMaterialCount() < 1)
		{
			Material temp("DEFAULT_V3NEG");
			temp.SetDiffuse(vector3(1.0f, 0.0f, 1.0f));
			m_uMaterialIndex = m_pMatMngr->AddMaterial(temp);
		}
		else
			m_uMaterialIndex = 0;
	}

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO

	return;
}
GLuint Mesh::GetVAO(void)
{
	return m_VAO;
}
GLuint Mesh::GetVBO(void)
{
	return m_VBO;
}
void Mesh::SetWireframeColor(vector3 a_v3Color){ m_v3Wireframe = a_v3Color; }
vector3 Mesh::GetWireframeColor(void) { return m_v3Wireframe; }
// Compile shapes
void Mesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexUV(vector3(0.0f, 0.0f, 0.0f));
	AddVertexUV(vector3(1.0f, 0.0f, 0.0f));
	AddVertexUV(vector3(0.0f, 1.0f, 0.0f));
}
void Mesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);

	//UV
	AddVertexUV(vector3(0.0f, 0.0f, 0.0f));
	AddVertexUV(vector3(1.0f, 0.0f, 0.0f));
	AddVertexUV(vector3(0.0f, 1.0f, 0.0f));

	AddVertexUV(vector3(0.0f, 1.0f, 0.0f));
	AddVertexUV(vector3(1.0f, 0.0f, 0.0f));
	AddVertexUV(vector3(1.0f, 1.0f, 0.0f));
}
void Mesh::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	vector3 point0(-fValue, -fValue, 0.0f); //0
	vector3 point1(fValue, -fValue, 0.0f); //1
	vector3 point2(fValue, fValue, 0.0f); //2
	vector3 point3(-fValue, fValue, 0.0f); //3

	AddQuad(point0, point1, point3, point2);

	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
	m_sName = "plane_(" + std::to_string(a_v3Color.x) +
		"," + std::to_string(a_v3Color.y) +
		"," + std::to_string(a_v3Color.z) + ")";
	SetShaderProgram("BasicColor");
}
void Mesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
	m_sName = "cube_(" + std::to_string(a_v3Color.x) +
		"," + std::to_string(a_v3Color.y) +
		"," + std::to_string(a_v3Color.z) + ")";
	SetShaderProgram("BasicColor");
}
void Mesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	//Code removed for assignment purposes
	GenerateCube(a_v3Dimensions.x, a_v3Color);
}
void Mesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	//Code removed for assignment purposes
	GenerateCube(a_fRadius * 2.0f, a_v3Color);
}
void Mesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	//Code removed for assignment purposes
	GenerateCube(a_fRadius * 2.0f, a_v3Color);
}
void Mesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	//Code removed for assignment purposes
	GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
}
void Mesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	//Code removed for assignment purposes
	GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
}
void Mesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Code removed for assignment purposes
	GenerateCube(a_fRadius * 2.0f, a_v3Color);
}
void Mesh::GenerateSkybox(void)
{
	Release();
	Init();

	float fValue = 500.0f;

	vector3 v3Position[8];
	v3Position[0] = vector3(-fValue, -fValue, fValue);
	v3Position[1] = vector3(fValue, -fValue, fValue);
	v3Position[2] = vector3(-fValue, fValue, fValue);
	v3Position[3] = vector3(fValue, fValue, fValue);
	v3Position[4] = vector3(-fValue, fValue, -fValue);
	v3Position[5] = vector3(fValue, fValue, -fValue);
	v3Position[6] = vector3(-fValue, -fValue, -fValue);
	v3Position[7] = vector3(fValue, -fValue, -fValue);

	AddTri(v3Position[0], v3Position[2], v3Position[1]);
	AddTri(v3Position[1], v3Position[2], v3Position[3]);
	AddTri(v3Position[2], v3Position[4], v3Position[3]);
	AddTri(v3Position[3], v3Position[4], v3Position[5]);
	AddTri(v3Position[4], v3Position[6], v3Position[5]);
	AddTri(v3Position[5], v3Position[6], v3Position[7]);
	AddTri(v3Position[6], v3Position[0], v3Position[7]);
	AddTri(v3Position[7], v3Position[0], v3Position[1]);
	AddTri(v3Position[1], v3Position[3], v3Position[7]);
	AddTri(v3Position[7], v3Position[3], v3Position[5]);
	AddTri(v3Position[6], v3Position[4], v3Position[0]);
	AddTri(v3Position[0], v3Position[4], v3Position[2]);

	m_lVertexUV.clear();

	vector3 v3UV[14];
	v3UV[0] = vector3(1.00, 0.333333, 0.00);
	v3UV[1] = vector3(1.00, 0.666666, 0.00);
	v3UV[2] = vector3(0.75, 0.666666, 0.00);
	v3UV[3] = vector3(0.75, 0.333333, 0.00);
	v3UV[4] = vector3(0.25, 1.000000, 0.00);
	v3UV[5] = vector3(0.25, 0.666666, 0.00);
	v3UV[6] = vector3(0.50, 0.666666, 0.00);
	v3UV[7] = vector3(0.50, 1.000000, 0.00);
	v3UV[8] = vector3(0.25, 0.333333, 0.00);
	v3UV[9] = vector3(0.50, 0.333333, 0.00);
	v3UV[10] = vector3(0.25, 0.000000, 0.00);
	v3UV[11] = vector3(0.50, 0.000000, 0.00);
	v3UV[12] = vector3(0.00, 0.666666, 0.00);
	v3UV[13] = vector3(0.00, 0.333333, 0.00);

	AddVertexUV(v3UV[0]);
	AddVertexUV(v3UV[1]);
	AddVertexUV(v3UV[3]);
	AddVertexUV(v3UV[3]);
	AddVertexUV(v3UV[1]);
	AddVertexUV(v3UV[2]);
	AddVertexUV(v3UV[4]);
	AddVertexUV(v3UV[5]);
	AddVertexUV(v3UV[7]);
	AddVertexUV(v3UV[7]);
	AddVertexUV(v3UV[5]);
	AddVertexUV(v3UV[6]);
	AddVertexUV(v3UV[5]);
	AddVertexUV(v3UV[8]);
	AddVertexUV(v3UV[6]);
	AddVertexUV(v3UV[6]);
	AddVertexUV(v3UV[8]);
	AddVertexUV(v3UV[9]);
	AddVertexUV(v3UV[8]);
	AddVertexUV(v3UV[10]);
	AddVertexUV(v3UV[9]);
	AddVertexUV(v3UV[9]);
	AddVertexUV(v3UV[10]);
	AddVertexUV(v3UV[11]);
	AddVertexUV(v3UV[3]);
	AddVertexUV(v3UV[2]);
	AddVertexUV(v3UV[9]);
	AddVertexUV(v3UV[9]);
	AddVertexUV(v3UV[2]);
	AddVertexUV(v3UV[6]);
	AddVertexUV(v3UV[8]);
	AddVertexUV(v3UV[5]);
	AddVertexUV(v3UV[13]);
	AddVertexUV(v3UV[13]);
	AddVertexUV(v3UV[5]);
	AddVertexUV(v3UV[12]);

	CompleteMesh(C_WHITE);
	CompileOpenGL3X();
	m_sName = "Skybox_Skybox.png";
	SetMaterial("Skybox", "Skybox.png");
	SetShaderProgram("Skybox");
}
void Mesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mWorld, vector3 a_v3CameraPosition, int a_RenderOption)
{
	Render(a_mProjection, a_mView, glm::value_ptr(a_mWorld), 1, a_v3CameraPosition, a_RenderOption);
}
void Mesh::Render( matrix4 a_mProjection, matrix4 a_mView, float* a_fMatrixArray, int a_nInstances, vector3 a_v3CameraPosition, int a_RenderOption)
{
	//check if the shape has been binded
	if (!m_bBinded)
		return;
	/*
		The purpose of the next part is to check if the mesh was sent to render
		with solid and wire, solid goes first and there is nothing else to do there
		other than marking that we went through the solid phase, if we are going to
		wire then we need check if we went to solid as well, if we did not we render
		in the color of the mesh, if we did we render in the color of the wireframe
		if we where to render in the color of the mesh as well then the lines of the
		wire would not be noticible.
	*/
	bool solid = false;
	//Draw
	if (a_RenderOption & BTO_RENDER::RENDER_SOLID)
	{
		solid = true;
		RenderSolid(a_mProjection, a_mView, a_fMatrixArray, a_nInstances, a_v3CameraPosition);
	}
	if (a_RenderOption & BTO_RENDER::RENDER_WIRE)
	{
		if (!solid)
		{
			vector3 wireframe;
			wireframe = m_v3Wireframe;
			std::swap(wireframe, m_v3Wireframe);
			RenderWire(a_mProjection, a_mView, a_fMatrixArray, a_nInstances);
			m_v3Wireframe = wireframe;
		}
		else
			RenderWire(a_mProjection, a_mView, a_fMatrixArray, a_nInstances);
	}
}
void Mesh::RenderWire(matrix4 a_mProjection, matrix4 a_mView, float* a_fMatrixArray, int a_nInstances)
{
	GLuint nShader = m_pShaderMngr->GetShaderID("Wireframe");
	// Use the buffer and shader
	glUseProgram(nShader);

	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint VP = glGetUniformLocation(nShader, "VP");
	GLuint m4ToWorld = glGetUniformLocation(nShader, "m4ToWorld");
	GLuint vWireframe = glGetUniformLocation(nShader, "vWireframe");

	//Final Projection of the Camera
	matrix4 m4VP = a_mProjection * a_mView;
	glUniformMatrix4fv(VP, 1, GL_FALSE, glm::value_ptr(m4VP));
	glUniform3f(vWireframe, m_v3Wireframe.x, m_v3Wireframe.y, m_v3Wireframe.z);

	//Number of Instances
	uint nSections = a_nInstances / 250;
	uint nRemainders = a_nInstances - (250 * nSections);
	uint nInstances = a_nInstances;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	for (uint n = 0; n < nSections; n++)
	{
		glUniformMatrix4fv(m4ToWorld, 250, GL_FALSE, &a_fMatrixArray[n * 250 * 16]);
		//Draw
		glDrawArraysInstanced(GL_TRIANGLES, 0, m_uVertexCount, 250);
		m_uRenderCalls++;
	}

	glUniformMatrix4fv(m4ToWorld, nRemainders, GL_FALSE, &a_fMatrixArray[nSections * 250 * 16]);
	glDrawArraysInstanced(GL_TRIANGLES, 0, m_uVertexCount, nRemainders);
	m_uRenderCalls++;

	glDisable(GL_POLYGON_OFFSET_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//Set rendering mode back to fill

	glBindVertexArray(0);
}
void Mesh::RenderSolid(matrix4 a_mProjection, matrix4 a_mView, float* a_fMatrixArray, int a_nInstances, vector3 a_v3CameraPosition)
{
	GLuint nShader = GetShaderIndex();
	// Use the buffer and shader
	glUseProgram(nShader);

	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint VP = glGetUniformLocation(nShader, "VP");
	GLuint m4ModelToWorld = glGetUniformLocation(nShader, "m4ModelToWorld");

	GLuint TextureID = glGetUniformLocation(nShader, "TextureID");
	GLuint NormalID = glGetUniformLocation(nShader, "NormalID");
	GLuint SpecularID = glGetUniformLocation(nShader, "SpecularID");
	GLuint nTexture = glGetUniformLocation(nShader, "nTexture");

	GLuint LightPosition_W = glGetUniformLocation(nShader, "LightPosition_W");
	GLuint LightColor = glGetUniformLocation(nShader, "LightColor");
	GLuint LightPower = glGetUniformLocation(nShader, "LightPower");
	GLuint AmbientColor = glGetUniformLocation(nShader, "AmbientColor");
	GLuint AmbientPower = glGetUniformLocation(nShader, "AmbientPower");
	GLuint Tint = glGetUniformLocation(nShader, "Tint");

	GLuint CameraPosition_W = glGetUniformLocation(nShader, "CameraPosition_W");

	GLuint gl_nInstances = glGetUniformLocation(nShader, "nElements");

	GLuint m4ToWorld = glGetUniformLocation(nShader, "m4ToWorld");
	GLuint m4CameraOnWorld = glGetUniformLocation(nShader, "m4CameraOnWorld");

	//ToWorld matrix
	glUniformMatrix4fv(m4ModelToWorld, 1, GL_FALSE, glm::value_ptr(matrix4(1.0f)));
	glUniformMatrix4fv(m4CameraOnWorld, 1, GL_FALSE, glm::value_ptr(glm::translate(a_v3CameraPosition)));

	//Final Projection of the Camera
	matrix4 m4VP = a_mProjection * a_mView;
	glUniformMatrix4fv(VP, 1, GL_FALSE, glm::value_ptr(m4VP));

	Light* pLight;
	pLight = m_pLightMngr->GetLight(0);
	vector3 v3Color = pLight->GetColor();
	glUniform3f(AmbientColor, v3Color.r, v3Color.g, v3Color.b);
	glUniform1f(AmbientPower, pLight->GetIntensity());
	pLight = m_pLightMngr->GetLight(1);
	v3Color = pLight->GetColor();
	vector3 v3Position = pLight->GetPosition();
	glUniform3f(LightPosition_W, v3Position.x, v3Position.y, v3Position.z);
	glUniform3f(LightColor, v3Color.r, v3Color.g, v3Color.b);
	glUniform1f(LightPower, pLight->GetIntensity());
	glUniform3f(Tint, m_v3Tint.r, m_v3Tint.g, m_v3Tint.b);

	glUniform3f(CameraPosition_W, a_v3CameraPosition.x, a_v3CameraPosition.y, a_v3CameraPosition.z);

	int nTextures = 0;
	// Bind our texture in Texture Unit 0
	int nMaterialIndex = static_cast<int>(m_uMaterialIndex);
	if (nMaterialIndex >= 0)
	{
		
		
		GLuint index = m_pMatMngr->GetDiffuseMap(nMaterialIndex);
		//if (m_pMatMngr->m_lMaterial[nMaterialIndex]->GetDiffuseMapName() != "NULL")
		if (index > 0)
		{
			glActiveTexture(GL_TEXTURE0);
			//glBindTexture(GL_TEXTURE_2D, m_pMatMngr->m_lMaterial[nMaterialIndex]->GetDiffuseMap());
			glBindTexture(GL_TEXTURE_2D, index);
			glUniform1i(TextureID, 0);
			nTextures += 1;
		}

		// Bind our texture in Texture Unit 1
		index = m_pMatMngr->GetNormalMap(nMaterialIndex);
		//if (m_pMatMngr->m_lMaterial[nMaterialIndex]->GetNormalMapName() != "NULL")
		if (index > 0)
		{
			glActiveTexture(GL_TEXTURE1);
			//glBindTexture(GL_TEXTURE_2D, m_pMatMngr->m_lMaterial[nMaterialIndex]->GetNormalMap());
			glBindTexture(GL_TEXTURE_2D, index);
			glUniform1i(NormalID, 1);
			nTextures += 2;
		}

		// Bind our texture in Texture Unit 2
		index = m_pMatMngr->GetSpecularMap(nMaterialIndex);
		//if (m_pMatMngr->m_lMaterial[nMaterialIndex]->GetSpecularMapName() != "NULL")
		{
			glActiveTexture(GL_TEXTURE2);
			//glBindTexture(GL_TEXTURE_2D, m_pMatMngr->m_lMaterial[nMaterialIndex]->GetSpecularMap());
			glBindTexture(GL_TEXTURE_2D, index);
			glUniform1i(SpecularID, 2);
			nTextures += 4;
		}
	}
	glUniform1i(nTexture, nTextures);

	//Number of Instances
	uint nSections = a_nInstances / 250;
	uint nRemainders = a_nInstances - (250 * nSections);
	uint nInstances = a_nInstances;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (uint n = 0; n < nSections; n++)
	{
		glUniform1i(gl_nInstances, 250);
		glUniformMatrix4fv(m4ToWorld, 250, GL_FALSE, &a_fMatrixArray[n * 250 * 16]);
		glUseProgram(nShader);
		
		glDrawArraysInstanced(GL_TRIANGLES, 0, m_uVertexCount, 250);
		m_uRenderCalls++;
	}

	glUniform1i(gl_nInstances, nRemainders);
	glUniformMatrix4fv(m4ToWorld, nRemainders, GL_FALSE, &a_fMatrixArray[nSections * 250 * 16]);
	glDrawArraysInstanced(GL_TRIANGLES, 0, m_uVertexCount, nRemainders);
	m_uRenderCalls++;
	//For the remainder
	glDisable(GL_TEXTURE2);
	glDisable(GL_TEXTURE1);
	glDisable(GL_TEXTURE0);

	glBindVertexArray(0);
}