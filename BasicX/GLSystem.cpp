#include "BasicX\System\GLSystem.h"
#include "BasicX\System\SystemSingleton.h"

#include <iostream>
using namespace BasicX;
//-----------------------------------------------------------------------------------------------------------
// GLSystem
//-----------------------------------------------------------------------------------------------------------
GLSystem* GLSystem::m_pInstance = nullptr;
GLSystem* GLSystem::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new GLSystem();
	}
	return m_pInstance;
}
GLSystem::GLSystem(){Init();}
GLSystem::GLSystem(GLSystem const& other){}
GLSystem& GLSystem::operator=(GLSystem const& other) {	return *this; }
GLSystem::~GLSystem(){Release();};
void GLSystem::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
//--- Non Standard Singleton Methods
void  GLSystem::Release(void)
{
	//No pointers allocated, so nothing to do here
}

void GLSystem::Init(void)
{
	m_hDC = NULL;
	m_hRC = NULL;
	m_fGLVersion = 0.0f;
	m_bForceOldGL = false;
}

void GLSystem::ForceOldOpenGL(bool input)
{
	m_bForceOldGL = input;
}

int GLSystem::DrawOldGLScene(GLvoid)					// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Model-View Matrix
	glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glBegin(GL_TRIANGLES);								// Drawing Using Triangles
		glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
	glEnd();											// Finished Drawing The Triangle
	glTranslatef(3.0f,0.0f,0.0f);						// Move Right 3 Units
	glBegin(GL_QUADS);									// Draw A Quad
		glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
		glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
		glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
		glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	glEnd();											// OUT_DONE Drawing The Quad

	SwapBuffers(m_hDC);
	return TRUE;										// Keep Going
}
HRESULT GLSystem::InitGLDevice(HWND g_hWnd)
{
	if (!(m_hDC=GetDC(g_hWnd)))				// Did We Get A Device Context?
	{
		MessageBox( NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=	// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Size Of This Pixel Format Descriptor
		1,								// Version Number
		PFD_DRAW_TO_WINDOW |			// Format Must Support Window
		PFD_SUPPORT_OPENGL |			// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,				// Must Support Double Buffering
		PFD_TYPE_RGBA,					// Request An RGBA Format
		16,								// Select Our Color Depth
		0, 0, 0, 0, 0, 0,				// Color Bits Ignored
		0,								// No Alpha Buffer
		0,								// Shift Bit Ignored
		0,								// No Accumulation Buffer
		0, 0, 0, 0,						// Accumulation Bits Ignored
		32,								// 32Bit Z-Buffer (Depth Buffer)  
		0,								// No Stencil Buffer
		0,								// No Auxiliary Buffer
		PFD_MAIN_PLANE,					// Main Drawing Layer
		0,								// Reserved
		0, 0, 0							// Layer Masks Ignored
	};

	GLuint PixelFormat;								// Holds The Results After Searching For A Match
	if (!(PixelFormat = ChoosePixelFormat(m_hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		MessageBox( NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(m_hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		MessageBox( NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(m_hRC=wglCreateContext(m_hDC)))			// Are We Able To Get A Rendering Context?
	{
		MessageBox( NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	HGLRC tempHRC = wglCreateContext(m_hDC);	// Create an OpenGL 2.1 context for our device context
	if(!wglMakeCurrent(m_hDC,tempHRC))			// Try To Activate The Rendering Context
	{
		MessageBox( NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return FALSE;
	}
	int nMajor = 5;
	int nMinor = 5;

	int attributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4, // Set the major version of OpenGL
		WGL_CONTEXT_MINOR_VERSION_ARB, 5, // Set the minor version of OpenGL
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, // Set our OpenGL context to be forward compatible
		0
	};
	
	if (wglewIsSupported("WGL_ARB_create_context") == 1 && m_bForceOldGL == false) // If the OpenGL 3.x context creation extension is available
	{ 
		m_hRC = wglCreateContextAttribsARB(m_hDC, NULL, attributes);//Creates a 5.5 context
		while (m_hRC == NULL && nMajor > 2)
		{
			nMinor--;
			if (nMinor < 0)
			{
				nMajor--;
				nMinor = 9;
			}
			attributes[1] = nMajor;
			attributes[3] = nMinor;
			
			m_hRC = wglCreateContextAttribsARB(m_hDC, NULL, attributes); // Create and OpenGL 4.5 context based on the given attributes
		}
		wglMakeCurrent(NULL, NULL); // Remove the temporary context from being active
		wglDeleteContext(tempHRC); // Delete the temporary context (OpenGL 2.1)
		wglMakeCurrent(m_hDC, m_hRC); // Make our context current (Whatever context was created)
	}
	else //OpenGL 2.0
	{
		m_fGLVersion = 2.0f;
		m_hRC = tempHRC; // If we didn't have support for OpenGL 3.x and up, use the OpenGL 2.1 context

		RECT rc;
		GetClientRect( g_hWnd, &rc );
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;

		ShowWindow(g_hWnd,SW_SHOW);						// Show The Window
		SetForegroundWindow(g_hWnd);						// Slightly Higher Priority
		SetFocus(g_hWnd);									// Sets Keyboard Focus To The Window
		
		//This uses the System's information to generate the projection
		SystemSingleton* pSystem = SystemSingleton::GetInstance();
		int nWidth = pSystem->GetWindowWidth();
		int nHeight = pSystem->GetWindowHeight();

		glViewport( 0, 0, nWidth, nHeight);					// Reset The Current Viewport

		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The Window
		gluPerspective(45.0f,(GLfloat)nWidth/(GLfloat)nHeight,0.1f,1000.0f);

		glMatrixMode(GL_MODELVIEW);							// Select The Model-View Matrix
		glLoadIdentity();									// Reset The Model-View Matrix

		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
			
		return TRUE;										// Initialization Went OK
	}

	int glVersion[2] = {-1, -1}; // Set some DEFAULT_V3NEG values for the version
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]); // Get back the OpenGL major version we are using
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]); // Get back the OpenGL minor version we are using

	std::cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << std::endl; // Output which version of OpenGL we are using
	m_fGLVersion = static_cast <float>(glVersion[0]) + (static_cast <float>(glVersion[1]) * 0.1f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);	// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do

	glEnable(GL_CULL_FACE);

	printf("\n");
	

	return TRUE; // Success
}

HDC GLSystem::GetDeviceContext(GLvoid)
{
	return m_hDC;
}

float GLSystem::GetGLVersion(void)
{
	return m_fGLVersion;
}

bool GLSystem::IsNewOpenGLRunning(void)
{
	return m_fGLVersion >= 3.0;
}

void GLSystem::GLSwapBuffers(void)
{
	SwapBuffers(m_hDC);
}
bool GLSystem::UpdateRenderTarget(GLuint& a_nFrameBuffer, GLuint& a_nDepthBuffer, GLuint& a_nTextureIndex)
{
	if (a_nFrameBuffer == 0 || a_nDepthBuffer == 0 || a_nTextureIndex == 0)
		return false;

	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	uint width = pSystem->GetWindowWidth();
	uint height = pSystem->GetWindowHeight();

	glBindFramebuffer(GL_FRAMEBUFFER, a_nFrameBuffer);

	glBindTexture(GL_TEXTURE_2D, a_nTextureIndex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindRenderbuffer(GL_RENDERBUFFER, a_nDepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, a_nDepthBuffer);

	//// Alternative : Depth texture. Slower, but you can sample it later in your shader
	//GLuint depthTexture;
	//glGenTextures(1, &depthTexture);
	//glBindTexture(GL_TEXTURE_2D, depthTexture);
	//glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, 1024, 768, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, a_nTextureIndex, 0);

	//// Depth texture alternative : 
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	return (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE); //return falure or success
}
bool GLSystem::GenerateRenderTarget(GLuint& a_nFrameBuffer, GLuint& a_nDepthBuffer, GLuint& a_nTextureIndex)
{
	SystemSingleton* pSystem = SystemSingleton::GetInstance();

	glGenFramebuffers(1, &a_nFrameBuffer);	
	glGenTextures(1, &a_nTextureIndex);
	glGenRenderbuffers(1, &a_nDepthBuffer);
	return UpdateRenderTarget(a_nFrameBuffer, a_nDepthBuffer, a_nTextureIndex);
}