/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
Modified: 2017/06
----------------------------------------------*/
#ifndef __SEQUENCECLASS_H_
#define __SEQUENCECLASS_H_

#include "Simplex\System\SystemSingleton.h"

namespace Simplex
{

//sequence class
class SimplexDLL Sequence
{
	String m_sName = "";		//Secuence Name
	bool m_bDirectAnimation = true;//Secuence going from a low to a high frame number?
	uint m_uID = 0;					//Secuence Identifier
	int m_nFirstFrame = 0;			//First frame of the secuence;
	int m_nLastFrame = 0;			//Last frame of the secuence;
	uint m_uFrameRate = 0;			//How many frames a secuence is playing
	uint m_uFrameCount = 0;			//Number of frames in this sequence;
	
public:
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Sequence();
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Sequence(String a_sName, int a_nID, int a_nFirstFrame, int a_nLastFrame, int a_nFrameRate);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Sequence(String a_sName, int a_nID, int a_nFirstFrame, int a_nLastFrame, int a_nFrameRate, bool a_bRepeat);

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Sequence(const Sequence& other);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Sequence& operator=(const Sequence& other);;
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	~Sequence();

	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void Init();
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void Release();
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetID(int a_nID);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int getID(void);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetName(String a_sName);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	String GetName(void);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetFirstFrame(int a_nFirstFrame);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int GetFirstFrame(void);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetLastFrame(int a_nLastFrame);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int GetLastFrame(void);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetDirectAnimation(bool a_bDirectAnimation);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	bool IsDirectAnimation(void);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void setFrameRate(int a_nFrameRate);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int GetFrameRate(void);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	uint GetFrameCount(void);
	/*


private:
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void Swap(Sequence& other);
};

EXPIMP_TEMPLATE template class SimplexDLL std::vector<Sequence>;
EXPIMP_TEMPLATE template class SimplexDLL std::vector<Sequence*>;

} //namespace Simplex

#endif //__SEQUENCECLASS_H__
  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */