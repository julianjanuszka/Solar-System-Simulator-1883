/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/05
Modified: 2017/06
----------------------------------------------*/
#ifndef __SIMPLEXAPPCLASS_H_
#define __SIMPLEXAPPCLASS_H_
#pragma warning(disable:4251)
#include "Simplex\Simplex.h"
#include <locale>
#include <codecvt>
#include <string>

#ifndef FBXSDK_SHARED
#define FBXSDK_SHARED
#endif

/* Winapi callback for the window */
SimplexDLL LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Simplex
{

class SimplexDLL SimplexApplication
{
protected:
	bool m_bUsingConsole = false;//Using console flag
	bool m_bFPC = false;// First Person Camera flag
	bool m_bArcBall = false;// Arcball flag

	float m_dMinDelta = 0.0166f;//Minimum reason of change

	GLuint m_nFrameBuffer = 0;
	GLuint m_nDepthBuffer = 0;
	GLuint m_nDawingTexture = 0;

	int m_nScroll = 0;
	unsigned short m_cChar = 0;

	std::pair<int, int> m_selection = std::pair<int, int>(-1, -1); //Selection in the scene

	int m_nCmdShow;	// Number of starting commands on startup
	HINSTANCE m_hInstance; // Windows application Instance
	LPWSTR m_lpCmdLine; // Command line arguments

	//Standard variables
	SystemSingleton* m_pSystem = nullptr;// Singleton of the system

	Window* m_pWindow = nullptr;// Window class
	GLSystem* m_pGLSystem = nullptr;// Singleton of the OpenGL rendering context

	MaterialManager* m_pMatMngr = nullptr;// singleton for the material manager
	LightManager* m_pLightMngr = nullptr;// Singleton for the Light Manager
	MeshManager* m_pMeshMngr = nullptr;//Mesh Manager
	CameraManager* m_pCameraMngr = nullptr; // Singleton for the camera that represents our scene

	vector4 m_v4ClearColor; //Color of the scene
	quaternion m_qArcBall; //ArcBall quaternion

	uint m_uRenderCallCount = 0; //count of render calls per frame

public:

	static SimplexApplication* m_pSelfPointer; //Used for callbacks
	/*
	USAGE: Initializes the object
	ARGUMENTS: SimplexApplication
	- HINSTANCE hInstance -> Instance of the window
	- LPWSTR lpCmdLine -> Command line
	- int nCmdShow -> Number or arguments
	- bool a_bConsole = false -> create command window flag
	OUTPUT: instance object
	*/
	SimplexApplication(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bConsole = false) : m_hInstance(hInstance), m_lpCmdLine(lpCmdLine), m_nCmdShow(nCmdShow), m_bUsingConsole(a_bConsole){}
	/*
	USAGE: Destroys instance
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~SimplexApplication(void){Release();}
	/*
	USAGE: Runs the main loop of this class DO NOT OVERRIDE
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Run(void) final
	{
		//Initialize the system with the fields recollected by the constructor
		Init(m_hInstance, m_lpCmdLine, m_nCmdShow, m_bUsingConsole);

		//Run the main loop until the exit message is sent
		MSG msg = { 0 };
		DWORD dCumulative = 0;
		DWORD dLastTime = GetTickCount();
		while (WM_QUIT != msg.message)
		{
			//Peek the message send by windows and do something dispatch it
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else //If no message was sent continue the regular fields
			{
				DWORD dCurrentTime = GetTickCount();//Current time in the clock
				DWORD dDeltaTime = dCurrentTime - dLastTime; //Calculate the dif between calls
				dLastTime = dCurrentTime; //Set the last time the method was call
			
				dCumulative += dDeltaTime;//Calculate the cumulative time
				if (static_cast<float>(dCumulative/1000.0f) >= m_dMinDelta) //if more than the minimum delta time has passed
				{
					if (GetFocus() != NULL) //If the window is focused...
					{
						ProcessKeyboard(); //Check for keyboard input
						ProcessMouse(); //Check for mouse input
						ProcessJoystick(); //Check for Joystick input
					}
					Update(); //Update the scene
					Display(); //Display the changes on the scene

					dCumulative = dDeltaTime; //reset cumulative time
				}

					
			}
			Idle(); //Every cycle execute idle code.
		}
	}
	/*
	USAGE: This will process windows messages received from the Windows callback
	ARGUMENTS:
	- HWND hwnd -> Window handle
	- UINT msg -> message
	- WPARAM wParam ->  wParam
	- LPARAM lParam -> lParam
	OUTPUT:
	*/
	virtual LRESULT ProcessMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		//Callbacks for winapi 
		switch (msg)
		{
		case WM_SIZE: //if the windows changed size
			if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED) //if it was either maximized or minimized
				Reshape(); //Resize the viewport
			break;
		case WM_EXITSIZEMOVE: //if the window is OUT_DONE resized by the edges
			Reshape(); //resize the viewport
			break;
		case WM_CLOSE: // if the close message was sent
			DestroyWindow(hwnd); //destroy the window
			break;
		case WM_DESTROY:// if the destroy message was sent
			PostQuitMessage(0); //post the quit message to the message manager
			break;
		case WM_MOUSEWHEEL:
			//7864320
			m_nScroll = static_cast<int>(wParam) / 7864320;
			//printf("%d\n", m_nScroll);
			break;
		case WM_KEYDOWN:
			//if escape
			if (wParam == 27)
			{
				PostQuitMessage(0); //post the quit message to the message manager
			}
			// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
			if (wParam > 0 && wParam < 0x10000)
				m_cChar = static_cast<unsigned short>(wParam);
			break;
		case WM_KEYUP:
			// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
			if (wParam > 0 && wParam < 0x10000)
				m_cChar = 0;
			break;
		}
		return 0; //end the program
	}
	/*
	USAGE: Clears the OpenGL screen by the specified color
	ARGUMENTS:
	- vector4 a_v4ClearColor = vector4(-1.0f) -> the color of the clear window, if vec4 of -1s
	will use the initial color without changing it
	OUTPUT: ---
	*/
	void ClearScreen(vector4 a_v4ClearColor = vector4(-1.0f))
	{
		if (a_v4ClearColor != vector4(-1.0f))
		{
			m_v4ClearColor = a_v4ClearColor;
		}
		glClearColor(m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
	}

private:
	/*
	USAGE: Can't be defined
	ARGUMENTS:
	- SimplexApplication const& input -> object to instance
	OUTPUT: instance
	*/
	SimplexApplication(SimplexApplication const& input);
	/*
	USAGE: Cant be defined
	ARGUMENTS:
	- SimplexApplication const& input -> object to copy
	OUTPUT: ---
	*/
	SimplexApplication& operator=(SimplexApplication const& input);
	/*
	USAGE: Resizes the window DO NOT OVERRIDE
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Reshape(void) final
	{
		static bool bFirstRun = true;

		int nWidth; //Get the width of the window
		int nHeight;//Get the height of the window
		m_pWindow->GetSize(&nWidth, &nHeight);

		if (bFirstRun == false)
		{
			m_pWindow->CalculateWindowSize(); //Ask WinApi for the window size and store it in System
			//m_pWindow->GetRenderArea(&nWidth, &nHeight);
		}
			
		printf("Window size: [%d, %d]\n", nWidth, nHeight);//inform the new window size
		glViewport(0, 0, nWidth, nHeight);//resize the viewport
		if (m_nFrameBuffer != 0)
		{
			m_pGLSystem->UpdateRenderTarget(m_nFrameBuffer, m_nDepthBuffer, m_nDawingTexture);
			m_pMeshMngr->SetRenderTarget();
		}
		bFirstRun = false;
	}
	/*
	USAGE: Initializes the ReEng window and rendering context DO NOT OVERRIDE
	ARGUMENTS:
	- HINSTANCE hInstance -> Window instance
	- LPWSTR lpCmdLine -> command arguments
	- int nCmdShow -> number or arguments
	- bool a_bUsingConsole -> console window creation flag
	OUTPUT: ---
	*/
	virtual void Init(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow, bool a_bUsingConsole) final
	{
		// Get the system singleton
		m_pSystem = SystemSingleton::GetInstance();

		SetMaxFramerate(60.0f);

		m_pSystem->SetUsingConsole(a_bUsingConsole);
		// Is this OUT_RUNNING within Visual Studio?
		if (IsDebuggerPresent())
		{
			system("cmd.exe /C xcopy \"../include/RE/Shaders\" \"Shaders\" /y /q");//copy the shader to the right folder
			m_pSystem->SetUsingConsole(true); //set the console creation flag to true
		}
		if (m_pSystem->GetUsingConsole()) //If using the window
		{
			m_pWindow->CreateConsoleWindow();//create a new console window
		}

		m_pSelfPointer = this; //make the shared pointer of the class object point to this object

		//Light manager
		m_pLightMngr = LightManager::GetInstance();

		// Init the App System
		InitWindow("Rendering Engine");

		// Read the configuration file
		ReadConfig();

#pragma region Window Construction and Context setup
		// Create a new window and set its properties
		m_pWindow = new Window(hInstance, nCmdShow, WndProc);
		m_pWindow->SetFullscreen(m_pSystem->IsWindowFullscreen());//set the window to fullscreen?
		m_pWindow->SetBorderless(m_pSystem->IsWindowBorderless());//Set the window to borderless?

		// Make the Window name a wide string
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wide = converter.from_bytes(m_pSystem->GetWindowName());

		// Create a window in the window class
		m_pWindow->CreateMEWindow(wide.c_str(), m_pSystem->GetWindowWidth(), m_pSystem->GetWindowHeight());

		// Get the instance of the class
		m_pGLSystem = GLSystem::GetInstance();
			
		// Create context
		m_pGLSystem->InitGLDevice(m_pWindow->GetHandler());

		// Verify what is the OpenGL rendering context and save it to system (3.x might fail, in which case exit)
		if (m_pGLSystem->GetGLVersion() < 3.0f)
			exit(0);
#pragma endregion			
		//Ambient light (Ambient Light is always the first light, or light[0])
		m_pLightMngr->SetPosition(glm::vec3(0, 0, 0), 0);
		m_pLightMngr->SetIntensity(0.75f, 0);
		m_pLightMngr->SetColor(glm::vec3(1, 1, 1), 0);

		//Point Light (light[1])
		m_pLightMngr->SetPosition(glm::vec3(0, 0, 10), 1);
		m_pLightMngr->SetIntensity(5.00f, 1);
		m_pLightMngr->SetColor(glm::vec3(1, 1, 1), 1);

		m_pMatMngr = MaterialManager::GetInstance();

		// Initializing the Mesh manager
		m_pMeshMngr = MeshManager::GetInstance();
			
		// Setting the camera position.
		m_pCameraMngr = CameraManager::GetInstance();
		m_pCameraMngr->SetPosition(vector3(0.0f, 0.0f, 10.0f));

		// Initialize the App Variables
		InitVariables();

		//Color of the window
		glClearColor(m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);

		//Generate a new render target and set back the render target to be the window
		m_pGLSystem->GenerateRenderTarget(m_nFrameBuffer, m_nDepthBuffer, m_nDawingTexture);
		m_pMeshMngr->SetRenderTarget();

		//Init selection
		m_selection = std::pair<int, int>(-1, -1);

		printf("\n");
	}

protected:
	/*
	USAGE: Process the arcball of the scene, rotating an object in the center of it	a_fSensitivity is
	a factor of change DO NOT OVERRIDE
	ARGUMENTS:
	- float a_fSensitivity = 0.1f -> indicates how fast the arcball is going to change
	OUTPUT: ---
	*/
	virtual void ArcBall(float a_fSensitivity = 0.1f) final
	{
		//If the arcball is not enabled return
		if (!m_bArcBall)
			return;

		//static quaternion qArcBall;
		UINT	MouseX, MouseY;		// Coordinates for the mouse
		UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

		//Initialize the position of the pointer to the middle of the screen
		CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
		CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;
			
		//Calculate the position of the mouse and store it
		POINT pt;
		GetCursorPos(&pt); 
		MouseX = pt.x;
		MouseY = pt.y;

		//Calculate the difference in position and update the quaternion orientation based on it
		float DeltaMouse;
		if (MouseX < CenterX)
		{
			DeltaMouse = static_cast<float>(CenterX - MouseX);
			m_qArcBall = quaternion(vector3(0.0f, glm::radians(a_fSensitivity * DeltaMouse), 0.0f)) * m_qArcBall;
		}
		else if (MouseX > CenterX)
		{
			DeltaMouse = static_cast<float>(MouseX - CenterX);
			m_qArcBall = quaternion(vector3(0.0f, glm::radians(-a_fSensitivity * DeltaMouse), 0.0f)) * m_qArcBall;
		}

		if (MouseY < CenterY)
		{
			DeltaMouse = static_cast<float>(CenterY - MouseY);
			m_qArcBall = quaternion(vector3(glm::radians(-a_fSensitivity * DeltaMouse), 0.0f, 0.0f)) * m_qArcBall;
		}
		else if (MouseY > CenterY)
		{
			DeltaMouse = static_cast<float>(MouseY - CenterY);
			m_qArcBall = quaternion(vector3(glm::radians(a_fSensitivity * DeltaMouse), 0.0f, 0.0f)) * m_qArcBall;
		}

		SetCursorPos(CenterX, CenterY);//Position the mouse in the center
		//return qArcBall; // return the new quaternion orientation
	}
	/*
	USAGE: Manages the rotation of the camera a_fSpeed is a factor of change DO NOT OVERRIDE
	ARGUMENTS:
	- float a_fSpeed = 0.005f
	OUTPUT: ---
	*/
	virtual void CameraRotation(float a_fSpeed = 0.005f)
	{
		UINT	MouseX, MouseY;		// Coordinates for the mouse
		UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

		//Initialize the position of the pointer to the middle of the screen
		CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
		CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

		//Calculate the position of the mouse and store it
		POINT pt;
		GetCursorPos(&pt);
		MouseX = pt.x;
		MouseY = pt.y;

		//Calculate the difference in view with the angle
		float fAngleX = 0.0f;
		float fAngleY = 0.0f;
		float fDeltaMouse = 0.0f;
		if (MouseX < CenterX)
		{
			fDeltaMouse = static_cast<float>(CenterX - MouseX);
			fAngleY += fDeltaMouse * a_fSpeed;
		}
		else if (MouseX > CenterX)
		{
			fDeltaMouse = static_cast<float>(MouseX - CenterX);
			fAngleY -= fDeltaMouse * a_fSpeed;
		}

		if (MouseY < CenterY)
		{
			fDeltaMouse = static_cast<float>(CenterY - MouseY);
			fAngleX -= fDeltaMouse * a_fSpeed;
		}
		else if (MouseY > CenterY)
		{
			fDeltaMouse = static_cast<float>(MouseY - CenterY);
			fAngleX += fDeltaMouse * a_fSpeed;
		}
		//Change the Yaw and the Pitch of the camera
		m_pCameraMngr->ChangeYaw(fAngleY * 3.0f);
		m_pCameraMngr->ChangePitch(-fAngleX * 3.0f);
		SetCursorPos(CenterX, CenterY);//Position the mouse in the center
	}
	/*
	USAGE: Initialize ReEng variables necessary to create the window
	ARGUMENTS:
	- String a_sWindowName = "ReEng" -> Window name
	OUTPUT: ---
	*/
	virtual void InitWindow(String a_sWindowName = "ReEng")
	{
		//These are the DEFAULT_V3NEG values for the windows construction but they will
		//not have any effect if the .cfg file is present next to the binary folder
		//(the .cfg will be created if not existent using these values, but once
		//created its values will have priority over these)

		// Indicate window properties
		m_pSystem->SetWindowName(a_sWindowName);
		m_pSystem->SetWindowResolution(BTO_RESOLUTIONS::RES_C_1280x720_16x9_HD);
		m_pSystem->SetWindowFullscreen(BTO_RESOLUTIONS::RES_WINDOWED);
		m_pSystem->SetWindowBorderless(false);

		// Set the clear color based on Microsoft's CornflowerBlue (DEFAULT_V3NEG in XNA)
		//if this line is in Init Window it will depend on the .cfg file, if it
		//is on the InitVariables it will always force it regardless of the .cfg
		m_v4ClearColor = vector4(C_BLUE_CORNFLOWER, 1.0f);
	}
	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void)
	{
		//If we are reading the changes the changes, know what file to open
		String sRoot = m_pSystem->m_pFolder->GetFolderRoot();
		String App = m_pSystem->GetAppName();
		App = sRoot + App + ".cfg";

		FileReader reader;
		//If the file doesnt exist, create it and exit this method
		if (reader.ReadFile(App.c_str()) == BTO_OUTPUT::OUT_ERR_FILE_MISSING)
		{
			WriteConfig();
			return;
		}

		//read the file for startup values
		reader.Rewind();
		while (reader.ReadNextLine() == OUT_RUNNING)
		{
			String sWord = reader.GetFirstWord();

			int nLenght = reader.m_sLine.length();
			char* zsTemp = new char[nLenght];

			if (sWord == "Fullscreen:")
			{
				int nValue;
				sscanf_s(reader.m_sLine.c_str(), "Fullscreen: %d", &nValue);
				m_pSystem->SetWindowFullscreen(nValue != 0);
			}
			else if (sWord == "Borderless:")
			{
				int nValue;
				sscanf_s(reader.m_sLine.c_str(), "Borderless: %d", &nValue);
				if (nValue == 0)
					m_pSystem->SetWindowBorderless(false);
				else
					m_pSystem->SetWindowBorderless(true);
			}
			else if (sWord == "Resolution:")
			{
				int nValue1;
				int nValue2;
				sscanf_s(reader.m_sLine.c_str(), "Resolution: [ %d x %d ]", &nValue1, &nValue2);
				m_pSystem->SetWindowWidth(nValue1);
				m_pSystem->SetWindowHeight(nValue2);
			}
			else if (sWord == "Ambient:")
			{
				float fValueX;
				float fValueY;
				float fValueZ;
				sscanf_s(reader.m_sLine.c_str(), "Ambient: [%f,%f,%f]", &fValueX, &fValueY, &fValueZ);
				m_pLightMngr->SetColor(vector3(fValueX, fValueY, fValueZ), 0);
			}
			else if (sWord == "Background:")
			{
				float fValueX;
				float fValueY;
				float fValueZ;
				float fValueW;
				sscanf_s(reader.m_sLine.c_str(), "Background: [%f,%f,%f,%f]", &fValueX, &fValueY, &fValueZ, &fValueW);
				m_v4ClearColor = vector4(fValueX, fValueY, fValueZ, fValueW);
			}
			else if (sWord == "AmbientPower:")
			{
				float fValue;
				sscanf_s(reader.m_sLine.c_str(), "AmbientPower: %f", &fValue);
				m_pLightMngr->SetIntensity(fValue, 0);
			}
			else if (sWord == "Data:")
			{
				sscanf_s(reader.m_sLine.c_str(), "Data: %s", zsTemp, nLenght);
				m_pSystem->m_pFolder->SetFolderData(zsTemp);
			}
			else if (sWord == "BTO:")
			{
				sscanf_s(reader.m_sLine.c_str(), "BTO: %s", zsTemp, nLenght);
				m_pSystem->m_pFolder->SetFolderMBTO(zsTemp);
			}
			else if (sWord == "FBX:")
			{
				sscanf_s(reader.m_sLine.c_str(), "FBX: %s", zsTemp, nLenght);
				m_pSystem->m_pFolder->SetFolderMFBX(zsTemp);
			}
			else if (sWord == "OBJ:")
			{
				sscanf_s(reader.m_sLine.c_str(), "OBJ: %s", zsTemp, nLenght);
				m_pSystem->m_pFolder->SetFolderMOBJ(zsTemp);
			}
			else if (sWord == "Level:")
			{
				sscanf_s(reader.m_sLine.c_str(), "Level: %s", zsTemp, nLenght);
				m_pSystem->m_pFolder->SetFolderLVL(zsTemp);
			}
			else if (sWord == "Textures:")
			{
				sscanf_s(reader.m_sLine.c_str(), "Textures: %s", zsTemp, nLenght);
				m_pSystem->m_pFolder->SetFolderTextures(zsTemp);
			}

			delete[] zsTemp;
			zsTemp = nullptr;
		}
		reader.CloseFile();
	}
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void)
	{
		// Write the configuration for this application
		String sRoot = m_pSystem->m_pFolder->GetFolderRoot();
		String App = m_pSystem->GetAppName();
		App = sRoot + App + ".cfg";

		FILE *pFile;
		fopen_s(&pFile, App.c_str(), "w");
		if (!pFile)	//If we couldn't create the file we exit without changes.
			return;

		//Save default values for a config file
		rewind(pFile);
		fprintf(pFile, "# Configuration file for the program: %s", m_pSystem->GetAppName().c_str());

		fprintf(pFile, "\n\nFullscreen: ");
		if (m_pSystem->IsWindowFullscreen())
			fprintf(pFile, "1");
		else
			fprintf(pFile, "0");

		fprintf(pFile, "\nBorderless: ");
		if (m_pSystem->IsWindowBorderless())
			fprintf(pFile, "1");
		else
			fprintf(pFile, "0");

		fprintf(pFile, "\nContext: OPT_OPENGL3X"); //Only openGL3X context is supported ATM

		fprintf(pFile, "\n\n# Resolution: [ 640 x 480 ]");
		fprintf(pFile, "\n# Resolution: [ 1280 x 720 ]");
		fprintf(pFile, "\n# Resolution: [ 1680 x 1050 ]");
		fprintf(pFile, "\n# Resolution: [ 1920 x 1080 ]");
		fprintf(pFile, "\n# Resolution: [ 2650 x 1440 ]");
		fprintf(pFile, "\nResolution: [ %d x %d ]", m_pSystem->GetWindowWidth(), m_pSystem->GetWindowHeight());

		fprintf(pFile, "\n\nAmbient: [%.2f,%.2f,%.2f]",
			m_pLightMngr->GetColor(0).r, m_pLightMngr->GetColor(0).g, m_pLightMngr->GetColor(0).b);
		fprintf(pFile, "\nAmbientPower: %.2f", m_pLightMngr->GetIntensity(0));

		fprintf(pFile, "\n\nBackground: [%.3f,%.3f,%.3f,%.3f]",
			m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);

		fprintf(pFile, "\n\n# Folders:");

		fprintf(pFile, "\nData:		%s", m_pSystem->m_pFolder->GetFolderData().c_str());
		fprintf(pFile, "\nBTO:		%s", m_pSystem->m_pFolder->GetFolderMBTO().c_str());
		fprintf(pFile, "\nFBX:		%s", m_pSystem->m_pFolder->GetFolderMFBX().c_str());
		fprintf(pFile, "\nOBJ:		%s", m_pSystem->m_pFolder->GetFolderMOBJ().c_str());
		fprintf(pFile, "\nLevel:		%s", m_pSystem->m_pFolder->GetFolderLVL().c_str());
		fprintf(pFile, "\nTextures:	%s", m_pSystem->m_pFolder->GetFolderTextures().c_str());

		fclose(pFile);
	}
	/*
	USAGE: Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void InitVariables(void){}
	/*
	USAGE:	Will initialize the maximum frame rate and the max delta frame 
	ARGUMENTS: 
	- float a_fMaxFrameRate -> maximum frame rate the system can execute
	OUTPUT: ---
	*/
	virtual void SetMaxFramerate(float a_fFrameRateLimit) final { m_dMinDelta = 1.0f / a_fFrameRateLimit; }
	/*
	USAGE: Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Release(void)
	{
		SafeDelete(m_pWindow); // destroy the allocated window
		// Release all the singletons used in the dll
		glDeleteFramebuffers(1, &m_nFrameBuffer);
		glDeleteTextures(1, &m_nDepthBuffer);
		glDeleteRenderbuffers(1, &m_nDawingTexture);
		ReleaseAllSingletons();
	}
	/*
	USAGE: Updates the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Update(void)
	{
		//Update the system so it knows how much time has passed since the last call
		m_pSystem->Update();

		//Add the sphere to the render queue
		m_pMeshMngr->AddTorusToRenderList(glm::rotate(IDENTITY_M4, 90.0f, vector3(90.0f, 0.0f, 0.0f)) * ToMatrix4(m_qArcBall), C_RED, RENDER_SOLID | RENDER_WIRE);

		//Is the arcball active?
		ArcBall();

		//Is the first person camera active?
		if (m_bFPC == true)
			CameraRotation();
			
		//Indicate the FPS
		int nFPS = m_pSystem->GetFPS();
		//print info into the console
		printf("FPS: %d            \r", nFPS);//print the Frames per Second
		//Print info on the screen
		m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), C_YELLOW);
		m_pMeshMngr->Print("FPS:");
		m_pMeshMngr->Print(std::to_string(nFPS), C_RED);
	}
	/*
	USAGE: Displays the scene
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Display(void)
	{
		//clear the screen
		ClearScreen();
		//Render the grid based on the camera's mode:
		//m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
		m_uRenderCallCount = m_pMeshMngr->Render(); //renders the render list
		m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
		m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
	}
	/*
	USAGE: Runs faster than the update
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void Idle(void) {}
	/*
	USAGE: Manage the response of key presses
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessKeyboard(void){}
	/*
	USAGE: Manage the response of key presses and mouse position
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessMouse(void){}
	/*
	USAGE: Manage the response of gamepad controllers
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ProcessJoystick(void){}
};

} //namespace Simplex

#endif //__SIMPLEXAPPCLASS_H_

  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */