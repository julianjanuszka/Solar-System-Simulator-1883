/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
----------------------------------------------*/
#ifndef __SIMPLEXDEFINITIONS_H_
#define __SIMPLEXDEFINITIONS_H_

// Include standard headers
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <vector>
#include <locale>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <vector>
#include <map>
#include <set>
#include <deque>

// Include GLM
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\ext.hpp>
#include <glm\gtc\quaternion.hpp>

#ifdef EXP_STL
#	define SimplexDLL __declspec(dllexport)
#	define EXPIMP_TEMPLATE
#else
#	define SimplexDLL __declspec(dllimport)
#	define EXPIMP_TEMPLATE extern
#endif

namespace Simplex
{
	typedef unsigned int uint;
	typedef std::string String;
	typedef glm::vec2 vector2;
	typedef glm::vec3 vector3;
	typedef glm::vec4 vector4;
	typedef glm::mat3 matrix3;
	typedef glm::mat4 matrix4;
	typedef glm::quat quaternion;
/*
USAGE: will safely delete the input pointer and initialize it to nullptr, DOES NOT WORK WITH POINTER ARRAY
*/
#define SafeDelete(p){ if(p) { delete p; p = nullptr; } }

#define PI 3.14159265358979323846
#define IDENTITY_M4 matrix4(1.0f)
#define IDENTITY_QUAT quaternion();
#define ZERO_V3 vector3(0.0f, 0.0f, 0.0f)
#define DEFAULT_V3NEG vector3(-1.0f, -1.0f, -1.0f)

#define C_BLACK vector3(0.0f, 0.0f, 0.0f)
#define C_WHITE vector3(1.0f, 1.0f, 1.0f)
#define C_GRAY vector3(0.3f, 0.3f, 0.3f)

#define C_RED vector3(1.0f, 0.0f, 0.0f)
#define C_MAGENTA vector3(1.0f, 0.0f, 1.0f)
#define C_BROWN vector3(0.6f,0.3f,0.0f)

#define C_GREEN vector3(0.0f, 1.0f, 0.0f)
#define C_GREEN_DARK vector3(0.0f, 5.0f, 0.0f)
#define C_GREEN_LIME vector3(0.33f,0.90f,0.33f)

#define C_BLUE vector3(0.0f, 0.0f, 1.0f)
#define C_BLUE_CORNFLOWER vector3(0.4f, 0.6f, 0.9f)
#define C_CYAN vector3(0.0f,1.0f,1.0f)

#define C_INDIGO vector3(0.30f, 0.0f, 0.52)

#define C_YELLOW vector3(1.0f, 1.0f, 0.0f)
#define C_ORANGE vector3(1.0f,0.5f,0.0f)
#define C_VIOLET vector3(0.54f,0.16f,0.88f)
#define C_PURPLE vector3(0.50f,0.0f,0.50f)

#define AXIS_X vector3(1.0f, 0.0f, 0.0f)
#define AXIS_XY vector3(1.0f, 1.0f, 0.0f)
#define AXIS_XZ vector3(1.0f, 0.0f, 1.0f)
#define AXIS_Y vector3(0.0f, 1.0f, 0.0f)
#define AXIS_YZ vector3(0.0f, 1.0f, 1.0f)
#define AXIS_Z vector3(0.0f, 0.0f, 1.0f)

//-----------------------------------------------------------------------------------------------------------
// Enumerations
//-----------------------------------------------------------------------------------------------------------
enum BTO_OPTIONS
{
	OPT_NO = 0,
	OPT_YES = 1,
	OPT_ASK = 2,
	OPT_OPENGL3X = 3,
};
enum BTO_OUTPUT
{
	OUT_ERR_NONE,
	OUT_ERR_GENERAL,
	OUT_ERR_FILE_MISSING,
	OUT_ERR_CONTEXT,
	OUT_ERR_MEMORY,
	OUT_ERR_NAME,
	OUT_ERR_NOT_INITIALIZED,
	OUT_ERR_FILE,
	OUT_ERR_NO_EXTENSION,
	OUT_DONE,
	OUT_RUNNING,
};
enum BTO_AXIS
{
	AX_NONE = 0,
	AX_XY = 1,
	AX_XZ = 2,
	AX_YZ = 4,
};
enum BTO_DISPLAY
{
	BD_NONE = 0,//...
	BD_BS = 1, //Bounding Sphere
	BD_OB = 2, //Oriented Bounding Box
	BD_AB = 4, //Axis (Re)Aligned Bounding Box
};
enum BTO_RENDER
{
	RENDER_NONE = 0,
	RENDER_SOLID = 1,
	RENDER_WIRE = 2,
};
enum BTO_CAMERAMODE
{
	CAM_PERSP = 0,
	CAM_ORTHO_X = 1,
	CAM_ORTHO_Y = 2,
	CAM_ORTHO_Z = 3,
};
enum BTO_FORMAT
{
	FORMAT_ATO = 0,
	FORMAT_BTO = 1,
};
enum BTO_RESOLUTIONS
{
	//Resolution | Aspect Ratio | Name
	RES_WINDOWED,

	//Common resolutions
	RES_C_720x480_4x3_NTSC,
	RES_C_1280x720_16x9_HD,
	RES_C_1920x1080_16x9_FULLHD,

	RES_CV_480x720_3x4_NTSC,
	RES_CV_720x1280_9x16_HD,
	RES_CV_1080x1920_9x16_FULLHD,

	//Monitor Resolutions
	RES_M_640x480_4x3_VGA,
	RES_M_1600x900_16x9_WXGA,
	RES_M_1920x1200_16x10_WUXGA,
	RES_M_2560x1080_21x9_UWUXGA,

	RES_MV_480x640_3x4_VGA,
	RES_MV_900x1600_9x16_WXGA,
	RES_MV_1200x1920_10x16_WUXGA,
	RES_MV_1080x2560_9x21_UWUXGA,

	//Other Resolutions
	RES_O_800x600_4x3_SVGA,
	RES_O_1024x768_4x3_XGA,
	RES_O_1280x800_16x10_WXGA,
	RES_O_1600x1200_4x3_UXGA,
	RES_O_2048x1080_17x9_2K,
	RES_O_3840x2160_17x9_4K,
};

struct SimplexDLL MeshOptions
{
	matrix4 m_m4Transform;
	int m_nRender;
	MeshOptions():m_m4Transform(IDENTITY_M4), m_nRender(RENDER_SOLID) {};
	MeshOptions(matrix4 a_m4Transform, int a_nRender):m_m4Transform(a_m4Transform), m_nRender(a_nRender){};
};

/*
USAGE: Will translate all characters in the string to upper case and return a copy string
ARGUMENTS: String a_sInput -> input string
OUTPUT: output
*/
static String ToUpperCase(String a_sInput)
{
	String output = a_sInput;
	std::transform(output.begin(), output.end(), output.begin(), ::toupper);
	return output;
}

/*
USAGE: Will trim the input string when the first token is found
ARGUMENTS:
-	String a_sInput -> input string
-	char a_sToken -> token to be used as divider
OUTPUT: trimmed output
*/
static String CopyUntilToken(String a_sInput, char a_sToken)
{
	char* szOutput = new char[a_sInput.size() + 1];
	uint counter = 0;
	uint charCount = a_sInput.size();
	while (a_sInput[counter] != a_sToken && counter < charCount)
	{
		szOutput[counter] = a_sInput[counter];
		++counter;
	}
	szOutput[counter] = '\0';
	String output = szOutput;
	if (szOutput)
	{
		delete[] szOutput;
		szOutput = nullptr;
	}
	return output;
}

/*
USAGE: Will trim the input string from when the first token is found till the end
ARGUMENTS:
-	String a_sInput -> input string
-	char a_sToken -> token to be used as divider
OUTPUT: trimmed output
*/
static String CopyAfterToken(String a_sInput, char a_sToken)
{
	uint counter = 0;
	uint charCount = a_sInput.size();
	while (a_sInput[counter] != a_sToken && counter < charCount)
	{
		++counter;
	}
	if (counter == charCount)
		return a_sInput;

	char* szOutput = new char[a_sInput.size() + 1];
	int nSecond = 0;
	++counter;
	while (counter < charCount)
	{
		szOutput[nSecond] = a_sInput[counter];
		++counter;
		++nSecond;
	}
	szOutput[nSecond] = '\0';
	String output = szOutput;
	if (szOutput)
	{
		delete[] szOutput;
		szOutput = nullptr;
	}
	return output;
}

/*
USAGE: Will map a value from an original scale to a new scale
ARGUMENTS:
-	T valueToMap -> input value
-	T originalScale_min ->  Start of the original scale
-	T originalScale_max -> End of the original scale
-	T mappedScale_min -> Start of the new scale
-	T mappedScale_max -> end of the new scale
OUTPUT: returns the mapped value
*/
template <class T>
static T MapValue(T valueToMap, T originalScale_min, T originalScale_max, T mappedScale_min, T mappedScale_max)
{
	return (valueToMap - originalScale_min) * (mappedScale_max - mappedScale_min) / (originalScale_max - originalScale_min) + mappedScale_min;
}

/*
USAGE: Will take a glm::quat and return a glm::mat4 wrapping glm::mat4_cast
ARGUMENTS: quaternion a_qInput -> quaternion to translate from
OUTPUT: matrix4 conversion of a_qInput
*/
static matrix4 ToMatrix4(quaternion a_qInput)
{
	return glm::mat4_cast(a_qInput);
}

/*
USAGE: Will generate random numbers limited to the cap (inclusive)
ARGUMENTS:
-	uint a_uMin -> lower cap (exclusive)
-	uint a_uMax -> upper cap (exclusive)
OUTPUT: random number between 0 and a_uMax
*/
static double GenerateRandom(double a_uMin, double a_uMax)
{
	if (a_uMin >= a_uMax)
		a_uMax = a_uMin + 1;

	//C++11 way
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(a_uMin, a_uMax);
	return dist(gen);
}

/* 
USAGE: Will generate a vector3 from the provided wavelength value
ARGUMENTS: double Wavelength -> wavelength value
OUTPUT: value of the wavelenght on a 0 to 1 vector3
NOTES:
	Adapted from Earl F. Glynn's web page:
	http://www.efg2.com/Lab/ScienceAndEngineering/Spectra.htm
*/
static vector3 WaveLengthToRGB(double Wavelength) {
	double Gamma = 0.80;
	double IntensityMax = 255;

	double factor;
	double Red, Green, Blue;

	if ((Wavelength >= 380) && (Wavelength<440)) {
		Red = -(Wavelength - 440) / (440 - 380);
		Green = 0.0;
		Blue = 1.0;
	}
	else if ((Wavelength >= 440) && (Wavelength<490)) {
		Red = 0.0;
		Green = (Wavelength - 440) / (490 - 440);
		Blue = 1.0;
	}
	else if ((Wavelength >= 490) && (Wavelength<510)) {
		Red = 0.0;
		Green = 1.0;
		Blue = -(Wavelength - 510) / (510 - 490);
	}
	else if ((Wavelength >= 510) && (Wavelength<580)) {
		Red = (Wavelength - 510) / (580 - 510);
		Green = 1.0;
		Blue = 0.0;
	}
	else if ((Wavelength >= 580) && (Wavelength<645)) {
		Red = 1.0;
		Green = -(Wavelength - 645) / (645 - 580);
		Blue = 0.0;
	}
	else if ((Wavelength >= 645) && (Wavelength<781)) {
		Red = 1.0;
		Green = 0.0;
		Blue = 0.0;
	}
	else {
		Red = 0.0;
		Green = 0.0;
		Blue = 0.0;
	};

	// Let the intensity fall off near the vision limits

	if ((Wavelength >= 380) && (Wavelength<420)) {
		factor = 0.3 + 0.7*(Wavelength - 380) / (420 - 380);
	}
	else if ((Wavelength >= 420) && (Wavelength<701)) {
		factor = 1.0;
	}
	else if ((Wavelength >= 701) && (Wavelength<781)) {
		factor = 0.3 + 0.7*(780 - Wavelength) / (780 - 700);
	}
	else {
		factor = 0.0;
	};

	vector3 v3Color;
	// Don't want 0^x = 1 for x <> 0
	v3Color.r = Red == 0.0 ? 0.0f : static_cast<float>(glm::round(IntensityMax * glm::pow(Red * factor, Gamma)));
	v3Color.g = Green == 0.0 ? 0.0f : static_cast<float>(glm::round(IntensityMax * glm::pow(Green * factor, Gamma)));
	v3Color.b = Blue == 0.0 ? 0.0f : static_cast<float>(glm::round(IntensityMax * glm::pow(Blue * factor, Gamma)));

	v3Color = MapValue(v3Color, vector3(0.0f), vector3(255.0f), vector3(0.0f), vector3(1.0f));

	return v3Color;
};

} //namespace Simplex

#endif //__REDEFINITIONS_H__
  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */