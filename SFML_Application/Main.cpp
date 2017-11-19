// Include standard headers
#include "Main.h"

int main(void)
{
	SFMLApp* pApp = new SFMLApp();
	pApp->Run();
	SafeDelete(pApp);
	return 0;
}