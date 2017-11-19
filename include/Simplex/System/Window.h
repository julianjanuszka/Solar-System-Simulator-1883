/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
	Provides a fullscreen mode and icon to 
	http://www.winprog.org/tutorial/simple_window.html 
	Adapted into a class.
Date: 2014/05
Modified: 2017/06
----------------------------------------------*/
#ifndef __WINDOWCLASS_H_
#define __WINDOWCLASS_H_

#include <windows.h>
#include "Resource.h"
#include "Simplex\system\Definitions.h" //Simplex basic Definitions
#include "Simplex\System\SystemSingleton.h"

namespace Simplex
{

//Window class
class SimplexDLL Window
{
	bool m_bFullscreen = false; //Run in fullscreen mode?
	bool m_bBorderless = false; //Run with borders?
	bool m_bWindowCrated = false; //Window has been created

	int m_nCommandShow = 0; //Number of arguments

	LPCWSTR m_sWindowName; //Name of the window
	HWND m_hWindowHandler; //Window handler

	HINSTANCE m_hInstance; //Window Instance
	WNDPROC m_Callback; //Associated Callback for this window

	SystemSingleton* m_pSystem; //System singleton for ReEngine
	
public:
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	Window(void);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Window(HINSTANCE a_hInstance, int a_nCmdShow, WNDPROC a_WndProc);
	/*
	USAGE:Gets the window size.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateWindowSize(void);
	/*
	USAGE: Calculates the render area in the gl window
	ARGUMENTS:
	-	int* a_nPosX -> output; Gets the position x
	-	int* a_nPosY -> output; Gets the position y
	OUTPUT: ---
	*/
	void GetPosition(int* a_nPosX, int* a_nPosY);
	/*
	USAGE: Calculates the size of the window
	ARGUMENTS:
	-	int* a_nWidth -> output; Gets the width
	-	int* a_nHeight -> output; Gets the height
	OUTPUT: ---
	*/
	void GetSize(int* a_nWidth, int* a_nHeight);
	/*
	USAGE: Calculates the render area in the gl window
	ARGUMENTS:
	-	int* a_nWidth -> output; Gets the width
	-	int* a_nHeight -> output; Gets the height
	OUTPUT: ---
	*/
	void GetRenderArea(int* a_nWidth, int* a_nHeight);
	/*
	USAGE:Sets the window Instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetWindowInstance(HINSTANCE a_hInstance);
	/*
	USAGE:Sets the window callback
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetWindowCallback(WNDPROC a_WndProc);
	/*
	USAGE:Sets the number of incoming arguments
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetIncomingArguments(int a_nCmdShow);
	/*
	USAGE: Creates window with the provided arguments
	ARGUMENTS:
	-	LPCWSTR windowName = L"Window" -> Name of the window
	-	int width = 1280 -> width of the window
	-	int height = 720 -> height of the window
	OUTPUT:
	*/
	int CreateMEWindow(LPCWSTR a_windowName = L"Window", int a_nWidth = 1280, int a_nHeight = 720);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetWidth(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetHeight(void);
	/*
	USAGE:Returns the window handler
	ARGUMENTS: ---
	OUTPUT:
	*/
	HWND GetHandler(void);
	/*
	USAGE:Sets whether or not the program will run in fullscreen
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFullscreen(bool a_bInput = true);
	/*
	USAGE:Sets whether or not the window will be borderless
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetBorderless(bool a_bInput = true);
	/*
	USAGE:Allocates a console window for output
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CreateConsoleWindow(void);
	/*
	USAGE: Gets the Mouse coordinates in window space
	ARGUMENTS: ---
	OUTPUT: mouse coordinates
	*/
	vector3 GetMouseCoordinates(void);
	
private:
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Window(const Window& other);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Window& operator=(const Window& other);
	/*
	USAGE:Initializes the member variables
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

} //namespace Simplex

#endif /*__WINDOWCLASS_H__*/
  /*
  USAGE:
  ARGUMENTS: ---
  OUTPUT: ---
  */