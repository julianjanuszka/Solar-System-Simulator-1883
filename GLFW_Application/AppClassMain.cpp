#include "AppClass.h"
GLFWApp* GLFWApp::m_pSelfPointer = nullptr;
GLFWApp::GLFWApp() {}
GLFWApp::GLFWApp(GLFWApp const& input) {}
GLFWApp& GLFWApp::operator=(GLFWApp const& input) { return *this; }
GLFWApp::~GLFWApp(void) 
{
	Release();
	// Release the Simplex singletons
	Simplex::ReleaseAllSingletons();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}
void GLFWApp::Run(void)
{
	//Initialize the system with the fields recollected by the constructor
	Init();
	do {
		Update();
		Display();
		Idle();
	} while (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&	glfwWindowShouldClose(m_pWindow) == 0);// Check if the ESC key was pressed or the window was closed
}
void GLFWApp::ClearScreen(vector4 a_v4ClearColor)
{
	if (a_v4ClearColor != vector4(-1.0f))
	{
		m_v4ClearColor = a_v4ClearColor;
	}
	glClearColor(m_v4ClearColor.r, m_v4ClearColor.g, m_v4ClearColor.b, m_v4ClearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
}
void GLFWApp::Reshape(void)
{
	int width, height;
	glfwGetWindowSize(m_pWindow, &width, &height);
	m_pSystem->SetWindowWidth(width);
	m_pSystem->SetWindowHeight(height);
	m_pMeshMngr->SetRenderTarget(0, 0, 0, width, height);
	
	int x, y;
	glfwGetWindowPos(m_pWindow, &x, &y);
	m_pSystem->SetWindowX(x);
	m_pSystem->SetWindowY(y);
}
void GLFWApp::Init(void)
{
	//set the self pointer of the app
	m_pSelfPointer = this;
	//Init GLFW Window
	InitWindow("GLFW_APP");
	//Set the maximum framerate of the app
	SetMaxFramerate(60.0f);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(m_pWindow, GLFW_STICKY_KEYS, GL_TRUE);
	//Init Simplex basic Systems
	m_pSystem = SystemSingleton::GetInstance();
	m_pMeshMngr = MeshManager::GetInstance();
	m_pCameraMngr = CameraManager::GetInstance();
	//Change size of render target
	Reshape();
	//Init App variables
	InitVariables();
		//Set callbacks
	glfwSetKeyCallback(m_pWindow, key_callback);
	glfwSetMouseButtonCallback(m_pWindow, mouse_button_callback);
}
void GLFWApp::InitWindow(String a_sWindowName)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	m_pWindow = glfwCreateWindow(1024, 768, a_sWindowName.c_str(), NULL, NULL);
	if (m_pWindow == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_pWindow);

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
void GLFWApp::ReadConfig(void) {}
void GLFWApp::WriteConfig(void) {}
void GLFWApp::SetMaxFramerate(float a_fFrameRateLimit) { m_dMinDelta = 1.0f / a_fFrameRateLimit; }
void GLFWApp::ArcBall(float a_fSensitivity)
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
void GLFWApp::CameraRotation(float a_fSpeed)
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
void GLFWApp::Idle(void)
{
	//runs after Display, nothing to do in this app
}