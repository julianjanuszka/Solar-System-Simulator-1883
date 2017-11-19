/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
Modified: 2017/06
----------------------------------------------*/
#ifndef __SimplexGroup_H_
#define __SimplexGroup_H_

#include "Simplex\System\SystemSingleton.h"
#include "Simplex\Mesh\MeshManager.h"
#include "Simplex\Animation\Frame.h"
#include "Simplex\Animation\Animation.h"

namespace Simplex
{

//Group Class
class SimplexDLL Group
{
	String m_sName = ""; //name of the group
	String m_sParent = ""; //parent's name
	Group* m_pParent = nullptr; //pointer to the parent
	Group* m_pOriginal = nullptr; //points to the group this is instanced from.
	bool m_bGlobalized = false;	//Global coordinates flag
	uint m_uFrameCount = 1; //number of frames in this group
	vector3 m_v3Pivot;		//Point in which the point is going to rotate around
	matrix4* m_pToWorld; //List of transformations of the group to global scale (one per frame)
	Frame* m_pFrame = nullptr; //List of frames of animation in the group

	std::vector<uint> m_meshList;//List of meshes that makes the model they correspond to the index in the mesh manager
	std::vector<std::vector<MeshOptions>*> m_renderOptionsList;	//list of MeshOptions (one for each mesh)
		//(one for each time this mesh will be called to render) the same mesh can appear more than once in the group
		//with the same or different options therefore the need of a list of lists
	ShaderManager* m_pShaderMngr = nullptr;	//Shader Manager
	MaterialManager* m_pMatMngr = nullptr;		//Material Manager
	LightManager* m_pLightMngr = nullptr;		//Light Manager
	CameraManager* m_pCameraMngr = nullptr;	//Camera Manager
	MeshManager* m_pMeshMngr = nullptr;			//Mesh Manager

public:
	/*
	USAGE: Will calculate the transformations of each frame of the group
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ComputeTransforms(void);
	/*
	USAGE: Will interpolate the frames of animation
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Interpolate(void);
	/*
	USAGE: Will set the frame transforms of the specified frame, frames must exist
	ARGUMENTS:
		uint a_nFrame -> frame to store the information into (must exist, if not GenerateFrames() first)
		vector3 a_v3Translation -> translation of the frame
		vector3 a_v3Rotation -> rotation of the frame
		vector3 a_v3Scale -> scale of the frame
		bool a_bVisible -> visibility of the frame
		bool a_bKeyframe -> is this a keyframe?
	OUTPUT: ---
	*/
	void SetFrame(uint a_nFrame, vector3 a_v3Translation, vector3 a_v3Rotation, vector3 a_v3Scale, bool a_bVisible, bool a_bKeyframe);
	/*
	USAGE: Will set the frame transforms of the specified frame, frames must exist
	ARGUMENTS:
		uint a_nFrame -> frame to store the information into (must exist, if not GenerateFrames() first)
		Frame a_frame -> frame to set
	OUTPUT: ---
	*/
	void SetFrame(Frame a_frame, uint a_nFrame);
	
	/*
	USAGE: Will get the total number of frames in the group
	ARGUMENTS:---
	OUTPUT: Frame count
	*/
	uint GetFrameCount(void);
	/*
	USAGE: Will get a copy of the frame specified by index, if out of range will return a new one
	ARGUMENTS: uint a_nFrame -> queried frame index
	OUTPUT: Frame
	*/
	Frame GetFrame(uint a_nFrame);
	/*
	Method: Group
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	Group(void);
	/*
	Method: Group
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	Group(Group const& other);
	/*
	Method: operator=
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	Group& operator=(Group const& other);
	/*
	Method: ~Group
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~Group(void);
	/*
	USAGE: Gets the list of meshes that are part of this model
	ARGUMENTS: ---
	OUTPUT: list of meshes by index of the mesh manager(std::vector<uint>)
	*/
	std::vector<uint> GetMeshList(void);

	/*
	Method: Swap
	Usage: Changes object contents for other object's
	Arguments:
	other -> object to swap content from
	Output: ---
	*/
	void Swap(Group& other);
	/*
	USAGE: Sets the name of the group
	ARGUMENTS: 
		String a_sName -> desired name of the group
	OUTPUT: ---
	*/
	void SetName(String a_sName);
	/*
	USAGE: Returns the name of the Group
	ARGUMENTS: ---
	OUTPUT: name of the mesh
	*/
	String GetName(void);
	/*
	USAGE: Adds a mesh to the map of meshes, it the mesh is already in it will just add it to the group
	without readding it to the list in the group at the specified transform and render options
	ARGUMENTS:
		Mesh* a_pMesh -> mesh to apply transform to
		matrix4 a_m4Transform -> transform to apply
		int a_Render = SOLID -> render options SOLID | WIRE
	OUTPUT: ---
	*/
	void AddMesh(Mesh* a_pMesh, MeshOptions a_otions = MeshOptions());
	/*
	USAGE: Adds a mesh to the map of meshes in the group at the specified transform and render options
	ARGUMENTS:
		uint u_MeshIndex -> mesh to apply transform to
		matrix4 a_m4Transform -> transform to apply
		int a_Render = SOLID -> render options SOLID | WIRE
	OUTPUT: ---
	*/
	void AddMesh(uint u_MeshIndex, MeshOptions a_otions = MeshOptions());
	/*
	USAGE: Adds all the meshes in the group to the mesh manager render list
	ARGUMENTS:
		matrix4 a_m4Transform = IDENTITY_M4 -> Offset transform to apply to the group
		uint a_uFrame = 0 -> frame to display
	OUTPUT: ---
	*/
	void AddRenderToList(matrix4 a_m4Transform = IDENTITY_M4, int a_nFrame = 0);
	/*
	USAGE: Gets the options for the mesh specified by index
	ARGUMENTS: uint a_uMeshOptionsIndex -> Index of the mesh
	OUTPUT: std::vector<MeshOptions>* all the options to render this mesh
	*/
	std::vector<MeshOptions>* GetMeshOptions(uint a_uMeshOptionsIndex);
	/*
	USAGE: Will change the previously loaded material applied to all the meshes
	ARGUMENTS:
	String sMaterialName -> Previously loaded material name
	OUTPUT: ---
	*/
	void ChangeMaterial(String a_sMaterialName);
	/*
	USAGE: Will change the previously loaded material applied to all the meshes
	ARGUMENTS:
	uint a_uMaterialIndex -> Previously loaded material index
	String a_sGroup = "ALL" -> group to apply the change to, if "ALL" will apply it to every group
	OUTPUT: ---
	*/
	void ChangeMaterial(uint a_uMaterialIndex);
	/*
	USAGE: Gets the mesh specified by index
	ARGUMENTS: uint a_nIndex
	OUTPUT: Mesh in the meshList
	*/
	Mesh* GetMesh(uint a_nIndex);
	/*
	USAGE: Will compile all meshes inside the mesh list
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompileMeshList(void);
	/*
	USAGE: Will change the render options for the ones specified for the mesh indicated by index
	ARGUMENTS:
	MeshOptions a_MeshOptions -> options to change | -1 will change it to all meshes in the group
	uint a_nMeshIndex -> mesh in the list to apply changes to
	OUTPUT: ---
	*/
	void ChangeMeshOptions(MeshOptions a_MeshOptions, int a_nMeshIndex = -1);
	/*
	USAGE: Will create new unique materials for the existing group 
	that are a duplicate of the current one, one material per mesh is created.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CreateMaterials(void);
	/*
	USAGE: Will create new unique materials for the existing group
	that are a duplicate of the current one, one material per mesh is created.
	The identifier is attached at the end of the current material one, clones the
	material and assign the new name, if the material has already been created
	it will attach it without making a new one.
	ARGUMENTS: 
		String a_sIdentifier = "_copy" -> Name to be attached at the end of the current material
	OUTPUT: ---
	*/
	void DuplicateMaterialsUnique(String a_sIdentifier = "_copy");
	/*
	USAGE: Will copy the provided group onto this group, creating new meshes in the process
	ARGUMENTS: 
		Group* a_pOriginal -> group to copy from
		bool a_bDuplicateMaterials = false -> create new materials for the meshes?
	OUTPUT: success or failure
	*/
	bool Clone(Group* const a_pOriginal);
	/*
	USAGE: Will copy the provided group onto this group, using the same meshes from the input
	in the process
	ARGUMENTS: Group* a_pOriginal -> group to copy from
	OUTPUT: success or failure
	*/
	bool Instance(Group* const a_pOriginal);
	/*
	USAGE: Sets the parent name
	ARGUMENTS: String a_pParentName -> name of the group that is parent to this
	OUTPUT: ---
	*/
	void SetParentName(String a_pParentName);
	/*
	USAGE: Gets the parent name
	ARGUMENTS: --- 
	OUTPUT: name of the group that is parent to this
	*/
	String GetParentName(void);
	/*
	USAGE: Sets the parent object
	ARGUMENTS: Group* a_pParentName -> group that is parent to this
	OUTPUT: ---
	*/
	void SetParent(Group* a_pParent);
	/*
	USAGE: Gets the parent 
	ARGUMENTS: ---
	OUTPUT: group that is parent to this
	*/
	Group* GetParent(void);
	/*
	USAGE: Set the pivot point to rotate around
	ARGUMENTS: 
		vector3 a_v3Pivot -> pivot
	OUTPUT: ---
	*/
	void SetPivot(vector3 a_v3Pivot);
	/*
	USAGE: Get the pivot point to rotate around
	ARGUMENTS: ---
	OUTPUT: pivot
	*/
	vector3 GetPivot(void);
	/*
	USAGE: Generates frames for the animation system
	ARGUMENTS: int a_nFrames -> number of frames to generate
	OUTPUT: ---
	*/
	void GenerateFrames(int a_nFrames);
	/*
	USAGE: Will indicate whether the group has been globalized or not
	ARGUMENTS: bool a_bGlobalized -> is globalized?
	OUTPUT: ---
	*/
	void SetGlobalized(bool a_bGlobalized);
	/*
	USAGE: Will get whether the group has been globalized or not
	ARGUMENTS: ---
	OUTPUT: globalided?
	*/
	bool GetGlobalized(void);
	/*
	USAGE: Sets the Model to world matrix for the provided frame
	ARGUMENTS: uint a_uFrame -> frame to modify
	OUTPUT: ---
	*/
	void SetModelToWorld(matrix4 a_m4ModelToWorld, uint a_uFrame);
	/*
	USAGE: Gets the model matrix of the specified frame
	ARGUMENTS:
		uint a_uFrame -> frame looked
	OUTPUT: model matrix of the frame
	*/
	matrix4 GetModelMatrix(uint a_uFrame);
	/*
	USAGE: Sets the model matrix of the specified frame
	ARGUMENTS:
	matrix4 a_m4Transform -> model matrix of the frame
	uint a_uFrame -> frame looked
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4Transform, uint a_uFrame);
	/*
	USAGE: will get the number of meshes in this model
	ARGUMENTS: ---
	OUTPUT: number of meshes in this model
	*/
	uint GetMeshCount(void);
	/*
	USAGE: Asks the group for the list of vertices for all meshes
	ARGUMENTS: ---
	OUTPUT: list of vertices of this group
	*/
	std::vector<vector3> GetVertexList(int a_nFrame = 0);
private:
	/*
	Method: Release
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Method: Init
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

EXPIMP_TEMPLATE template class SimplexDLL std::vector<Group>;
EXPIMP_TEMPLATE template class SimplexDLL std::vector<Group*>;

} //namespace Simplex

#endif //__SimplexGroup_H__
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/