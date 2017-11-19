/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
----------------------------------------------*/
#ifndef __SDLAPPCLASS_H_
#define __SDLAPPCLASS_H_

#define SDL_MAIN_HANDLED

#include "Simplex\Simplex.h"

#include "SDL\SDL.h"
#include "SDL\SDL_opengl.h"

using namespace Simplex;

class SDLApp
{
	bool m_bFPC = false;// First Person Camera flag
	bool m_bArcBall = false;// Arcball flag
	quaternion m_qArcBall; //ArcBall quaternion
	float m_dMinDelta = 0.0166f;//Minimum reason of change
	vector4 m_v4ClearColor; //Color of the scene

	SDL_Window* window = nullptr; //SDL Window
	SDL_GLContext context; //SDL Context
	SystemSingleton* m_pSystem = nullptr;// Singleton of the system
	MeshManager* m_pMeshMngr = nullptr;//Mesh Manager
	CameraManager* m_pCameraMngr = nullptr; // Singleton for the camera that represents our scene
	
	Simplex::Model* m_pModel = nullptr; //Model to try

public:
	static SDLApp* m_pSelfPointer; //Used for callbacks
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	SDLApp();
	/*
	USAGE: Destroys instance
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~SDLApp(void);
	/*
	USAGE: Runs the main loop of this class DO NOT OVERRIDE
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Run(void);
	
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessKeyboard(SDL_Event a_event);
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMousePress(SDL_Event a_event);
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMouseRelease(SDL_Event a_event);
	/*
	USAGE: Manage the response of gamepad controllers
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessJoystick(SDL_Event a_event);

private:
	/*
	USAGE: copy constructor, private so it does not let object copy
	ARGUMENTS:
		GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	SDLApp(SDLApp const& input);
	/*
	USAGE: copy assignment, private so it does not let object copy
	ARGUMENTS:
	GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	SDLApp& operator=(SDLApp const& input);
	/*
	USAGE: Resizes the window
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Reshape(void);
	/*
	USAGE: Clears the OpenGL screen by the specified color
	ARGUMENTS:
	vector4 a_v4ClearColor = vector4(-1.0f) -> Color to clear the screen with
	OUTPUT: ---
	*/
	void ClearScreen(vector4 a_v4ClearColor = vector4(-1.0f));
	
protected:
	/*
	USAGE: Initializes the window and rendering context
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Process the arcball of the scene, rotating an object in the center of it	a_fSensitivity is
	a factor of change
	ARGUMENTS:
		float a_fSensitivity = 0.1f -> indicates how fast the arcball is going to change
	OUTPUT: ---
	*/
	void ArcBall(float a_fSensitivity = 0.1f);
	/*
	USAGE: Manages the rotation of the camera a_fSpeed is a factor of change
	ARGUMENTS:
		float a_fSpeed = 0.005f
	OUTPUT: ---
	*/
	void CameraRotation(float a_fSpeed = 0.005f);
	/*
	USAGE: Initialize the window
	ARGUMENTS:
		String a_sWindowName = "GLFW" -> Window name
	OUTPUT: ---
	*/
	void InitWindow(String a_sWindowName = "SFML");
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ReadConfig(void);
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void WriteConfig(void);
	/*
	USAGE: Initializes user specific variables, this is executed right after InitWindow,
	the purpose of this member function is to initialize member variables specific for this project.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void InitVariables(void);
	/*
	USAGE:	Will initialize the maximum frame rate and the max delta frame
	ARGUMENTS:
		float a_fMaxFrameRate -> maximum frame rate the system can execute
	OUTPUT: ---
	*/
	void SetMaxFramerate(float a_fFrameRateLimit);
	/*
	USAGE: Releases the application
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Display(void);
	/*
	USAGE: Runs faster than the update
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Idle(void);
	
};

#endif //__SDLAPPCLASS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/