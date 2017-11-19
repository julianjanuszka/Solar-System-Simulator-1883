/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
----------------------------------------------*/
#ifndef __GLFWAPPCLASS_H_
#define __GLFWAPPCLASS_H_

#include "Simplex\Simplex.h"
#include "GLFW\glfw3.h"

using namespace Simplex;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

class GLFWApp
{
	bool m_bFPC = false;// First Person Camera flag
	bool m_bArcBall = false;// Arcball flag
	quaternion m_qArcBall; //ArcBall quaternion
	float m_dMinDelta = 0.0166f;//Minimum reason of change
	vector4 m_v4ClearColor; //Color of the scene

	GLFWwindow* m_pWindow = nullptr; //GLFW pointer to window
	SystemSingleton* m_pSystem = nullptr;// Singleton of the system
	MeshManager* m_pMeshMngr = nullptr;//Mesh Manager
	CameraManager* m_pCameraMngr = nullptr; // Singleton for the camera that represents our scene
	
	Simplex::Model* m_pModel = nullptr; //Model to try

public:
	static GLFWApp* m_pSelfPointer; //Used for callbacks
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	GLFWApp();
	/*
	USAGE: Destroys instance
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~GLFWApp(void);
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
	void ProcessKeyboard(int key, int scancode, int action, int mods);
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessMouse(int button, int action, int mods);
	/*
	USAGE: Manage the response of gamepad controllers
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ProcessJoystick(void);

private:
	/*
	USAGE: copy constructor, private so it does not let object copy
	ARGUMENTS:
		GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	GLFWApp(GLFWApp const& input);
	/*
	USAGE: copy assignment, private so it does not let object copy
	ARGUMENTS:
	GLFWApp const& input -> object to copy (well in this case not)
	OUTPUT: ---
	*/
	GLFWApp& operator=(GLFWApp const& input);
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
	void InitWindow(String a_sWindowName = "GLFW");
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

#endif //__GLFWAPPCLASS_H_

/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/