/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __LIGHTCLASS_H_
#define __LIGHTCLASS_H_

#include "BasicX\System\SystemSingleton.h"

namespace BasicX
{

class BasicXDLL Light
{
	//Private Fields
	float m_fIntensity = 0.0f;
	vector3 m_v4Position;
	vector3 m_vColor;
public:
	/*
	 Light
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	Light(void);
	/* 	Constructor */
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Light(vector3 a_v4Position, vector3 a_v3Color, float a_vIntensity);
	/* Copy Constructor */
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Light(const Light& other);
	/* Copy Assignment operator */
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Light& operator=(const Light& other);
	/* Destructor */
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Light(void);
	
	//Helper Methods
	/* Swaps the information of two objects*/
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Swap(Light& other);

	//Accessors
	/* Sets the position of the light */
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetPosition(vector3 a_v4Position);
	/* Gets the position of the light */
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetPosition(void);
	/* Property SetPosition/GetPosition */
	//__declspec(property(put = SetPosition, get = GetPosition)) vector3 Position;

	/* Sets the color of the light */
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetColor(vector3 a_v3Color);
	/* Gets the color of the light*/
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetColor(void);
	/* Property SetColor/GetColor */
	//__declspec(property(put = SetColor, get = GetColor)) vector3 Color;

	/* Set Intensity of the light */
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetIntensity(float a_fIntensity);
	/* Gets the intensity of the light*/
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetIntensity(void);
	/* Property SetIntensity/GetIntensity */
	//__declspec(property(put = SetIntensity, get = GetIntensity)) float Intensity;

protected:
	//Protected methods
	/* Initializates the object values*/
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/* Releases the object*/
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
};

EXPIMP_TEMPLATE template class BasicXDLL std::vector<Light>;
EXPIMP_TEMPLATE template class BasicXDLL std::vector<Light*>;

}
#endif //__LIGHT_H__