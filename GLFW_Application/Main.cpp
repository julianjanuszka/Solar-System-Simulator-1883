/*--------------------------------------------------------------------------------------------------
Code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
modified by labigm@rit.edu
--------------------------------------------------------------------------------------------------*/
// Include standard headers
#include "Main.h"
 
int main(void)
{
	GLFWApp* pApp = new GLFWApp();
	pApp->Run();
	SafeDelete(pApp);
	return 0;
}