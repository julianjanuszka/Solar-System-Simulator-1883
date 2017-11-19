#include "BasicX\System\FileReader.h"
using namespace BasicX;
String GetFirst(String input)
{
	int length = static_cast<int>(input.size());
	char* temp = new char[length+1];
	int i = 0;
	for (i = 0; i < length; i++)
	{
		temp[i] = input[i];
	}
	temp[i] = '\0';

	char * pch;
	pch = strtok (temp," ");

	String sWord = temp;
	delete temp;
	
	return sWord;
}

FileReader::FileReader(void) { Init(); }
FileReader::FileReader(const FileReader& other) { }
FileReader& FileReader::operator=(const FileReader& other) { return *this; }
FileReader::~FileReader(void) { Release(); }
	
void FileReader::Release(void) { }
void FileReader::Init(void)
{
	m_pFile = nullptr;
	m_pSystem = SystemSingleton::GetInstance();
	m_sFirstWord = "";
}

BTO_OUTPUT FileReader::SaveBinaryFile(String a_sFileName)
{
	m_oStream = std::ofstream(a_sFileName.c_str(), std::ios::out | std::ios::binary);
	if (m_oStream.is_open() == false)
	{
		return OUT_ERR_FILE_MISSING;
	}
		
	return OUT_ERR_NONE;
}

BTO_OUTPUT FileReader::ReadBinaryFile(String a_sFileName)
{
	m_iStream = std::ifstream(a_sFileName.c_str(), std::ios::in | std::ios::binary);
	if (m_iStream.is_open() == false)
	{
		return OUT_ERR_FILE_MISSING;
	}

	return OUT_ERR_NONE;
}
BTO_OUTPUT FileReader::ReadFile(String a_sFileName)
{
	//if(m_pFile != nullptr)
	//	CloseFile();

	//fopen_s(&m_pFile, a_sFileName.c_str(), "r");

	m_iStream = std::ifstream(a_sFileName.c_str());
	if (m_iStream.is_open() == false)
		return OUT_ERR_FILE_MISSING;
	
	//if(m_pFile == nullptr)
	//	return OUT_ERR_FILE_MISSING;

	return OUT_ERR_NONE;
}

BTO_OUTPUT FileReader::SaveFile(String a_sFileName)
{
	if (m_pFile != nullptr)
		CloseFile();

	fopen_s(&m_pFile, a_sFileName.c_str(), "w");
	if (m_pFile == nullptr)
		return BTO_OUTPUT::OUT_ERR_FILE_MISSING;

	return OUT_ERR_NONE;
}

void FileReader::CloseFile(void)
{
	if(m_pFile != nullptr)
		fclose(m_pFile);

	if (m_iStream.is_open())
		m_iStream.close();
	
	if (m_oStream.is_open())
		m_oStream.close();
}

void FileReader::Rewind(void) const
{
	if(m_pFile != nullptr)
		rewind(m_pFile);
}
BTO_OUTPUT FileReader::Write(String a_sStringInput)
{
	if (!m_pFile)
		return OUT_ERR_FILE_MISSING;

	fprintf_s(m_pFile, "%s", a_sStringInput.c_str());

	return OUT_ERR_NONE;
}
BTO_OUTPUT FileReader::Write(const char * _Format, ...)
{
	if (!m_pFile)
		return OUT_ERR_FILE_MISSING;
	va_list args;
	va_start(args, _Format);
	vfprintf_s(m_pFile, _Format, args);
	va_end(args);
	return OUT_ERR_NONE;
}

void FileReader::WriteInt(int input)
{
	if (m_oStream.is_open())
	{
		m_oStream.write((char*)&input, sizeof(int));
	}
	return;
}

void FileReader::WriteFloat(float input)
{
	if (m_oStream.is_open())
	{
		m_oStream.write((char*)&input, sizeof(float));
	}
	return;
}

void FileReader::WriteBool(bool input)
{
	if (m_oStream.is_open())
	{
		m_oStream.write((char*)&input, sizeof(bool));
	}
	return;
}

void FileReader::WriteString(String input)
{
	if (m_oStream.is_open())
	{
		int nsize = input.length();
		m_oStream.write((char*)&nsize, sizeof(int));
		m_oStream.write(input.c_str(), nsize);
	}
	return;
}

int FileReader::ReadInt(void)
{
	int output = 0;
	if (m_iStream.is_open())
	{
		m_iStream.read((char*)&output, sizeof(int));
	}
	return output;
}

float FileReader::ReadFloat(void)
{
	float output = 0.0f;
	if (m_iStream.is_open())
	{
		m_iStream.read((char*)&output, sizeof(float));
	}
	return output;
}

bool FileReader::ReadBool(void)
{
	bool output = false;
	if (m_iStream.is_open())
	{
		m_iStream.read((char*)&output, sizeof(bool));
	}
	return output;
}

String FileReader::ReadString(void)
{
	char* output;
	int nSize = 0;
	if (m_iStream.is_open())
	{
		m_iStream.read((char*)&nSize, sizeof(int));
		output = new char[nSize + 1];
		m_iStream.read((char*)output, sizeof(char) * nSize);
		output[nSize] = '\0';
	}
	return String(output);
 }

BTO_OUTPUT FileReader::WriteLine(String a_sStringInput)
{
	if (!m_pFile)
		return OUT_ERR_FILE_MISSING;

	fprintf_s(m_pFile, "%s\n", a_sStringInput.c_str());

	return OUT_ERR_NONE;
}
BTO_OUTPUT FileReader::WriteLine(const char * _Format, ...)
{
	if (!m_pFile)
		return OUT_ERR_FILE_MISSING;

	va_list args;
	va_start(args, _Format);
	vfprintf_s(m_pFile, _Format, args);
	va_end(args);
	fprintf_s(m_pFile, "\n");

	return OUT_ERR_NONE;
}

BTO_OUTPUT FileReader::RemoveTabs(String* a_sInput)
{
	uint nLenght = (*a_sInput).length();
	if (nLenght == 0)
		return BTO_OUTPUT::OUT_ERR_CONTEXT;
	for (uint n = 0; n < nLenght; n++)
	{
		if ((*a_sInput)[n] == '\t')
			(*a_sInput)[n] = ' ';
	}
	return BTO_OUTPUT::OUT_ERR_NONE;
}

BTO_OUTPUT FileReader::ReadNextLine(bool bSkipComments)
{
	//if the file is not open return
	if (!m_iStream.is_open())
		return BTO_OUTPUT::OUT_ERR_NOT_INITIALIZED;

	//if we are at the end of the file return
	if (m_iStream.eof())
		return BTO_OUTPUT::OUT_DONE;

	//read the next line
	std::getline(m_iStream, m_sLine);
	
	//Remove the tabs from the lines
	//m_sLine = RemoveTabs(m_sLine);
	
	//Send the string to clean
	RemoveBlanks(&m_sLine);

	//if comments are skipped check for the beginning of the string
	if(bSkipComments)
	{
		if(m_sLine[0] == '#')
		{
			if(ReadNextLine(bSkipComments) == OUT_DONE)
				return OUT_DONE;
		}
		if(m_sLine[0] == '/')
		{
			if(m_sLine[1] == '/')
			{
				if(ReadNextLine(bSkipComments) == OUT_DONE)
					return OUT_DONE;
			}
		}
		if(m_sLine[0] == 0)
		{
			if(ReadNextLine(bSkipComments) == OUT_DONE)
				return OUT_DONE;
		}
	}

	return OUT_RUNNING;
};
BTO_OUTPUT FileReader::RemoveBlanks(String* a_sInput)
{
	if ((*a_sInput)[0] == 32 || (*a_sInput)[0] == 9)
	{
		//create a char* backup
		int nLenght = m_sLine.size() + 1;
		char* zsLine = new char[nLenght];
		strcpy_s(zsLine, nLenght, m_sLine.c_str());

		uint nLength = strlen(zsLine);
		if (nLength == 0)
			return OUT_ERR_NONE;

		zsLine[nLength] = '\0';

		int nFirstCharacter = 0; //Counts how many characters or tabs there are before each line	
		while (zsLine[nFirstCharacter] == 9 || zsLine[nFirstCharacter] == 32)
		{
			nFirstCharacter++;
		}

		memcpy_s(zsLine, nLength - nFirstCharacter + 1, &zsLine[nFirstCharacter], nLength - nFirstCharacter + 1);
		*a_sInput = zsLine;

		//release the allocated memory
		if (zsLine != nullptr)
		{
			delete[] zsLine;
			zsLine = nullptr;
		}
		return OUT_DONE;
	}
	return OUT_ERR_NONE;
}

BTO_OUTPUT FileReader::RemoveBlanks(char* a_szInput)
{
	if (a_szInput == nullptr)
		return OUT_ERR_MEMORY;

	uint nLength = strlen(a_szInput);
	if (nLength == 0)
		return OUT_ERR_NONE;

	a_szInput[nLength] = '\0';

	int nFirstCharacter = 0; //Counts how many characters or tabs there are before each line	
	while (a_szInput[nFirstCharacter] == 9 || a_szInput[nFirstCharacter] == 32)
	{
		nFirstCharacter++;
	}

	if (nFirstCharacter == 0)
		return OUT_ERR_NONE;
	
	//char *zsTemp = new char[nLength - nFirstCharacter + 1];	//we create a new temp line
	//if (zsTemp == nullptr)
	//	return OUT_ERR_MEMORY;
	//memcpy_s(zsTemp, nLength - nFirstCharacter + 1, &a_szInput[nFirstCharacter], nLength - nFirstCharacter + 1);
	memcpy_s(a_szInput, nLength - nFirstCharacter + 1, &a_szInput[nFirstCharacter], nLength - nFirstCharacter + 1);
	//SafeDelete(a_szInput);
	//a_szInput = zsTemp;

	return BTO_OUTPUT::OUT_DONE;
}
BTO_OUTPUT FileReader::RemoveBlanks(char** zsInput)
{
	int nLength = static_cast<int>(strlen(*zsInput)) + 1;

	if( nLength == 0)
		return OUT_ERR_MEMORY;

	int character = 0; //Counts how many characters or tabs there are before each line	
	
	while ((*zsInput)[character] == 9)
		character ++;

	while ((*zsInput)[character] == 32)
		character ++;
	
	if(character > 0)	//If there is more than one character
	{
		nLength -= character;
		char *zsTemp = new char[nLength];	//we create a new temp line
		if(zsTemp == nullptr)
			return OUT_ERR_MEMORY;

		//Backup the original values
		for(int n = 0; n < nLength; n++)
		{
			zsTemp[n] = (*zsInput)[character + n];
		}
		zsTemp[nLength - 1] = '\0';
		
		//Clean up and initialize original
		if ((*zsInput) != nullptr)
		{
			delete[](*zsInput);
			(*zsInput) = nullptr;
		}
		
		(*zsInput) = new char[nLength];
		//realloc( zsInput, sizeof(char) * nLength );
		
		if((*zsInput) == 0)
		{
			if (zsTemp != nullptr)
			{
				delete[] zsTemp;
				zsTemp = nullptr;
			}
			return OUT_ERR_MEMORY;
		}

		//Restor the original values
		for(int n = 0; n < nLength; n++)
		{
			(*zsInput)[n] = zsTemp[n];
		}
		if (zsTemp != nullptr)
		{
			delete[] zsTemp;
			zsTemp = nullptr;
		}
		
	}

	return OUT_DONE;
};
String FileReader::GetFirstWord(bool a_bToUpper)
{
	m_sFirstWord = m_sLine;
	RemoveTabs(&m_sFirstWord);
	m_sFirstWord = GetFirst(m_sLine);
	
	if(a_bToUpper)
		std::transform(m_sFirstWord.begin(), m_sFirstWord.end(), m_sFirstWord.begin(), ::toupper);
	
	return m_sFirstWord;
}

//BOOL AnsiToUnicode16(CHAR *in_Src, WCHAR *out_Dst, INT in_MaxLen)
//{
//    /* locals */
//    INT lv_Len;
//
//  // do NOT decrease maxlen for the eos
//  if (in_MaxLen <= 0)
//    return FALSE;
//
//  // let windows find out the meaning of ansi
//  // - the SrcLen=-1 triggers MBTWC to add a eos to Dst and fails if MaxLen is too small.
//  // - if SrcLen is specified then no eos is added
//  // - if (SrcLen+1) is specified then the eos IS added
//  lv_Len = MultiByteToWideChar(CP_ACP, 0, in_Src, -1, out_Dst, in_MaxLen);
//
//  // validate
//  if (lv_Len < 0)
//    lv_Len = 0;
//
//  // ensure eos, watch out for a full buffersize
//  // - if the buffer is full without an eos then clear the output like MBTWC does
//  //   in case of too small outputbuffer
//  // - unfortunately there is no way to let MBTWC return shortened strings,
//  //   if the outputbuffer is too small then it fails completely
//  if (lv_Len < in_MaxLen)
//    out_Dst[lv_Len] = 0;
//  else if (out_Dst[in_MaxLen-1])
//    out_Dst[0] = 0;
//
//  // OUT_DONE
//  return TRUE;
//}
//
////WCHAR* ReturnUnicode(String input)
////{
////	int nLenght = static_cast<int>(input.length());
////	if( nLenght < 1)
////		return NULL;
////	WCHAR* output = new WCHAR[(nLenght - 1) * 8 + 1];
////	if(!output)
////		return L"NULL";
////	char* name = input.c_str();
////	AnsiToUnicode16( name, output, nLenght +1);
////	return output;
////}

//http://msdn.microsoft.com/en-us/library/cc500362.aspx
std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

String FileReader::RetriveFileNameFromExplorer(LPCWSTR mFilter, LPCWSTR mDefaultExt) const
{
	String sTemp;
	String sFileName = "";

	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = (LPWSTR) szFileName;
	ofn.nMaxFile = sizeof(szFileName);
	ofn.lpstrFilter = mFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = mDefaultExt;

	Folder* pFolder = Folder::GetInstance();
	sTemp = pFolder->GetFolderRoot() + pFolder->GetFolderData();

	std::wstring wsTemp = s2ws(sTemp);
	LPCWSTR initialDir = wsTemp.c_str();
	ofn.lpstrInitialDir = initialDir;

	if(GetOpenFileName(&ofn))
	{
		std::wstring wsFile = ofn.lpstrFile;

		sFileName = std::string(wsFile.begin(), wsFile.end()); //http://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
	}

	return sFileName;
}
String FileReader::IndicateFileNameOnExplorer(LPCWSTR mFilter, LPCWSTR mDefaultExt) const
{
	String sTemp = "";

	OPENFILENAME ofn;
	char szFileName[MAX_PATH];
	ZeroMemory(&szFileName, sizeof(szFileName));
	//LPWSTR mSuggested

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = (LPWSTR)szFileName; //mSuggested;
	ofn.nMaxFile = sizeof(szFileName);
	ofn.lpstrFilter = mFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = mDefaultExt;
	ofn.lpTemplateName = NULL;
	
	Folder* pFolder = Folder::GetInstance();
	std::wstring wsFile = mDefaultExt;
	sTemp = std::string(wsFile.begin(), wsFile.end());
	if (sTemp == "bto" || sTemp == "BTO" || sTemp == "ato" || sTemp == "ATO")
		sTemp = pFolder->GetFolderRoot() + pFolder->GetFolderData() + pFolder->GetFolderMBTO();
	else
		sTemp = pFolder->GetFolderRoot() + pFolder->GetFolderData();

	std::wstring wsTemp = s2ws(sTemp);
	LPCWSTR initialDir = wsTemp.c_str();
	ofn.lpstrInitialDir = initialDir;

	if(GetSaveFileName(&ofn))
	{
		wsFile = ofn.lpstrFile;
		sTemp = std::string(wsFile.begin(), wsFile.end());
	}
	else
	{
		sTemp = "";
	}

	return sTemp;
}
String FileReader::GetFileNameAndExtension(String aFileName)
{
	int nLenght = static_cast<int>(aFileName.size());
	int nLastOne = 0;
	String output = "";
	for(int i = 0; i < nLenght; i++)
	{
		if(aFileName[i] == '\\' || aFileName[i] == '/')
		{
			nLastOne = i;
		}
	}

	if(nLastOne != 0)
		output = String(aFileName, nLastOne +1, nLenght);
	else
		output = aFileName;

	return output;
}
String FileReader::GetExtension(String a_sFileName)
{
	String output = GetFileNameAndExtension(a_sFileName);
	uint nLenght = output.size();
	uint nLastOne = 0;
	for (uint i = 0; i < nLenght; i++)
	{
		if (output[i] == '.')
		{
			nLastOne = i;
		}
	}
	String sTemp = output;

	if (nLastOne != 0)
		output = String(output, nLastOne + 1, nLenght);
	else
		output = a_sFileName;

	if (sTemp == output)
		output = "";
	
	return output;
}

String FileReader::ToUpper(String a_sInput)
{
	for (auto & c : a_sInput) c = toupper(c);
	return a_sInput;
}
String FileReader::GetFileName(String a_sFileName)
{
	String output = GetFileNameAndExtension(a_sFileName);

	uint nLenght = output.size();
	uint nLastOne = 0;
	for(uint i = 0; i < nLenght; i++)
	{
		if(output[i] == '.')
		{
			nLastOne = i;
		}
	}

	if(nLastOne != 0)
		output = String(output, 0, nLastOne);
	else
		output = a_sFileName;

	return output;
}
String FileReader::GetAbsoluteRoute(String aFileName)
{
	int nLenght = static_cast<int>(aFileName.size());
	int nLastOne = 0;
	String output = "";
	for(int i = 0; i < nLenght; i++)
	{
		if(aFileName[i] == '\\')
		{
			nLastOne = i;
		}
	}

	if(nLastOne != 0)
		output = String(aFileName, 0, nLastOne +1);
	else
		output = aFileName;

	return output;
}
bool FileReader::FileExists(String a_sFileName)
{
	bool output = false;
	//Check if we can open the file
	std::ifstream iStream = std::ifstream(a_sFileName.c_str());
	if (true == iStream.is_open())
	{
		//if we can the file exists and we need to close the file
		output = true;
		iStream.close();
	}

	return output;
}