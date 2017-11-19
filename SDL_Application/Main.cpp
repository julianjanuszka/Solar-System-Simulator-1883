// Include standard headers
#include "Main.h"

int main(void)
{
	SDLApp* pApp = new SDLApp();
	pApp->Run();
	SafeDelete(pApp);
	return 0;
}