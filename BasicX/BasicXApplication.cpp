#include "BasicX\BasicXApplication.h"

using namespace BasicX;
BasicXApplication* BasicXApplication::m_pSelfPointer = nullptr;

//Callbacks
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (BasicXApplication::m_pSelfPointer != nullptr)
		BasicXApplication::m_pSelfPointer->ProcessMessages(hwnd, msg, wParam, lParam);

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

BasicXApplication::BasicXApplication(BasicXApplication const& input){}
BasicXApplication& BasicXApplication::operator=(BasicXApplication const& input){ return *this; }
