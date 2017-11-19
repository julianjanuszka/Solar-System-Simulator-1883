/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
Modified: 2017/06
----------------------------------------------*/
#ifndef __FOLDERSINGLETON_H_
#define __FOLDERSINGLETON_H_

#include <string>
#include <Windows.h>

#include "Simplex\system\Definitions.h" //ReEng basic Definitions

namespace Simplex
{

//Folder Class
class SimplexDLL Folder
{
	String m_sRoot = "";
	String m_sData = "";
	String m_sBTO = "";
	String m_sFBX = "";
	String m_sOBJ = "";
	String m_sLVL = "";
	String m_sAudio = "";
	String m_sTextures = "";
	String m_sShaders = "";
	String m_sAddOn = "";

	static Folder* m_pInstance;
public:
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	static Folder* GetInstance(void);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	static void ReleaseInstance();	//Singleton Destructor
	
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderRoot(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderRoot(void);
	//__declspec(property(put = SetFolderRoot, get = GetFolderRoot)) String Root;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderData(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderData(void);
	//__declspec(property(put = SetFolderData, get = GetFolderData)) String Data;

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderAudio(String a_sInput);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderAudio(void);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderMBTO(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderMBTO(void);
	//__declspec(property(put = SetFolderMBTO, get = GetFolderMBTO)) String MBTO;


	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderMFBX(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderMFBX(void);
	//__declspec(property(put = SetFolderMFBX, get = GetFolderMFBX)) String MFBX;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderMOBJ(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderMOBJ(void);
	//__declspec(property(put = SetFolderMOBJ, get = GetFolderMOBJ)) String MOBJ;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderLVL(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderLVL(void);
	//__declspec(property(put = SetFolderLVL, get = GetFolderLVL)) String LVL;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderTextures(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderTextures(void);
	//__declspec(property(put = SetFolderTextures, get = GetFolderTextures)) String Textures;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderShaders(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderShaders(void);
	//__declspec(property(put = SetFolderShaders, get = GetFolderShaders)) String Shaders;

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFolderAddOn(String a_sInput);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetFolderAddOn(void);
	//__declspec(property(put = SetFolderAddOn, get = GetFolderAddOn)) String AddOn;

private:
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	Folder(void);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Folder(const Folder& other);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Folder& operator=(const Folder& other);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Folder(void);

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/*
	
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetRealProgramPath(void);
};

} //namespace Simplex

#endif //__FOLDERSINGLETON_H_
  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */
