#include "AppClass.h"
SFMLApp* SFMLApp::m_pSelfPointer = nullptr;
SFMLApp::SFMLApp() {}
SFMLApp::SFMLApp(SFMLApp const& input) {}
SFMLApp& SFMLApp::operator=(SFMLApp const& input) { return *this; }
SFMLApp::~SFMLApp(void) 
{
	Release();
	// Release the Simplex singletons
	Simplex::ReleaseAllSingletons();
	SafeDelete(window);
}
void SFMLApp::Run(void)
{
	//Initialize the system with the fields recollected by the constructor
	Init();
	// run the main loop
	bool running = true;
	sf::Vector2i pos = window->getPosition();
	sf::Vector2u size = window->getSize();
	while (running)
	{
		// handle events
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				Reshape();
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				if (pos != window->getPosition())
				{
					pos = window->getPosition();
					size = window->getSize();

					m_pSystem->SetWindowX(pos.x);
					m_pSystem->SetWindowY(pos.y);
					m_pSystem->SetWindowWidth(size.x);
					m_pSystem->SetWindowHeight(size.y);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				ProcessMousePressed(event);
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				ProcessMouseReleased(event);
			}
		}
		Update();
		Display();
		Idle();
	}
}
void SFMLApp::ClearScreen(vector4 a_v4ClearColor)
{
	if (a_v4ClearColor != vector4(-1.0f))
	{
		m_v4ClearColor = a_v4ClearColor;
	}
	glClearColor(m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
}
void SFMLApp::Reshape(void)
{
	sf::Vector2i pos = window->getPosition();
	sf::Vector2u size = window->getSize();

	m_pSystem->SetWindowX(pos.x);
	m_pSystem->SetWindowY(pos.y);
	m_pSystem->SetWindowWidth(size.x);
	m_pSystem->SetWindowHeight(size.y);

	// adjust the viewport when the window is resized
	glViewport(0, 0, size.x, size.y);
	m_pMeshMngr->SetRenderTarget(0, 0, 0, size.x, size.y);
}
void SFMLApp::Init(void)
{
	//set the self pointer of the app
	m_pSelfPointer = this;
	
	//Init GLFW Window
	InitWindow("SFML_APP");

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
void SFMLApp::InitWindow(String a_sWindowName)
{
	window = new sf::Window(sf::VideoMode(800, 600), a_sWindowName, sf::Style::Default, sf::ContextSettings(32));
	window->setVerticalSyncEnabled(true);
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
void SFMLApp::ReadConfig(void) {}
void SFMLApp::WriteConfig(void) {}
void SFMLApp::SetMaxFramerate(float a_fFrameRateLimit) { m_dMinDelta = 1.0f / a_fFrameRateLimit; }
void SFMLApp::ArcBall(float a_fSensitivity)
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
void SFMLApp::CameraRotation(float a_fSpeed)
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
void SFMLApp::Idle(void)
{
	//runs after Display, nothing to do in this app
}