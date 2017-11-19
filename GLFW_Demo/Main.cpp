/*--------------------------------------------------------------------------------------------------
Code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
modified by labigm@rit.edu
--------------------------------------------------------------------------------------------------*/
// Include standard headers
#include "Main.h"
 
GLFWwindow* window;

using namespace Simplex;

int main(void)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(800, 600, "GLFW_Demo", NULL, NULL);
	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	MeshManager* pMeshMngr = MeshManager::GetInstance();
	pMeshMngr->SetRenderTarget(0,0,0,width, height);
	Model* pModel = new Simplex::Model();
	pModel->Load("Lego\\Unikitty.BTO");

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);	// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do

	glEnable(GL_CULL_FACE);
	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
		pMeshMngr->AddSkyboxToRenderList();
		pModel->SetModelMatrix(glm::translate(vector3(0.0f, -5.0f, -15.0f)));
		pModel->PlaySequence();
		pMeshMngr->Render();
		pMeshMngr->ClearRenderList();
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&	glfwWindowShouldClose(window) == 0);
	SafeDelete(pModel);
	Simplex::ReleaseAllSingletons();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	
	return 0;
}