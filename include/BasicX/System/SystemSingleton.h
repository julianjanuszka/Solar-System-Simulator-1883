/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/06
----------------------------------------------*/
#ifndef __BASICXSYSTEM_H_
#define __BASICXSYSTEM_H_

#include "BasicX\System\Folder.h"
#include <random>

namespace BasicX
{

	//System Class
	class BasicXDLL SystemSingleton
	{
		static SystemSingleton* m_pInstance; // Singleton

		bool m_bWindowFullscreen = false; // Is window Fullscreen?
		bool m_bWindowBorderless = false; // Is window Borderless?
		bool m_bConsoleWindow = false; // Using console Window?

		int m_nWindowWidth = 1280; // Window width
		int m_nWindowHeight = 720; // Window height
		int m_nWindowX = 0; // Window Position X
		int m_nWindowY = 0; // Window Position Y

		int m_nFPS = 60; //Frames per Second

		uint m_uMaxFPS = 120; //Maximum Frames per Second

		String m_sWindowName = "BasicX - Window"; // Window Name
		String m_sAppName = "";//Name of the Application

		std::vector<DWORD> m_clockList;//clocks list
		std::vector<DWORD> m_deltaList;//deltas list
		std::vector<float> m_countdownList;//countdown list

	public:
		Folder* m_pFolder; //Folder that contains the address of resources
						   /*
						   USAGE: Singleton accessor
						   ARGUMENTS:
						   OUTPUT:
						   */
		static SystemSingleton* GetInstance();
		/*
		USAGE: Singleton Release
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		static void ReleaseInstance(void);
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT:
		*/
		String GetAppName(void);
		/*
		USAGE:
		ARGUMENTS:
		OUTPUT: ---
		*/
		void SetWindowBorderless(bool a_bBorderless = true);
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT:
		*/
		bool IsWindowBorderless(void);
		/*
		USAGE: Will set the window to fullscreen mode in the desired resolution
		ARGUMENTS:
		BTO_RESOLUTIONS a_Resolution = BTO_RESOLUTIONS::HD_1280X720 -> resolution of the screen
		OUTPUT: ---
		*/
		void SetWindowFullscreen(bool a_bFullScreen);
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT:
		*/
		bool IsWindowFullscreen(void);
		/*
		USAGE:
		ARGUMENTS:
		OUTPUT: ---
		*/
		void SetWindowResolution(uint a_nResolution = BTO_RESOLUTIONS::RES_C_1280x720_16x9_HD);
		/*
		USAGE:
		ARGUMENTS:
		OUTPUT: ---
		*/
		void SetWindowWidth(uint a_nWidth);
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT:
		*/
		uint GetWindowWidth(void);
		/*
		USAGE:
		ARGUMENTS:
		OUTPUT: ---
		*/
		void SetWindowHeight(uint a_nHeight);
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT:
		*/
		uint GetWindowHeight(void);
		/*
		USAGE:
		ARGUMENTS:
		OUTPUT: ---
		*/
		void SetWindowX(int a_nX);
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT:
		*/
		int GetWindowX(void);
		/*
		USAGE:
		ARGUMENTS:
		OUTPUT: ---
		*/
		void SetWindowY(int a_nY);
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT:
		*/
		int GetWindowY(void);
		/*
		USAGE: Calculates the render area in the gl window
		ARGUMENTS:
		int* a_nPosX -> output; Gets the position x
		int* a_nPosY -> output; Gets the position y
		OUTPUT: ---
		*/
		void GetWindowPosition(int* a_nPosX, int* a_nPosY);
		/*
		USAGE: Calculates the size of the window
		ARGUMENTS:
		int* a_nWidth -> output; Gets the width
		int* a_nHeight -> output; Gets the height
		OUTPUT: ---
		*/
		void GetWindowSize(int* a_nWidth, int* a_nHeight);
		/*
		USAGE:
		ARGUMENTS:
		OUTPUT:
		*/
		void SetWindowName(String a_sWindowName);
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT:
		*/
		String GetWindowName(void);
		/*
		USAGE: Sets the maximum frame rate allowed in the application
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void SetMaxFrameRate(uint a_uMax);
		/*
		USAGE: Gets the maximum frame rate allowed in the application
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		uint GetMaxFrameRate(void);
		/*
		USAGE: Asks for the value of m_bConsole
		ARGUMENTS: ---
		OUTPUT:
		*/
		bool GetUsingConsole(void);
		/*
		USAGE: Asks for the value of m_bConsole
		ARGUMENTS:
		OUTPUT: ---
		*/
		void SetUsingConsole(bool a_bUsing);
		/*
		USAGE: This will return the proportions of the window size in the system, from bottom to top of the window the value is 1,
		from left to right the value is the output of this function.
		ARGUMENTS: ---
		OUTPUT:
		*/
		float GetWindowRatio(void);
		/*
		USAGE:
		ARGUMENTS: ---
		OUTPUT:
		*/
		int GetFPS(void);
		/*
		USAGE: Updates the system
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Update(void);
		/*
		USAGE: Starts a time count for the specified clock
		ARGUMENTS: uint a_nClock -> clock to query
		OUTPUT: ---
		*/
		void StartClock(uint a_nClock);
		/*
		USAGE: Gets the time difference between the last time this method was called or clock was created
		for this particular clock, need to generate a clock with GenClock first
		ARGUMENTS: uint a_nClock -> clock to query
		OUTPUT:
		*/
		float GetDeltaTime(uint a_nClock);
		/*
		USAGE: Adds a clock to the list starts it with current time and return said clock's index,
		need to generate a clock with GenClock first
		ARGUMENTS: ---
		OUTPUT: uint -> index of the new clock;
		*/
		uint GenClock(void);
		/*
		USAGE: Gets the time since this clock was created
		ARGUMENTS: uint a_nClock -> clock to query
		OUTPUT: ---
		*/
		float GetTimeSinceStart(uint a_nClock);
		/*
		USAGE: Resets the specified clock to the current time, need to generate a clock with GenClock first
		ARGUMENTS: uint a_nClock -> clock to query
		OUTPUT: ---
		*/
		void ResetClock(uint a_nClock);
		/*
		USAGE: Generates a countdown clock
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void StartTimerOnClock(float a_fTime, uint a_nClock);
		/*
		USAGE: Checks if the timer has finalized running, needs to
		call StartTimerOnClock() first
		ARGUMENTS: uint a_nClock -> queried clock
		OUTPUT: is the clock done the countdown? will return true if
		clock does not exist
		*/
		bool IsTimerDone(uint a_nClock);

	private:
		/*
		USAGE: Constructor
		ARGUMENTS: ---
		OUTPUT:
		*/
		SystemSingleton(void);
		/*
		USAGE: Copy Constructor
		ARGUMENTS:
		OUTPUT:
		*/
		SystemSingleton(SystemSingleton const& other);
		/*
		USAGE: Copy Assignment Operator
		ARGUMENTS:
		OUTPUT:
		*/
		SystemSingleton& operator=(SystemSingleton const& other);
		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~SystemSingleton(void);
		/*
		USAGE: Release Memory
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Release(void);
		/*
		USAGE: Initialize variables
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Init(void);
	};

}
#include "BasicX\System\GLSystem.h"
/*
USAGE:
ARGUMENTS: ---
OUTPUT: ---
*/
#endif //__BASICXSYSTEM_H_