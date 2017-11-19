#include "BasicX\System\Window.h"
#include "BasicX\System\SystemSingleton.h"
using namespace BasicX;
Window::Window()
{
	Init();
}

Window::Window(HINSTANCE hInstance, int nCmdShow, WNDPROC WndProc)
{
	Init();
	m_hInstance = hInstance;
	m_nCommandShow = nCmdShow;
	m_Callback = WndProc;
}

void Window::Init(void)
{
	m_hInstance = nullptr;
	m_hWindowHandler = nullptr;
	m_nCommandShow = 0;
	m_Callback = nullptr;

	m_bBorderless = false;
	m_bFullscreen = false;
	m_sWindowName = L"Window";

	m_bWindowCrated = false;

	m_pSystem = SystemSingleton::GetInstance();
}

Window::Window(const Window& other) { }

Window& Window::operator=(const Window& other) { return *this; }

void Window::SetWindowInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}

void Window::SetWindowCallback(WNDPROC WndProc)
{
	m_Callback = WndProc;
}

void Window::SetIncomingArguments(int nCmdShow)
{
	m_nCommandShow = nCmdShow;
}

void Window::SetFullscreen(bool input)
{
	m_bFullscreen = input;
}

void Window::SetBorderless(bool input)
{
	m_bBorderless = input;
}

int Window::CreateMEWindow( LPCWSTR windowName, int width, int height)
{
	/*
		First we check if we have the required information to create the window
	*/
	if(m_Callback == nullptr)
	{
		//Callback to run our window
		MessageBox( NULL, L"Callback not defined", L"Init error", MB_ICONEXCLAMATION );
		exit(0);
		return E_FAIL;
	}
	if(m_hInstance == nullptr)
	{
		//Window Handler to keep track of it
		MessageBox( NULL, L"Window instance not defined", L"Init error", MB_ICONEXCLAMATION );
		exit(0);
		return E_FAIL;
	}
	if(m_nCommandShow == 0)
	{
		//Number of arguments
		MessageBox( NULL, L"Command Show not defined", L"Init error", MB_ICONEXCLAMATION );
		exit(0);
		return E_FAIL;
	}

	//Set the value to the provided arguments
	m_pSystem->SetWindowWidth(width);
	m_pSystem->SetWindowHeight(height);
	m_sWindowName = windowName;
	std::wstring sWTemp = windowName;
	String sTemp( sWTemp.begin(), sWTemp.end() );
	m_pSystem->SetWindowName(sTemp);
	
	WNDCLASSEX wc; //Window Information Container
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = 0;
	wc.lpfnWndProc   = m_Callback;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hInstance;
	wc.hIcon         = LoadIcon(wc.hInstance, ( LPCTSTR )IDI_BTO);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = L"MEWINDOW";
	wc.hIconSm       = LoadIcon(wc.hInstance, ( LPCTSTR )IDI_BTO);
	
	//Register the container
	if(!RegisterClassEx(&wc))
	{
		//If this fails we have no window and we should exit the program
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		exit(0);
		return E_FAIL;
	}

	//Check if we are in fullscreen if so, there is more information to be provided
	if(m_bFullscreen)
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= 32;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer user Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, 
				L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", 
				L"BTO Window",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				m_bFullscreen = false;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				exit(0); //User decides not to continue
				return E_FAIL;
			}
		}
	}

	//Setting window stile accordingly
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style

	if (m_bFullscreen)	// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;					// Window Extended Style
		ShowCursor(FALSE);								// Hide Mouse Pointer
	}

	DWORD dwWindowStyle;
	if (m_bBorderless)//Do we want Borders?
	{
		dwWindowStyle = WS_POPUP; // Window Classic Style
		//dwWindowStyle = WS_POPUPWINDOW;
		//dwWindowStyle = WS_BORDER; //Working no real max
		
	}

	else
	{
		dwWindowStyle = WS_OVERLAPPEDWINDOW; // Window Borderless Style
	}

	//dwWindowStyle = WS_BORDER;
	//dwWindowStyle = WS_OVERLAPPEDWINDOW;

	//dwWindowStyle = WS_POPUP;
	//dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	//dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
	//dwWindowStyle = WS_POPUP;

	RECT rc = { (long)0, (long)0, (long)width, (long)height };// Grabs Rectangle Upper Left / Lower Right Values
	AdjustWindowRectEx(&rc, dwWindowStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	//Center the screen
	int nWindowPosX = (GetSystemMetrics(SM_CXSCREEN) - width)  / 2;// Find the middle point of the screen and subtract half the width
	m_pSystem->SetWindowX(nWindowPosX);
	int nWindowPosY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;// Find the middle point of the screen and subtract half the height
	m_pSystem->SetWindowY(nWindowPosY);
	
	//Create the window and store the returning handler in our window handler
	m_hWindowHandler = CreateWindowEx(	dwExStyle,
										L"MEWINDOW",
										m_sWindowName,
										dwWindowStyle |
										WS_CLIPSIBLINGS |
										WS_CLIPCHILDREN,
										nWindowPosX, nWindowPosY,
										width, height,
										NULL, NULL,
										m_hInstance,
										NULL);
	m_pSystem->SetWindowWidth(width);
	m_pSystem->SetWindowHeight(height);
	//If it failed...
	if(m_hWindowHandler == NULL)
	{
		//Inform the user and return fail
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		exit(0);
		return E_FAIL;
	}
	
	ShowWindow(m_hWindowHandler, m_nCommandShow); //Show the window
	UpdateWindow(m_hWindowHandler); //Update the window

	m_bWindowCrated = true;
	
	return NOERROR;
}

HWND Window::GetHandler(void)
{
	return m_hWindowHandler;
}

void Window::CreateConsoleWindow(void)
{
	if(AllocConsole())
	{
		FILE* stream;
		_wfreopen_s(&stream, TEXT("CONIN$"), TEXT("rb"), stdin);
		_wfreopen_s(&stream, TEXT("CONOUT$"), TEXT("wb"), stdout);
		_wfreopen_s(&stream, TEXT("CONOUT$"), TEXT("wb"), stderr);
	}
}

void Window::CalculateWindowSize(void)
{
	RECT var;
	GetWindowRect(m_hWindowHandler, &var);
	m_pSystem->SetWindowX(var.left);
	m_pSystem->SetWindowY(var.top);
	int nWidth = var.right - var.left; //Window width
	int nHeight = var.bottom - var.top; //Window height
	m_pSystem->SetWindowWidth(nWidth);
	m_pSystem->SetWindowHeight(nHeight);
}
void Window::GetPosition(int* a_nPosX, int* a_nPosY)
{
	CalculateWindowSize();

	*a_nPosX = m_pSystem->GetWindowX();
	*a_nPosY = m_pSystem->GetWindowY();
}

void Window::GetSize(int* a_nWidth, int* a_nHeight)
{
	CalculateWindowSize();

	*a_nWidth = m_pSystem->GetWindowWidth();
	*a_nHeight = m_pSystem->GetWindowHeight();
}

int Window::GetWidth(void){ return m_pSystem->GetWindowWidth(); }
int Window::GetHeight(void){ return m_pSystem->GetWindowHeight(); }
void Window::GetRenderArea(int* a_nWidth, int* a_nHeight)
{
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, a_nWidth);
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, a_nHeight);
}
