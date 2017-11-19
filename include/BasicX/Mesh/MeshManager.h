/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __BASICXMESHMANAGER_H_
#define __BASICXMESHMANAGER_H_
#include "BasicX\Mesh\Mesh.h"
#include "BasicX\Camera\CameraManager.h"
#include "BasicX\Mesh\Text.h"

namespace BasicX
{
	//MeshManager
	class BasicXDLL MeshManager
	{
		std::vector<Mesh*> m_meshList; //Lit of all the meshes added to the system
		std::map<String, uint> m_meshNames; //map of Meshes names and corresponding indices
		std::vector<std::vector<MeshOptions>*> m_renderOptionsList; //list of options, one for each mesh -> one for each render call

		static MeshManager* m_pInstance; // Singleton pointer
		ShaderManager* m_pShaderMngr = nullptr;	//Shader Manager
		MaterialManager* m_pMatMngr = nullptr;		//Material Manager
		LightManager* m_pLightMngr = nullptr;		//Light Manager
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
		OUTPUT: name of the generated Mesh
		*/
		int GeneratePlane(float a_fSize, vector3 a_v3Color = C_WHITE);
		/*
		USAGE: Generates a cube
		ARGUMENTS:
		float a_fSize -> Size of each side
		vector3 a_v3Color -> Color of the mesh
		OUTPUT: name of the generated Mesh
		*/
		int GenerateCube(float a_fSize, vector3 a_v3Color = C_WHITE);
		/*
		USAGE: Generates a cuboid
		ARGUMENTS:
		vector3 a_v3Dimensions -> Dimensions of each side of the cuboid
		vector3 a_v3Color -> Color of the mesh
		OUTPUT: name of the generated Mesh
		*/
		int GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color = C_WHITE);
		/*
		USAGE:Generates a cone mesh
		ARGUMENTS:
		float a_fRadius -> radius
		float a_fHeight -> how tall is the mesh
		int a_nSubdivisions -> divisions of the cap
		vector3 a_v3Color -> Color of the mesh
		OUTPUT: name of the generated Mesh
		*/
		int GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
		/*
		USAGE: Generates a cylinder mesh
		ARGUMENTS:
		float a_fRadius -> radius
		float a_fHeight -> how tall is the mesh
		int a_nSubdivisions -> divisions on the cap
		vector3 a_v3Color -> Color of the mesh
		OUTPUT: name of the generated Mesh
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
		OUTPUT: name of the generated Mesh
		*/
		int GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
		/*
		USAGE: Generates a torus mesh
		ARGUMENTS:
		float a_fOuterRadius -> Outer radius
		float a_fInnerRadius -> Inner Radius
		int a_nSubdivisionHeight -> divisions vertical
		int a_nSubdivisionAxis -> divisions along the roundness of the mesh
		a_v3Color -> Color of the mesh
		OUTPUT: name of the generated Mesh
		*/
		int GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeight, int a_nSubdivisionAxis, vector3 a_v3Color = C_WHITE);
		/*
		USAGE: Generates a Sphere mesh
		ARGUMENTS:
		float a_fDiameter -> diameter of the sphere (radius times 2)
		int a_nSubdivisions -> Number of divisions, not a lot of difference in shapes larger than 3 subd
		a_v3Color -> Color of the mesh
		OUTPUT: name of the generated Mesh
		*/
		int GenerateSphere(float a_fDiameter, int a_nSubdivisions, vector3 a_v3Color = C_WHITE);
		/*
		USAGE: Generates a skybox using the skybox.png file from data folder
		ARGUMENTS:
		OUTPUT: name of the generated Mesh
		*/
		int GenerateSkybox(void);
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
		OUTPUT: ---
		*/
		void AddPlaneToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
		/*
		USAGE: Renders the cube on the specified position
		ARGUMENTS:
		OUTPUT: returns the name of the mesh that will render
		*/
		void AddCubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
		/*
		USAGE: Renders the cone on the specified position
		ARGUMENTS:
		OUTPUT: returns the name of the mesh that will render
		*/
		void AddConeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
		/*
		USAGE: Renders the cylinder on the specified position
		ARGUMENTS:
		OUTPUT: returns the name of the mesh that will render
		*/
		void AddCylinderToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
		/*
		USAGE: Renders the tube on the specified position
		ARGUMENTS:
		OUTPUT: returns the name of the mesh that will render
		*/
		void AddTubeToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
		/*
		USAGE: Renders the torus on the specified position
		ARGUMENTS:
		OUTPUT: returns the name of the mesh that will render
		*/
		void AddTorusToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
		/*
		USAGE: Renders the sphere on the specified position
		ARGUMENTS:
		OUTPUT: returns the name of the mesh that will render
		*/
		void AddSphereToRenderList(matrix4 a_m4ToWorld, vector3 a_v3Color, int a_Render = RENDER_SOLID);
		/*
		USAGE: This add a giant inwards box to the scene at the origin which will translate along
		the camera use the argument to change the texture rendered
		ARGUMENTS:
		String a_sFileName -> name of the file to add
		OUTPUT: returns the name of the mesh that will render
		*/
		void AddSkyboxToRenderList(String a_sFileName = "Skybox.png");
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

}
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
#endif //__MESHMANAGERSINGLETON_H_