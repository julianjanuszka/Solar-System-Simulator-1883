#include "AppClass.h"
SDLApp* SDLApp::m_pSelfPointer = nullptr;
SDLApp::SDLApp() {}
SDLApp::SDLApp(SDLApp const& input) {}
SDLApp& SDLApp::operator=(SDLApp const& input) { return *this; }
SDLApp::~SDLApp(void) 
{
	Release();
	// Release the Simplex singletons
	Simplex::ReleaseAllSingletons();
}
void SDLApp::Run(void)
{
	//Initialize the system with the fields recollected by the constructor
	Init();
	// run the main loop
	bool running = true;

	Reshape();

	SDL_Event windowEvent;
	while (running)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			switch (windowEvent.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (windowEvent.key.keysym.sym == SDLK_ESCAPE)
					running = false;
				else
					ProcessKeyboard(windowEvent);
				break;
			case SDL_MOUSEBUTTONDOWN:
				ProcessMousePress(windowEvent);
				break;
			case SDL_MOUSEBUTTONUP:
				ProcessMouseRelease(windowEvent);
				break;
			}
		}
		Update();
		Display();
		Idle();
	}
}
void SDLApp::ClearScreen(vector4 a_v4ClearColor)
{
	if (a_v4ClearColor != vector4(-1.0f))
	{
		m_v4ClearColor = a_v4ClearColor;
	}
	glClearColor(m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
}
void SDLApp::Reshape(void)
{
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	int posX, posY;
	SDL_GetWindowPosition(window, &posX, &posY);

	m_pSystem->SetWindowX(posX);
	m_pSystem->SetWindowY(posY);
	m_pSystem->SetWindowWidth(width);
	m_pSystem->SetWindowHeight(height);

	// adjust the viewport when the window is resized
	glViewport(0, 0, width, height);
	m_pMeshMngr->SetRenderTarget(0, 0, 0, width, height);
}
void SDLApp::Init(void)
{
	//set the self pointer of the app
	m_pSelfPointer = this;
	
	//Init GLFW Window
	InitWindow("SDL_APP");

	//Set the maximum framerate of the app
	SetMaxFramerate(60.0f);
	
	//Init System
	m_pSystem = SystemSingleton::GetInstance();

	//Init Camera
	m_pCameraMngr = CameraManager::GetInstance();
	
	//Init Mesh Manager
	m_pMeshMngr = MeshManager::GetInstance();

	//Init sizes
	Reshape();

	//Init variables
	InitVariables();
}
void SDLApp::InitWindow(String a_sWindowName)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	window = SDL_CreateWindow(a_sWindowName.c_str(), 50, 50, 600, 600, SDL_WINDOW_OPENGL);
	
	context = SDL_GL_CreateContext(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);	// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do

	glEnable(GL_CULL_FACE);

	// Set the clear color based on Microsoft's CornflowerBlue (DEFAULT_V3NEG in XNA)
	//if this line is in Init Window it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(C_BLUE_CORNFLOWER, 1.0f);
}
void SDLApp::ReadConfig(void) {}
void SDLApp::WriteConfig(void) {}
void SDLApp::SetMaxFramerate(float a_fFrameRateLimit) { m_dMinDelta = 1.0f / a_fFrameRateLimit; }
void SDLApp::ArcBall(float a_fSensitivity)
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
void SDLApp::CameraRotation(float a_fSpeed)
{
	if (m_bFPC == false)
		return;

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
void SDLApp::Idle(void)
{
	//runs after Display, nothing to do in this app

}