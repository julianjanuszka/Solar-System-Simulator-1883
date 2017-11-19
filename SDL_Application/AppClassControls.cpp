#include "AppClass.h"
//Keyboard
void SDLApp::ProcessKeyboard(SDL_Event a_event)
{
	float fSpeed = 1.0f;
#pragma region Camera Positioning
	if (a_event.key.keysym.sym == SDLK_w)
		m_pCameraMngr->MoveForward(fSpeed);

	if (a_event.key.keysym.sym == SDLK_s)
		m_pCameraMngr->MoveForward(-fSpeed);

	if (a_event.key.keysym.sym == SDLK_a)
		m_pCameraMngr->MoveSideways(-fSpeed);

	if (a_event.key.keysym.sym == SDLK_d)
		m_pCameraMngr->MoveSideways(fSpeed);

	if (a_event.key.keysym.sym == SDLK_q)
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (a_event.key.keysym.sym == SDLK_e)
		m_pCameraMngr->MoveVertical(fSpeed);
#pragma endregion
}
//Mouse
void SDLApp::ProcessMousePress(SDL_Event a_event)
{
	if (a_event.button.button == SDL_BUTTON_MIDDLE)
		m_bArcBall = true;

	if (a_event.button.button == SDL_BUTTON_RIGHT)
		m_bFPC = true;
}
void SDLApp::ProcessMouseRelease(SDL_Event a_event)
{
	if (a_event.button.button == SDL_BUTTON_MIDDLE)
		m_bArcBall = false;

	if (a_event.button.button == SDL_BUTTON_RIGHT)
		m_bFPC = false;
}
//Joystick
void SDLApp::ProcessJoystick(SDL_Event a_event)
{
}