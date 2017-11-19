/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
Modified: 2017/06
----------------------------------------------*/
#ifndef __SIMPLEXMESHMANAGER_H_
#define __SIMPLEXMESHMANAGER_H_
#include "Simplex\Mesh\Mesh.h"
#include "Simplex\Camera\CameraManager.h"
#include "Simplex\Mesh\Text.h"

namespace Simplex
{

//MeshManager singleton
class SimplexDLL MeshManager
{
	std::vector<Mesh*> m_meshList; //Lit of all the meshes added to the system
	std::map<String, uint> m_meshNames; //map of Meshes names and corresponding indices
	std::vector<std::vector<MeshOptions>*> m_renderOptionsList; //list of options, one for each mesh -> one for each render call

	static MeshManager* m_pInstance; // Singleton pointer
	ShaderManager* m_pShaderMngr = nullptr;	//Shader Manager
	MaterialManager* m_pMatMngr = nullptr;	//Material Manager
	LightManager* m_pLightMngr = nullptr;	//Light Manager
	CameraManager* m_pCameraMngr = nullptr;	//Camera Manager
	Text* m_pText; //Text Singleton
public:
	//Singleton Methods
	/*
	USAGE: Gets/Constructs the singleton pointer
	ARGUMENTS:
	OUTPUT:
	*/
	static MeshManager* GetInstance();
	/*
	USAGE: Destroys the singleton
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/*
	USAGE: Adds a mesh to the list of meshes
	ARGUMENTS: Mesh* a_pMesh -> mesh to add
	OUTPUT: index of the mesh in the list, if -1 there was an error
	*/
	int AddMesh(Mesh* a_pMesh);
	/*
	USAGE: Gets the Mesh pointer from the map by name; 
	WARNING: DO NOT change the name of the mesh or it will lose its position in map
			 DO NOT delete the pointer outside of the manager
	ARGUMENTS: String a_sName -> name of the inquired mesh
	OUTPUT: index of the mesh in the mesh list, -1 if not found
	*/
	int GetMeshIndex(String a_sName);
	/*
	USAGE: Gets the Mesh pointer from the map by name;
	WARNING: DO NOT change the name of the mesh or it will lose its position in map
	DO NOT delete the pointer outside of the manager
	ARGUMENTS: String a_sName -> name of the inquired mesh
	OUTPUT: index of the mesh in the mesh list, -1 if not found
	*/
	int GetMeshIndex(Mesh* a_pMesh);
	/*
	USAGE: Returns the mesh specified by name from the list of Meshes
	ARGUMENTS: String a_sName -> name of the mesh
	OUTPUT: Inquired mesh
	*/
	Mesh* GetMesh(String a_sName);
	/*
	USAGE: Returns the mesh specified by index from the list of Meshes
	ARGUMENTS: uint nMesh -> index of the mesh
	OUTPUT: Inquired mesh
	*/
	Mesh* GetMesh(uint nMesh);

	/*
	USAGE: Generates a plane
	ARGUMENTS:
		float a_fSize -> Size of each side
		vector3 a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GeneratePlane(float a_fSize, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a cube
	ARGUMENTS:
		float a_fSize -> Size of each side
		vector3 a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GenerateCube(float a_fSize, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a cuboid
	ARGUMENTS:
		vector3 a_v3Dimensions -> Dimensions of each side of the cuboid
		vector3 a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE:Generates a cone mesh
	ARGUMENTS:
		float a_fRadius -> radius
		float a_fHeight -> how tall is the mesh
		int a_nSubdivisions -> divisions of the cap
		vector3 a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a cylinder mesh
	ARGUMENTS:
		float a_fRadius -> radius
		float a_fHeight -> how tall is the mesh
		int a_nSubdivisions -> divisions on the cap
		vector3 a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a tube mesh
	ARGUMENTS:
		float a_fOuterRadius -> outer radius
		float a_fInnerRadius -> inner radius
		float a_fHeight -> how tall is the mesh
		int a_nSubdivisions -> divisions on the cap
		a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a torus mesh
	ARGUMENTS:
	-	float a_fOuterRadius -> Outer radius
	-	float a_fInnerRadius -> Inner Radius
	-	int a_nSubdivisionHeight -> divisions vertical
	-	int a_nSubdivisionAxis -> divisions along the roundness of the mesh
	-	a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeight, int a_nSubdivisionAxis, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a Sphere mesh
	ARGUMENTS:
	-	float a_fRadius -> radius of the sphere
	-	int a_nSubdivisions -> Number of divisions, not a lot of difference in shapes larger than 3 subd
	-	a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates an IsoSphere mesh
	ARGUMENTS:
	-	float a_fRadius -> radius of the sphere
	-	int a_nSubdivisions -> Number of divisions, not a lot of difference in shapes larger than 3 subd
	-	a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GenerateIsoSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates an IcoSphere mesh
	ARGUMENTS:
	-	float a_fRadius -> radius of the sphere
	-	int a_nSubdivisions -> Number of divisions, not a lot of difference in shapes larger than 3 subd
	-	a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GenerateIcoSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates an WireCube mesh
	ARGUMENTS:
	-	float a_fSize -> Size of the cube
	-	a_v3Color -> Color of the mesh
	OUTPUT: index of the generated Mesh
	*/
	int GenerateWireCube(float a_fSize, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates an WireSphere mesh
	ARGUMENTS:
	-	float a_fRadius -> radius of the sphere
	-	a_v3Color -> Color of the mesh
	OUTPUT: name of the generated Mesh
	*/
	int GenerateWireSphere(float a_fRadius, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Generates a skybox using the skybox.png file from data folder
	ARGUMENTS: ---
	OUTPUT: index of the generated Mesh
	*/
	int GenerateSkybox(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	int GenerateLine(vector3 a_v3Start, vector3 a_v3End, vector3 a_v3ColorStart, vector3 a_v3ColorEnd);
	/*
	USAGE: will return all the names already stored in the mesh list
	ARGUMENTS: ---
	OUTPUT: Names in map
	*/
	std::vector<String> GetMeshNames(void);
	/*
	USAGE: Instantiate a new mesh based on the provided name
	ARGUMENTS: 
		String a_sName -> Name of the mesh to instantiate
		String a_sNameNewInstance -> Name of the new instance
	OUTPUT: String -> Name applied to the instance, "" if not found
	*/
	int InstantiateMesh(uint a_uMeshIndex, String a_sNameNewInstance);
	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddPlaneToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddCubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders the cone on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddConeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders the cylinder on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddCylinderToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders the tube on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddTubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders the torus on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddTorusToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders the sphere on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders an IcoSphere on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddIcoSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders an IsoSphere on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddIsoSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders an WireCube on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddWireCubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders an WireSphere on the specified position
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to render the primitive onto
	-	vector3 a_v3Color -> Color to render the solid part of the primitive
	-	int a_Render = RENDER_SOLID -> Render options RENDER_SOLID | RENDER_WIRE
	OUTPUT: ---
	*/
	void AddWireSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
	/*
	USAGE: Renders a line in the specified positions and colors
	ARGUMENTS:
	-	matrix4 a_m4ToWorld -> Space to draw the primitive onto
	-	vector3 a_v3Start -> Start point in local space
	-	vector3 a_v3End -> End point in local space
	-	vector3 a_v3ColorStart -> Color of the start point
	-	vector3 a_v3ColorEnd -> Color of the end point
	OUTPUT: ---
	*/
	void AddLineToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Start, vector3 a_v3End, vector3 a_v3ColorStart, vector3 a_v3ColorEnd);
	/*
	USAGE: This add a giant inwards box to the scene at the origin which will translate along
		the camera use the argument to change the texture rendered
	ARGUMENTS:
		String a_sFileName -> name of the file to add
	OUTPUT: returns the name of the mesh that will render
	*/
	void AddSkyboxToRenderList(String a_sFileName = "Skybox.png");
	/*
	USAGE: Render an axis on the specified position
	ARGUMENTS: matrix4 a_m4ToWorld -> space on which the axis will be rendered
	OUTPUT: ---
	*/
	void AddAxisToRenderList(matrix4 a_m4ToWorld);
	/*
	USAGE: Render a grid on the specified position
	ARGUMENTS: matrix4 a_m4ToWorld -> space on which the grid will be rendered
	OUTPUT: ---
	*/
	void AddGridToRenderList(matrix4 a_m4ToWorld);
	/*
	USAGE: Render a grid based on the active camera's mode
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void AddGridToRenderList();
	/*
	USAGE: Render a visual representation of the camera
	ARGUMENTS: int a_nIndex = -1 -> camera index, if less than 0 all cameras will be rendered
	OUTPUT: ---
	*/
	void AddCameraToRenderList(int a_nIndex = -1);
	/*
	USAGE: Finds the specified mesh and speficies a transform to display
	ARGUMENTS:
		uint a_nIndex -> index of the mesh to apply transform to
		matrix4 a_m4Transform -> transform to apply
		int a_Render = SOLID -> render options SOLID | WIRE
	OUTPUT: returns the name of the mesh that will render
	*/
	void AddMeshToRenderList(uint a_nIndex, matrix4 a_m4Transform, int a_Render = RENDER_SOLID);
	/*
	USAGE: Applies a transform to display to the specified mesh by name, the mesh will be
	lookout	for in the map of meshes, using the mesh index if know will result in faster
	additions
	ARGUMENTS:
	Strin a_sMeshName -> mesh to apply transform to
	matrix4 a_m4Transform -> transform to apply
	int a_Render = SOLID -> render options SOLID | WIRE
	OUTPUT: returns the name of the mesh that will render
	*/
	void AddMeshToRenderList(String a_sMeshName, matrix4 a_m4Transform, int a_Render = RENDER_SOLID);
	/*
	USAGE: Applies a transform to display to the specified mesh, the mesh will be lookout
	for in the map of meshes, using the mesh index if know will result in faster additions
	ARGUMENTS:
	Mesh* a_pMesh -> mesh to apply transform to
	matrix4 a_m4Transform -> transform to apply
	int a_Render = SOLID -> render options SOLID | WIRE
	OUTPUT: returns the name of the mesh that will render
	*/
	void AddMeshToRenderList(Mesh* a_pMesh, matrix4 a_m4Transform, int a_Render = RENDER_SOLID);
	/*
	USAGE: Clears the map of transforms
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearRenderList(void);
	/*
	USAGE: Draws all the meshes in the transform map
	ARGUMENTS: ---
	OUTPUT: number of render calls
	*/
	uint Render(void);
	/*
	USAGE: Get the number of meshes in the mesh manager
	ARGUMENTS: ---
	OUTPUT: number of meshes
	*/
	uint GetMeshCount(void);
	/*
	USAGE: Sets where the objects are going to be rendered
	ARGUMENTS:
	GLuint a_FrameBuffer = 0 -> Where to render, 0 for the window
	GLuint a_TextureToRender = 0 -> Texture to render onto
	OUTPUT: ---
	*/
	void SetRenderTarget(GLuint a_uFrameBuffer = 0, GLuint a_uDepthBuffer = 0, GLuint a_uTextureToRender = 0, int a_nWidth = -1, int a_nHeight = -1);
	/*
	USAGE: Will compile the mesh specified by the mesh index
	ARGUMENTS: uint a_nMeshIndex -> mesh to compile
	OUTPUT: ---
	*/
	void CompileMesh(uint a_nMeshIndex);
	/*
	USAGE: Renders a String in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Print(String a_sInput, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Renders a String Line in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void PrintLine(String a_sInput, vector3 a_v3Color = C_WHITE);
	/*
	USAGE: Renders a char array in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Printf(vector3 a_v3Color, const char * _Format, ...);
	/*
	USAGE: Sets the texture for the font
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFont(String a_sTextureName);
private:
	//Rule of 3
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	MeshManager(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	MeshManager(MeshManager const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	MeshManager& operator=(MeshManager const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MeshManager(void);
	//Other methods
	/*
	USAGE: Initializes the objects fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Releases the objects memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
};

} //namespace Simplex

#endif //__MESHMANAGERSINGLETON_H_
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/