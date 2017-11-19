/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __EXAMPLESINGLETON_H_
#define __EXAMPLESINGLETON_H_

#include "Simplex\Simplex.h"

namespace Simplex
{

//System Class
class ExampleSingleton
{
	int m_nData = 0; //number of elements in the list
	static ExampleSingleton* m_pInstance; // Singleton pointer
	std::vector<int> m_lData; //list of elements
public:
	/*
	Usage: Gets the singleton pointer
	Arguments: ---
	Output: singleton pointer
	*/
	static ExampleSingleton* GetInstance();
	/*
	Usage: Releases the content of the singleton
	Arguments: ---
	Output: ---
	*/
	static void ReleaseInstance(void);
	/*
	Usage: Gets data member
	Arguments: ---
	Output: data member
	*/
	int GetData(void);
	/*
	Usage: sets data member
	Arguments: int a_nData = 1 -> data to set
	Output: ---
	*/
	void SetData(int a_nData = 1);
	/* Property GetData/SetData */
	//__declspec(property(get = GetData, put = SetData)) int Data;
	/*
	Usage: Sets data on the vector
	Arguments: int a_nData -> data to set
	Output: ---
	*/
	void SetDataOnVector(int a_nData);
	/*
	Usage: Gets data from the vector at the specified position
	Arguments: int a_nIndex -> entry
	Output: entry
	*/
	int& GetDataOnVector(int a_nIndex);

private:
	/*
	Usage: constructor
	Arguments: ---
	Output: class object instance
	*/
	ExampleSingleton(void);
	/*
	Usage: copy constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	ExampleSingleton(ExampleSingleton const& other);
	/*
	Usage: copy assignment operator
	Arguments: class object to copy
	Output: ---
	*/
	ExampleSingleton& operator=(ExampleSingleton const& other);
	/*
	Usage: destructor
	Arguments: ---
	Output: ---
	*/
	~ExampleSingleton(void);
	/*
	Usage: releases the allocated member pointers
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Usage: initializes the singleton
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};//class

} //namespace Simplex

#endif //__EXAMPLESINGLETON_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/