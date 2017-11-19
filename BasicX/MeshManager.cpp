#include "BasicX\Mesh\MeshManager.h"
using namespace BasicX;
//  MeshManager
MeshManager* MeshManager::m_pInstance = nullptr;
void MeshManager::Init(void)
{
	//Get singletons instance
	m_pShaderMngr = ShaderManager::GetInstance();
	m_pMatMngr = MaterialManager::GetInstance();
	m_pLightMngr = LightManager::GetInstance();
	m_pCameraMngr = CameraManager::GetInstance();
	m_pText = Text::GetInstance();

	GenerateSkybox();
	GenerateCube(1.0f);
	GenerateCone(1.0f, 1.0f, 12);
	GenerateCylinder(1.0f, 1.0f, 12);
	GenerateTube(1.0f, 0.6f, 1.0f, 12);
	GeneratePlane(1.0f);
	GenerateSphere(1.0f, 6);
	GenerateTorus(1.0f, 0.6f, 12, 12);
}
void MeshManager::Release(void)
{
	m_pShaderMngr = nullptr;
	m_pMatMngr = nullptr;
	m_pLightMngr = nullptr;
	m_pCameraMngr = nullptr;
	uint uMeshCount = m_meshList.size();
	for (uint i = 0; i < uMeshCount; ++i)
	{
		Mesh* pMesh = m_meshList[i];
		if (pMesh)
		{
			delete pMesh;
			pMesh = nullptr;
		}
	}
	for (uint i = 0; i < uMeshCount; ++i)
	{
		std::vector<MeshOptions>* meshOptions = m_renderOptionsList[i];
		if (meshOptions)
		{
			delete meshOptions;
			meshOptions = nullptr;
		}
	}
	m_renderOptionsList.clear();
	m_meshNames.clear();
}
MeshManager* MeshManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MeshManager();
	}
	return m_pInstance;
}
void MeshManager::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//The big 3
MeshManager::MeshManager() { Init(); }
MeshManager::MeshManager(MeshManager const& other) { }
MeshManager& MeshManager::operator=(MeshManager const& other) { return *this; }
MeshManager::~MeshManager() { Release(); };
//---Text
void MeshManager::Print(String a_sInput, vector3 a_v3Color)
{
	m_pText->AddString(a_sInput, a_v3Color);
}
void MeshManager::PrintLine(String a_sInput, vector3 a_v3Color)
{
	m_pText->AddString(a_sInput + "\n", a_v3Color);
}
void MeshManager::Printf(vector3 a_v3Color, const char * _Format, ...)
{
	char* zs = nullptr;
	zs = new char[1000];
	va_list args;
	va_start(args, _Format);
	vsprintf_s(zs, 1000, _Format, args);
	va_end(args);
	m_pText->AddString(String(zs), a_v3Color);
	SafeDelete(zs);
}
void MeshManager::SetFont(String a_sTextureName)
{
	m_pText->SetFont(a_sTextureName);
}
//--- Non Standard Singleton Methods
int MeshManager::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GeneratePlane(a_fSize, a_v3Color);
	pMesh->SetShaderProgram("BasicColor");
	return AddMesh(pMesh);
}
int MeshManager::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCube(a_fSize, a_v3Color);
	pMesh->SetShaderProgram("BasicColor");
	return AddMesh(pMesh);
}
int MeshManager::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCuboid(a_v3Dimensions, a_v3Color);
	pMesh->SetShaderProgram("BasicColor");
	return AddMesh(pMesh);
}
int MeshManager::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCone(a_fRadius, a_fHeight, a_nSubdivisions, a_v3Color);
	pMesh->SetShaderProgram("BasicColor");
	return AddMesh(pMesh);
}
int MeshManager::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateCylinder(a_fRadius, a_fHeight, a_nSubdivisions, a_v3Color);
	pMesh->SetShaderProgram("BasicColor");
	return AddMesh(pMesh);
}
int MeshManager::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateTube(a_fOuterRadius, a_fInnerRadius, a_fHeight, a_nSubdivisions, a_v3Color);
	pMesh->SetShaderProgram("BasicColor");
	return AddMesh(pMesh);
}
int MeshManager::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeight, int a_nSubdivisionAxis, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateTorus(a_fOuterRadius, a_fInnerRadius, a_nSubdivisionHeight, a_nSubdivisionAxis, a_v3Color);
	pMesh->SetShaderProgram("BasicColor");
	return AddMesh(pMesh);
}
int MeshManager::GenerateSphere(float a_fDiameter, int a_nSubdivisions, vector3 a_v3Color)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateSphere(a_fDiameter, a_nSubdivisions, a_v3Color);
	pMesh->SetShaderProgram("BasicColor");
	return AddMesh(pMesh);
}
int MeshManager::GenerateSkybox(void)
{
	Mesh* pMesh = new Mesh();
	pMesh->GenerateSkybox();
	return AddMesh(pMesh);
}
std::vector<String> MeshManager::GetMeshNames(void)
{
	//for each element in map
	std::vector<String> lNames;

	for (auto it = m_meshList.begin(); it != m_meshList.end(); ++it)
	{
		lNames.push_back((*it)->GetName());
	}

	return lNames;
}
int MeshManager::InstantiateMesh(uint a_uMeshIndex, String a_sNameNewInstance)
{
	if (a_uMeshIndex < m_meshList.size())
	{
		Mesh* pCopy = new Mesh();
		pCopy->Instantiate(m_meshList[a_uMeshIndex]);
		while (GetMesh(a_sNameNewInstance))
		{
			a_sNameNewInstance = a_sNameNewInstance + std::to_string(pCopy->GetUniqueIdentifier());
		}
		pCopy->SetName(a_sNameNewInstance);
		return AddMesh(pCopy);
	}
	return -1;
}
void MeshManager::AddPlaneToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Get the index based on the name
	int nMeshIndex = 5;
	if (a_v3Color != C_WHITE)
	{
		//Get the name of the object
		String sName = "plane_(" + std::to_string(a_v3Color.x) +
			"," + std::to_string(a_v3Color.y) +
			"," + std::to_string(a_v3Color.z) + ")";
		nMeshIndex = GetMeshIndex(sName);
		//If the object does not exist create it
		if (nMeshIndex < 0)
		{
			int nIndex = GeneratePlane(1.0f, a_v3Color);
			if (nIndex < 0) //if I could not make the mesh return
				return;
		}
	}
	// add an instance of the object to the pile
	AddMeshToRenderList(nMeshIndex, a_m4ToWorld, a_Render);

	return;
}
void MeshManager::AddCubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Get the index based on the name
	int nMeshIndex = 1;
	if (a_v3Color != C_WHITE)
	{
		//Get the name of the object
		String sName = "cube_(" + std::to_string(a_v3Color.x) +
			"," + std::to_string(a_v3Color.y) +
			"," + std::to_string(a_v3Color.z) + ")";
		nMeshIndex = GetMeshIndex(sName);
		//If the object does not exist create it
		if (nMeshIndex < 0)
		{
			int nIndex = GenerateCube(1.0f, a_v3Color);
			if (nIndex < 0) //if I could not make the mesh return
				return;
		}
	}
	// add an instance of the object to the pile
	AddMeshToRenderList(nMeshIndex, a_m4ToWorld, a_Render);

	return;
}
void MeshManager::AddConeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Get the index based on the name
	int nMeshIndex = 2;
	if (a_v3Color != C_WHITE)
	{
		//Get the name of the object
		String sName = "cone_(" + std::to_string(a_v3Color.x) +
			"," + std::to_string(a_v3Color.y) +
			"," + std::to_string(a_v3Color.z) + ")";
		nMeshIndex = GetMeshIndex(sName);
		//If the object does not exist create it
		if (nMeshIndex < 0)
		{
			int nIndex = GenerateCone(1.0f, 1.0f, 12, a_v3Color);
			if (nIndex < 0) //if I could not make the mesh return
				return;
		}
	}
	// add an instance of the object to the pile
	AddMeshToRenderList(nMeshIndex, a_m4ToWorld, a_Render);

	return;
}
void MeshManager::AddCylinderToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Get the index based on the name
	int nMeshIndex = 3;
	if (a_v3Color != C_WHITE)
	{
		//Get the name of the object
		String sName = "cylinder_(" + std::to_string(a_v3Color.x) +
			"," + std::to_string(a_v3Color.y) +
			"," + std::to_string(a_v3Color.z) + ")";
		nMeshIndex = GetMeshIndex(sName);
		//If the object does not exist create it
		if (nMeshIndex < 0)
		{
			int nIndex = GenerateCylinder(1.0f, 1.0f, 12, a_v3Color);
			if (nIndex < 0) //if I could not make the mesh return
				return;
		}
	}
	// add an instance of the object to the pile
	AddMeshToRenderList(nMeshIndex, a_m4ToWorld, a_Render);

	return;
}
void MeshManager::AddTubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Get the index based on the name
	int nMeshIndex = 4;
	if (a_v3Color != C_WHITE)
	{
		//Get the name of the object
		String sName = "tube_(" + std::to_string(a_v3Color.x) +
			"," + std::to_string(a_v3Color.y) +
			"," + std::to_string(a_v3Color.z) + ")";
		nMeshIndex = GetMeshIndex(sName);
		//If the object does not exist create it
		if (nMeshIndex < 0)
		{
			int nIndex = GenerateTube(1.0f, 0.6f, 1.0f, 12, a_v3Color);
			if (nIndex < 0) //if I could not make the mesh return
				return;
		}
	}
	// add an instance of the object to the pile
	AddMeshToRenderList(nMeshIndex, a_m4ToWorld, a_Render);

	return;
}
void MeshManager::AddTorusToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Get the index based on the name
	int nMeshIndex = 7;
	if (a_v3Color != C_WHITE)
	{
		//Get the name of the object
		String sName = "torus_(" + std::to_string(a_v3Color.x) +
			"," + std::to_string(a_v3Color.y) +
			"," + std::to_string(a_v3Color.z) + ")";
		nMeshIndex = GetMeshIndex(sName);
		//If the object does not exist create it
		if (nMeshIndex < 0)
		{
			int nIndex = GenerateTorus(1.0f, 0.6f, 12, 12, a_v3Color);
			if (nIndex < 0) //if I could not make the mesh return
				return;
		}
	}
	// add an instance of the object to the pile
	AddMeshToRenderList(nMeshIndex, a_m4ToWorld, a_Render);

	return;
}
void MeshManager::AddSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render)
{
	//Get the index based on the name
	int nMeshIndex = 6;
	if (a_v3Color != C_WHITE)
	{
		//Get the name of the object
		String sName = "sphere_(" + std::to_string(a_v3Color.x) +
			"," + std::to_string(a_v3Color.y) +
			"," + std::to_string(a_v3Color.z) + ")";
		nMeshIndex = GetMeshIndex(sName);
		//If the object does not exist create it
		if (nMeshIndex < 0)
		{
			int nIndex = GenerateSphere(1.0f, 6, a_v3Color);
			if (nIndex < 0) //if I could not make the mesh return
				return;
		}
	}
	// add an instance of the object to the pile
	AddMeshToRenderList(nMeshIndex, a_m4ToWorld, a_Render);

	return;
}
void MeshManager::AddSkyboxToRenderList(String a_sFileName)
{
	if (a_sFileName == "")
		return;

	String sName = "Skybox_" + a_sFileName;
	int nMeshIndex = GetMeshIndex(sName);
	/*
	if the mesh does not exist we will need to generate a new instance
	and change the material of that instance
	*/
	if (nMeshIndex < 0)
	{
		nMeshIndex = GetMeshIndex("Skybox_Skybox.png");
		//if the mesh for the skybox does not exist do nothing
		if (nMeshIndex < 0)
			return;

		Mesh* pOriginal = m_meshList[nMeshIndex];
		Mesh* pMesh = new Mesh();
		pMesh->Instantiate(pOriginal);
		pMesh->SetMaterial(sName, a_sFileName);
		pMesh->SetShaderProgram("Skybox");
		pMesh->SetName(sName);
		nMeshIndex = AddMesh(pMesh);
	}

	AddMeshToRenderList(nMeshIndex, IDENTITY_M4);
	return;
}
int MeshManager::GetMeshIndex(Mesh* a_pMesh)
{
	uint uMeshCount = m_meshList.size();
	//Check for each mesh in the mesh list if the provided mesh is in the list
	for (uint nMesh = 0; nMesh < uMeshCount; ++nMesh)
	{
		//if it is in the list return the index
		if (m_meshList[nMesh] == a_pMesh)
			return nMesh;
	}
	//not found
	return -1;
}

int MeshManager::AddMesh(Mesh* a_pMesh)
{
	//check if empty pointer
	if (!a_pMesh)
		return -1;

	//if the mesh is already in the list return the index

	int nMesh = GetMeshIndex(a_pMesh);
	if (nMesh > 0)
		return nMesh;

	String sName = a_pMesh->GetName();
	while (GetMeshIndex(sName) >= 0)
	{
		sName = sName + std::to_string(a_pMesh->GetUniqueIdentifier());
	}
	a_pMesh->SetName(sName);
	m_meshList.push_back(a_pMesh);
	std::vector<MeshOptions>* meshOptions = new std::vector<MeshOptions>();
	m_renderOptionsList.push_back(meshOptions);
	m_meshNames[a_pMesh->GetName()] = m_meshList.size() - 1;
	return m_meshList.size() - 1;
}
Mesh* MeshManager::GetMesh(String a_sName)
{
	int nIndex = GetMeshIndex(a_sName);
	return GetMesh(nIndex);
}
Mesh *MeshManager::GetMesh(uint nMesh)
{
	if (nMesh >= m_meshList.size())
		return nullptr;
	return m_meshList[nMesh];
}
uint MeshManager::GetMeshCount(void) { return m_meshList.size(); }

void MeshManager::SetRenderTarget(GLuint a_uFrameBuffer, GLuint a_uDepthBuffer, GLuint a_uTextureToRender, int a_nWidth, int a_nHeight)
{
	//Set the frame buffer active
	glBindFramebuffer(GL_FRAMEBUFFER, a_uFrameBuffer);

	//Texture to render to
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, a_uTextureToRender);

	glBindRenderbuffer(GL_RENDERBUFFER, a_uDepthBuffer);

	SystemSingleton* pSystem = SystemSingleton::GetInstance();

	int nWidth = a_nWidth;
	if (nWidth < 0)
		nWidth = pSystem->GetWindowWidth();

	int nHeight = a_nHeight;
	if (nHeight < 0)
		nHeight = pSystem->GetWindowHeight();

	glViewport(static_cast<GLint>(0),
		static_cast<GLint>(0),
		static_cast<GLint>(nWidth),
		static_cast<GLint>(nHeight));
}
int MeshManager::GetMeshIndex(String a_sName)
{
	//look for the mesh by name in map
	auto var = m_meshNames.find(a_sName);
	//if found return it
	if (var != m_meshNames.end())
		return var->second;
	//if not available return not found
	return -1;
}
void MeshManager::ClearRenderList(void)
{
	for (auto it = m_renderOptionsList.begin(); it != m_renderOptionsList.end(); ++it)
	{
		(*it)->clear();
	}
	Mesh::ResetRenderCallCount();
}
void MeshManager::CompileMesh(uint a_nMeshIndex)
{
	if (a_nMeshIndex >= m_meshList.size())
		return;
	m_meshList[a_nMeshIndex]->CompileOpenGL3X();
}
void MeshManager::AddMeshToRenderList(uint a_nIndex, matrix4 a_m4Transform, int a_Render)
{
	//Id the index is larger than the number of meshes we know about return
	if (a_nIndex >= m_meshList.size())
		return;

	//we create a new options object and store the information provided
	MeshOptions options(a_m4Transform, a_Render);

	//Get the list of options for this mesh
	//std::vector<MeshOptions>* optionsList = m_MeshOptionsList[a_nIndex];
	//optionsList->push_back(options);
	(m_renderOptionsList[a_nIndex])->push_back(options);
	/*
	//look the map to see if we have options for the specified mesh
	auto var = m_mRender.find(a_sMeshName);
	//if we found the mesh in the map
	if (var != m_mRender.end())
	{
	lOptions = var->second; //we get the existing options for that mesh
	}
	else //this entry on the map was not allocated yet
	{
	lOptions = new std::vector<MeshOptions>(); //so we allocate new space for it
	}
	//we add the new options to the list (if it was empty this will be the first entry)
	lOptions->push_back(options);
	//we assign the transform to the place in the map
	m_mRender[a_sMeshName] = lOptions;
	*/
}
void MeshManager::AddMeshToRenderList(String a_sMeshName, matrix4 a_m4Transform, int a_Render)
{
	int nMeshIndex = GetMeshIndex(a_sMeshName);
	if (nMeshIndex < 0)
		return;

	AddMeshToRenderList(nMeshIndex, a_m4Transform, a_Render);
}
void MeshManager::AddMeshToRenderList(Mesh* a_pMesh, matrix4 a_m4Transform, int a_Render)
{
	if (!a_pMesh)
		return;
	AddMeshToRenderList(a_pMesh->GetName(), a_m4Transform, a_Render);

	/*
	//we create a new options object and store the information provided
	MeshOptions options;
	options.m_m4Transform = a_m4Transform;
	options.m_nRender = a_Render;

	//Get the vector of options from the map for this mesh
	std::vector<MeshOptions>* lOptions;
	//look the map to see if we have options for the specified mesh
	auto var = m_mRender.find(a_pMesh->GetName());
	//if we found the mesh in the map
	if (var != m_mRender.end())
	{
	lOptions = var->second; //we get the existing options for that mesh
	}
	else //this entry on the map was not allocated yet
	{
	lOptions = new std::vector<MeshOptions>(); //so we allocate new space for it
	}
	//we add the new options to the list (if it was empty this will be the first entry)
	lOptions->push_back(options);
	//we assign the transform to the place in the map
	m_mRender[a_pMesh->GetName()] = lOptions;
	*/
}
uint MeshManager::Render(void)
{
	//for each element in map check the rendering type
	uint nMeshCount = m_meshList.size();
	std::vector<matrix4> solidList;
	std::vector<matrix4> wireList;
	std::vector<matrix4> bothList;
	std::vector<MeshOptions>* optionList;
	for (uint nMesh = 0; nMesh < nMeshCount; ++nMesh)
	{
		optionList = m_renderOptionsList[nMesh];
		if (optionList->size() > 0)
		{
			//The idea is to know what each mesh will be rendered as and store the matrix in a list
			//that way we will have 3 separate calls each for a render mode
			for (uint nOpt = 0; nOpt < optionList->size(); ++nOpt)
			{
				switch ((*optionList)[nOpt].m_nRender)
				{
				case RENDER_NONE:
					break;
				case RENDER_SOLID:
					solidList.push_back((*optionList)[nOpt].m_m4Transform);
					break;
				case RENDER_WIRE:
					wireList.push_back((*optionList)[nOpt].m_m4Transform);
					break;
				default:
					bothList.push_back((*optionList)[nOpt].m_m4Transform);
					break;
				}
			}
			//For Solids ---------------------------------------------------------------------------
			int nSolids = solidList.size();//count elements
			if (nSolids > 0)
			{
				float* fSolidArray = new float[16 * nSolids];//reserve memory
															 //memcpy the translated values to the array (way faster than copy element by element)
				for (int nSolid = 0; nSolid < nSolids; ++nSolid)
				{
					const float* m4MVP = glm::value_ptr(solidList[nSolid]);
					memcpy(&fSolidArray[nSolid * 16], m4MVP, 16 * sizeof(float));
				}
				//render
				m_meshList[nMesh]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(),
					fSolidArray, solidList.size(), m_pCameraMngr->GetPosition(), RENDER_SOLID);
				//deallocate memory
				if (fSolidArray)
				{
					delete[] fSolidArray;
					fSolidArray = nullptr;
				}
				solidList.clear();
			}
			//For Wires ---------------------------------------------------------------------------
			int nWires = wireList.size();//count elements
			if (nWires > 0)
			{
				float* fWireArray = new float[16 * nWires];//reserve memory
														   //memcpy the translated values to the array (way faster than copy element by element)
				for (int nWire = 0; nWire < nWires; ++nWire)
				{
					const float* m4MVP = glm::value_ptr(wireList[nWire]);
					memcpy(&fWireArray[nWire * 16], m4MVP, 16 * sizeof(float));
				}
				//render
				m_meshList[nMesh]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(),
					fWireArray, wireList.size(), m_pCameraMngr->GetPosition(), RENDER_WIRE);
				//deallocate memory
				if (fWireArray)
				{
					delete[] fWireArray;
					fWireArray = nullptr;
				}
				wireList.clear();
			}
			//For Both ---------------------------------------------------------------------------
			int nBoths = bothList.size();//count elements
			if (nBoths > 0)
			{
				float* fBothArray = new float[16 * nBoths];//reserve memory
														   //memcpy the translated values to the array (way faster than copy element by element)
				for (int nBoth = 0; nBoth < nBoths; ++nBoth)
				{
					const float* m4MVP = glm::value_ptr(bothList[nBoth]);
					memcpy(&fBothArray[nBoth * 16], m4MVP, 16 * sizeof(float));
				}
				//render
				m_meshList[nMesh]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(),
					fBothArray, bothList.size(), m_pCameraMngr->GetPosition(), RENDER_SOLID | RENDER_WIRE);
				//deallocate memory
				if (fBothArray)
				{
					delete[] fBothArray;
					fBothArray = nullptr;
				}
				bothList.clear();
			}
		}
	}
	m_pText->Render();
	return Mesh::GetRenderCallCount();
}