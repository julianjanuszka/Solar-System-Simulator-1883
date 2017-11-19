/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
Modified: 2017/06
----------------------------------------------*/
#ifndef __ANIMATIONCLASS_H_
#define __ANIMATIONCLASS_H_

#include "Simplex\System\SystemSingleton.h"
#include "Simplex\Animation\Frame.h"

namespace Simplex
{

//Animation class
class SimplexDLL Animation
{
public:
	/*
	 Animation
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	Animation(void);
	/*
	 Animation
	USAGE: Copy Constructor
	ARGUMENTS: other instance
	OUTPUT: class object
	*/
	Animation(const Animation& other);
	/*
	 operator=
	USAGE: copy assignment operator
	ARGUMENTS: other instance
	OUTPUT: ---
	*/
	Animation& operator=(const Animation& other);
	/*
	 ~Animation
	USAGE: destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Animation(void);
	/*
	 Init
	USAGE: Initializes the variable members
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	 Release
	USAGE: Deinitializes the variable members
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	 Swap
	USAGE: swaps the values of the member fields of incoming object for self's
	ARGUMENTS: other instance
	OUTPUT: ---
	*/
	void Swap(Animation& other);
	/*
	 Animation
	USAGE: constructor, will create a number of frames
	ARGUMENTS:
		Frame *a_pFrame -> pointer to a frame class object 
		int a_nFrames -> number of frames to create
	OUTPUT: class object
	*/
	Animation(Frame *a_pFrame, int a_nFrames);
	/*
	 CheckInterpolation const;
	USAGE: Checks the interpolation of the frames
	ARGUMENTS:
		Frame *a_pFrame -> pointer to frame object
		int a_nFrames
	OUTPUT: ---
	*/
	void CheckInterpolation(Frame *a_pFrame, int a_nFrames) const;
private:
	/*
	 Interpolation const;
	USAGE: Interpolates the frames from the first to the last frame
	ARGUMENTS:
		Frame *a_pFrame -> frame pointer
		int a_nFirstKeyFrame -> First frame to interpolate
		int a_nLastKeyFrame -> Last frame to interpolate
	OUTPUT: ---
	*/
	void Interpolation(Frame *a_pFrame, int a_nFirstKeyFrame, int a_nLastKeyFrame) const;
};

EXPIMP_TEMPLATE template class SimplexDLL std::vector<Animation>;
EXPIMP_TEMPLATE template class SimplexDLL std::vector<Animation*>;

} //namespace Simplex

#endif //__ANIMATIONCLASS_H__
  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */