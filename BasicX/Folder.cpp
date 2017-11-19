#include "BasicX\System\Folder.h"
using namespace BasicX;
//  Folder
Folder* Folder::m_pInstance = nullptr;
Folder* Folder::GetInstance(void)
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new Folder();
	}
	return m_pInstance;
}
Folder::Folder(void){Init();}
Folder::Folder(Folder const& other){}
Folder& Folder::operator=(Folder const& other) {	return *this; }
Folder::~Folder(void){Release();};
void Folder::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

//--- Non Standard Singleton Methods
void Folder::Release(void) { }
void Folder::Init(void)
{
	m_sRoot = GetRealProgramPath();
	if( IsDebuggerPresent() )
	{
		int nSize = m_sRoot.size();
		nSize -= 9;
		char* temporal = new char[nSize + 1];
		int i;
		for(i = 0; i < nSize; i++)
		{
			temporal[i] = m_sRoot[i];
		}
		temporal[i] = '\0';
		m_sRoot = temporal;
		delete[] temporal;
		m_sRoot += "_Binary\\";
	}
	m_sData = "Data\\";
	m_sAudio = "Audio\\";
	m_s3DS = "M3DS\\";
	m_sBTO = "MBTO\\";
	m_sPOM = "MPOM\\";
	m_sFBX = "MFBX\\";
	m_sOBJ = "MOBJ\\";
	m_sLVL = "LVL\\";
	m_sTextures = "Textures\\";
	m_sShaders = "Shaders\\";
	m_sAddOn = "ADD\\";
}
String Folder::GetRealProgramPath(void)
{
	TCHAR stCurrentDir[MAX_PATH];
	//Get the Program Path, the directory on which the program lives
	GetModuleFileName( 0, stCurrentDir, MAX_PATH);
	char* zsTemp1 = new char[MAX_PATH];
	if(!zsTemp1)
		return NULL;
	strcpy_s(zsTemp1, MAX_PATH, "");
	int nCounter = 0;
	while(stCurrentDir[nCounter] != 0)
	{
		zsTemp1[nCounter] = static_cast<char> (stCurrentDir[nCounter]);
		nCounter++;
	}
	zsTemp1[nCounter] = 0;
	
	// Count backwards until a slash is found or zero
	while(nCounter > 0)
	{
		if(zsTemp1[nCounter] == '\\')
			break;
		nCounter--;
	}
	char* zsTemp2 = new char[nCounter +2];
	if(!zsTemp2)
		return NULL;
	for(int n = 0; n < nCounter +1; n++)
	{
		zsTemp2[n] = zsTemp1[n];
	}
	zsTemp2[nCounter+1] = 0;
	delete[] zsTemp1;
	zsTemp1 = 0;
	String output = static_cast<String> (zsTemp2);
	delete[] zsTemp2;
	zsTemp2 = 0;
	
	return output;
}

//m_sRoot
void Folder::SetFolderRoot(String input) {  m_sRoot = input; }
String Folder::GetFolderRoot(void) { return m_sRoot; }

//m_sData
void Folder::SetFolderData(String input) { m_sData = input; }
String Folder::GetFolderData(void) { return m_sData; }

//m_sTextures
void Folder::SetFolderAudio(String input) { m_sAudio = input; }
String Folder::GetFolderAudio(void) { return m_sAudio; }

//m_sTextures
void Folder::SetFolderTextures(String input) { m_sTextures = input; }
String Folder::GetFolderTextures(void) { return m_sTextures; }

//m_sShaders
void Folder::SetFolderShaders(String input) { m_sShaders = input; }
String Folder::GetFolderShaders(void) { return m_sShaders; }

//m_sM3DS
void Folder::SetFolderM3DS(String input) { m_s3DS = input; }
String Folder::GetFolderM3DS(void) { return m_s3DS; }

//m_sMBTO
void Folder::SetFolderMBTO(String input) { m_sBTO = input; }
String Folder::GetFolderMBTO(void) { return m_sBTO; }

//m_sMPOM
void Folder::SetFolderMPOM(String input) { m_sPOM = input; }
String Folder::GetFolderMPOM(void) { return m_sPOM; }

//m_sMFBX
void Folder::SetFolderMFBX(String input) { m_sFBX = input; }
String Folder::GetFolderMFBX(void) { return m_sFBX; }

//m_sMOBJ
void Folder::SetFolderMOBJ(String input) { m_sOBJ = input; }
String Folder::GetFolderMOBJ(void) { return m_sOBJ; }

//m_sLVL
void Folder::SetFolderLVL(String input) { m_sLVL = input; }
String Folder::GetFolderLVL(void) { return m_sLVL; }

//m_sAddOn
void Folder::SetFolderAddOn(String input) { m_sAddOn = input; }
String Folder::GetFolderAddOn(void) { return m_sAddOn; }