/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
Modified: 2017/06
----------------------------------------------*/
#ifndef __SIMPLEXMODEL_H_
#define __SIMPLEXMODEL_H_

#include "Simplex\Mesh\Group.h"
#include "Simplex\Animation\Sequence.h"
#include "Simplex\Animation\State.h"


#ifdef FBXSDK_SHARED
	#include <fbxsdk.h>
	#ifdef IOS_REF
		#undef  IOS_REF
		#define IOS_REF (*(pManager->GetIOSettings()))
	#endif
#endif


namespace Simplex
{

//Model Class
class SimplexDLL Model
{
	String m_sFileName = ""; //Name of the file that made this model
	uint m_uID; //Unique identifier of this mesh
	matrix4 m_m4ToWorld; //Transformation from local to world space
	uint m_uFrameCount = 1; //Number of frames this Model has
	uint m_uFrameCurrent = 0; //Current frame displayed
	float m_fLastFrameDrawn = 0.0f; //Last frame rendered
	DWORD m_dLastRenderCall = 0;	//Last render call
	bool m_bFirstRun = true; //Is this the first time the sequence will be played
	String m_sSequenceLast = ""; //Last sequence drawn

	std::set<Group*> m_groupSet; //set that stores the group pointers that make this model
	std::map<String, Group*> m_groupMap; //map that stores the groups by name

	std::set<Sequence*> m_sequenceSet;	//set of sequences
	std::map<String, Sequence*> m_sequenceMap;	//set of sequences

	std::vector<State*> m_stateList;	//List of states
	std::map<String, int> m_stateMap;//Indexer of states

	uint m_uStateCurrent = 0; //Current state of the model
	uint m_uStateNext = 0;

	ShaderManager* m_pShaderMngr = nullptr;	//Shader Manager
	MaterialManager* m_pMatMngr = nullptr;	//Material Manager
	LightManager* m_pLightMngr = nullptr;	//Light Manager
	CameraManager* m_pCameraMngr = nullptr;	//Camera Manager
	MeshManager* m_pMeshMngr = nullptr;		//Mesh Manager
	SystemSingleton* m_pSystem = nullptr;	//System pointer

	static uint m_uIndexer; //counter for unique identifiers
	static std::map<String, Model*> m_modelMap; //list of all the names of created models

public:
	/*
	USAGE: Gets the index of the queried state from the list of states
	ARGUMENTS:  Queried State
	OUTPUT: index ; -1 if not found
	*/
	int GetStateIndex(State* a_pState);
	/*
	USAGE: Gets the index of the queried state (by name) from the list of states
	ARGUMENTS: Name of Queried State
	OUTPUT: index ; -1 if not found
	*/
	int GetStateIndex(String a_sStateName);
	/*
	USAGE: Forces the current and next state to be the provided state if found
	ARGUMENTS: uint a_nState -> state we want to be at
	OUTPUT: ---
	*/
	void SetStateCurrent(uint a_nState);
	/*
	USAGE: Try to move us to the specified state if it cannot take us directly will try
	an auto exit of the current state to move us
	ARGUMENTS: uint a_nState -> state we want to be at
	OUTPUT: ---
	*/
	void SetStateNext(uint a_nState);
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	Model(void);
	/*
	 Model
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	Model(Model const& other);
	/*
	 operator=
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	Model& operator=(Model const& other);
	/*
	 ~Model
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Model(void);

	/*
	USAGE: Changes object contents for other object's
	ARGUMENTS:
		other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(Model& other);

	/*
	USAGE: Adds an existing group to the group list
	ARGUMENTS:
		Group* a_pGroup -> Group to add
	OUTPUT: ---
	*/
	void AddGroup(Group* a_pGroup);

	/*
	USAGE: Adds all the groups of this model to the render list, the transform
	is specified by the m_pModelToWorld member
	ARGUMENTS: 
	uint nFrame -> Frame to render
	OUTPUT: ---
	*/
	void AddToRenderList(uint a_nFrame = 0);
	/*
	USAGE: Sets the model matrix of the model
	ARGUMENTS:
		matrix4 m_mToWorld -> incoming transformation
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_mToWorld);

	/*
	USAGE: Generates a unique name for this model, desired name is returned if unique,
	otherwise will attach an unique identifier at the end, will not add it to the map
	ARGUMENTS: ---
	OUTPUT: Generated name
	*/
	String GenerateUniqueName(String a_sDesiredName);

	/*
	USAGE: Loads the material file for this model
	ARGUMENTS:
		String a_sFileName -> Name of the mtl file
	OUTPUT:
		Name assigned in the map
	*/
	void LoadMTL(String a_sFileName);
	/*
	USAGE:Loads a model from an OBJ file
	ARGUMENTS:
		String a_sFileName -> File name of the model
	OUTPUT:
		Name assigned in the map
		_|_ will announce the error
	*/
	String LoadOBJ(String a_sFileName);
	/*
	USAGE: Loads a model from an FBX file
	ARGUMENTS:
		String a_sFileName -> File name of the model
	OUTPUT:
		Name assigned in the map
		_|_ will announce the error
	*/
	String LoadFBX(String a_sFileName);
	/*
	USAGE: Loads a model from an FORMAT_ATO file
	ARGUMENTS:
		String a_sFileName -> File name of the model
	OUTPUT:
		Name assigned in the map
		_|_ will announce the error
	*/
	String LoadATO(String a_sFileName);
	/*
	USAGE: Loads a model from an BTO file
	ARGUMENTS:
		String a_sFileName -> File name of the model
	OUTPUT:
		Name assigned in the map
	_|_ will announce the error
	*/
	String LoadBTO(String a_sFileName);
	/*
	USAGE: Loads a file or model; will chose the right loader based 
		on the extension of the file
	ARGUMENTS:
		String a_sFileName -> File to load
	OUTPUT:
		_|_ will announce the error
	*/
	String Load(String a_sFileName);

	/*
	USAGE: Returns the group specified by name
	ARGUMENTS: 
		String a_sGroupName -> searched group
	OUTPUT: ---
		Group pointer
	*/
	Group* GetGroup(String a_sGroupName);
	/*
	USAGE: Gets the state specified by name
	ARGUMENTS: String a_sName -> name of the state
	OUTPUT: state queried
	*/
	State* GetState(String a_sName);

	/*
	USAGE: Sets the name to the model as each name needs to be unique 
		if the desired name is already used will generate a new one and return it
		the name can only be set once as this name is attached to the map of models
	ARGUMENTS:
		String a_sDesiredName -> desired name for the mesh
		bool bForce = false -> forces the name
	OUTPUT: name used
	*/
	String SetName(String a_sDesiredName, bool bForce = false);
	/*
	USAGE: Clone a model
	ARGUMENTS:
		Model* const a_pModel -> model to instantiate from
		String a_sDesiredName -> Name to apply to instance
		bool a_bDuplicateMaterials = false -> ask if the model should be disconnected (creating new materiasl for it)
	OUTPUT: name that instance came out with
	*/
	String Clone(Model* const a_pModel, String a_sDesiredName);
	/*
	USAGE: Instantiate a model
	ARGUMENTS:
	Model* const a_pModel -> model to instantiate from
	String a_sDesiredName -> Name to apply to instance
	OUTPUT: name that instance came out with
	*/
	String Instance(Model* const a_pModel, String a_sDesiredName);
	/*
	USAGE: Will change the previously loaded material applied to the specified group
	ARGUMENTS:
		String sMaterialName -> Previously loaded material name
		Group* a_pGroup -> group to apply the change to
	OUTPUT: ---
	*/
	void ChangeMaterialOfGroup(String a_sMaterialName, Group* a_pGroup);
	/*
	USAGE: Will change the previously loaded material applied to the specified group
	ARGUMENTS:
	uint a_uMaterialIndex -> Previously loaded material index
	Group* a_pGroup -> group to apply the change to, if nullptr will apply it to all
	OUTPUT: ---
	*/
	void ChangeMaterialOfGroup(uint a_uMaterialIndex, Group* a_pGroup = nullptr);
	/*
	USAGE: Will change the previously loaded material applied to the specified group
	ARGUMENTS: 
		String sMaterialName -> Previously loaded material name
		String a_sGroup = "ALL" -> group to apply the change to, if "ALL" will apply it to every group
	OUTPUT: ---
	*/
	void ChangeMaterialOfGroup(String a_sMaterialName, String a_sGroup = "ALL");
	/*
	USAGE: Will change the previously loaded material applied to the specified group
	ARGUMENTS:
	uint a_uMaterialIndex -> Previously loaded material index
	String a_sGroup = "ALL" -> group to apply the change to, if "ALL" will apply it to every group
	OUTPUT: ---
	*/
	void ChangeMaterialOfGroup(uint a_uMaterialIndex, String a_sGroup = "ALL");
	/*
	USAGE: Will change the render options for the ones specified for the group specified by name
		for its mesh indicated by index
	ARGUMENTS:
	MeshOptions a_MeshOptions -> options to change | -1 will change it to all meshes in the group
	String a_sGroupName -> name of the group to change
	int a_nMeshIndex = -1 -> mesh in the list to apply changes to
	OUTPUT: ---
	*/
	void ChangeMeshOptions(MeshOptions a_MeshOptions, String a_sGroupName, int a_nMeshIndex = -1);
	/*
	USAGE: Will change the render options for the ones specified for the group specified
		for its mesh indicated by index
	ARGUMENTS:
	MeshOptions a_MeshOptions -> options to change | -1 will change it to all meshes in the group
	Group* a_pGroup = nullptr -> Group to change | nullptr will change it to all groups in the model
	int a_nMeshIndex = -1 -> mesh in the list to apply changes to
	OUTPUT: ---
	*/
	void ChangeMeshOptions(MeshOptions a_MeshOptions, Group* a_pGroup = nullptr, int a_nMeshIndex = -1);
	/*
	USAGE: Will create new unique materials for each group that are a duplicate of the current 
	material, for each mesh in a group a new unique material will be created.
	ARGUMENTS:
		Group* a_pGroup = nullptr -> Group to affect, if nullptr all groups are affected
	OUTPUT: ---
	*/
	void CreateMaterials(Group* a_pGroup = nullptr);
	/*
	USAGE: Will create new unique materials for the existing group
	that are a duplicate of the current one, one material per mesh is created.
	The identifier is attached at the end of the current material one, clones the
	material and assign the new name, if the material has already been created
	it will attach it without making a new one.
	ARGUMENTS:
		Group* a_pGroup = nullptr -> group to apply changes, nullptr will apply it to all of them
		String a_sIdentifier = "_copy" -> Name to be attached at the end of the current material
	OUTPUT: ---
	*/
	void DuplicateMaterialsUnique(Group* a_pGroup = nullptr, String a_sIdentifier = "_copy");

	/*
	USAGE: Will get the list of models already loaded in memory
	ARGUMENTS: ---
	OUTPUT: map of models loaded in memory, name and index
	*/
	static std::map<String, Model*> GetModelsMap(void);

	/*
	USAGE: Will get a pointer to the model specified by the name, will look in m_modelMap
	ARGUMENTS: ---
	OUTPUT: Model looked
	*/
	static Model* GetModel(String a_sName);

	/*
	USAGE: will return the name assigned to the model
	ARGUMENTS: ---
	OUTPUT: name of the model
	*/
	String GetName(void);

	/*
	USAGE: Will traverse the list hierarchy of groups
	ARGUMENTS:
		Group* a_pGroup = queried group
		int a_nFrame = 0 -> frame of animation
	OUTPUT: matrix transform
	*/
	matrix4 TraverseHierarchy(Group* a_pGroup, int a_nFrame = 0);
	/*
	USAGE: Will play the specified sequence by name
	ARGUMENTS:
		String a_sSequence = "All" -> Sequence to play;
			if "FirstInSet" will play the first sequence in the set
			if "All" it will play a default All sequence (all frames repeting)
		will play the first sequence in the set
	OUTPUT: sequence finished this frame call?
	*/
	bool PlaySequence(String a_sSequence = "All");

	/*
	USAGE: Saves a loaded model as an FORMAT_ATO file
	ARGUMENTS:
	OUTPUT:
	*/
	BTO_OUTPUT SaveATO(String a_sFileName);

	/*
	USAGE: Saves a loaded model as an BTO file
	ARGUMENTS:
	OUTPUT:
	*/
	BTO_OUTPUT SaveBTO(String a_sFileName);
	/*
	USAGE: Adds a sequence to the set of sequences
	ARGUMENTS:
	Sequence* a_pSequence -> sequence to add
	OUTPUT: ---
	*/
	void AddSequence(Sequence* a_pSequence);
	/*
	USAGE: returns the pointer of the sequence queried if in set, nullptr if not
	ARGUMENTS:
	String a_sSequenceName -> queried sequence
	OUTPUT: Sequence
	*/
	Sequence* GetSequence(String a_sSequenceName);
	/*
	USAGE: Adds a state to the list of states
	ARGUMENTS: State* a_pState -> state to add
	OUTPUT: ---
	*/
	void AddState(State* a_pState);
	/*
	USAGE: Plays the current state of the model
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Play(void);
	/*
	USAGE: Asks the group for the list of vertices for all meshes
	ARGUMENTS: ---
	OUTPUT: list of vertices of this group
	*/
	std::vector<vector3> GetVertexList(uint a_nFrame = 0);
private:
	/*
	USAGE: Will compose the groups of the model, getting the frames 
	and interpolating the transforms
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ComposeGroups(void);
	/*
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: will round the vector to avoid float rounding errors
	ARGUMENTS:
		vector3 a_v3Vector -> vector to round
		float fMargin = 0.0001f -> delta
	OUTPUT:
	*/
	vector3 RoundVector(vector3 a_v3Vector, float fMargin = 0.0001f);
#ifdef FBXSDK_SHARED
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void FBXGetExtremeFrames2(FbxNode* a_pNode, int& a_nStart, int& a_nEnd);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void FBXProcessGroupAnimation2(FbxNode* a_pNode, Group* a_pGroup);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void FBXProcessEmpty2(FbxNode* a_pNode);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void FBXProcessMesh2(FbxNode* a_pNode);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void FBXProcessNode2(FbxNode* a_pNode);
	/*
	USAGE: Process the FBX scene into something the Model can read
	ARGUMENTS:
		FbxScene* pScene -> scene to process
	OUTPUT:
		bool -> successful attempt?
	*/
	bool FBXProcessScene2(FbxScene* a_pScene);
#endif
};

EXPIMP_TEMPLATE template class SimplexDLL std::vector<Model>;
EXPIMP_TEMPLATE template class SimplexDLL std::vector<Model*>;

} //namespace Simplex

#endif //__SimplexModel_H__

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */