/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
Modified: 2017/06
----------------------------------------------*/
#ifndef __STATECLASS_H_
#define __STATECLASS_H_

#include "Simplex\System\SystemSingleton.h"
#include <vector>

namespace Simplex
{

//State class
class SimplexDLL State
{
	String m_sName;

	bool m_bBreakableState = true;	//Can I break out of this state without finishing the animation?
	bool m_bTransitionState = false;//Is this a transition state
	bool m_bRepeatSequence	= true;	//Does the sequence repeats
	
	int m_nSequence = 0;			//Sequence being played
	String m_sSequenceName = "";
	uint m_uExitCount = 0;			//Number of exits of this state
	
	std::vector<State*> m_exitList;//Exits of the state
		
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	State();
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	State(String a_sName, int a_nSequence = 0, bool a_bBreakableState = false, bool a_bTransitionState = false, bool a_bRepeatSequence = false);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	State(const State& other);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	State& operator=(const State& other);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	~State();
	/*
	USAGE: Initialices variable values
	ARGUMENTS:
	OUTPUT:
	*/
	void Init();
	/*
	USAGE: Releases the memory and deallocate space.
	ARGUMENTS:
	OUTPUT:
	*/
	void Release();
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetName(String a_sName);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetName(void);
	//__declspec(property(put = SetName, get = GetName)) String Name;
	/*
	USAGE: Sets the sequence name used in this state
	ARGUMENTS: String a_sSequenceName -> name of sequence
	OUTPUT: ---
	*/
	void SetSequenceName(String a_sSequenceName);
	/*
	USAGE: Gets the name of the sequence used in this state
	ARGUMENTS: ---
	OUTPUT: Name of state sequence
	*/
	String GetSequenceName(void);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetSequence(int a_nSequence);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetSequence(void);
	//__declspec(property(put = SetSequence, get = GetSequence)) int Sequence;
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetBreakable(bool a_bRepeatSequence);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetBreakable(void);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetRepeatSequence(bool a_bRepeatSequence);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetRepeatSequence(void);
	//__declspec(property(put = SetRepeatSequence, get = GetRepeatSequence)) bool RepeatSequence;
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetNumberOfExits(void);
	//__declspec(property(get = GetNumberOfExists)) int Exits;
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int AddExit(State* a_pState);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int GetExitIndex(State* a_pState);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsTransitionState(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	State* GetAutoExit(void); //B-TODO: Get rid of this when old code is removed
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	State* GetExit(uint a_uIndex);
	/*
	USAGE: will check the list of exits for transitional states;
	once it finds out if the exit is one it will check if the
	exit is the exit we are looking for, if so it will return
	the transitional state that will take us to the query state
	ARGUMENTS:
	OUTPUT:
	*/
	State* GetExitFromTransitionExits(State* a_pExit);

private:
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void Swap(State& other);
};

EXPIMP_TEMPLATE template class SimplexDLL std::vector<State>;
EXPIMP_TEMPLATE template class SimplexDLL std::vector<State*>;

} //namespace Simplex

#endif //__STATECLASS_H__

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */