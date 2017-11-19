/*--------------------------------------------------------------------------------------------------
Code from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
modified by labigm@rit.edu
--------------------------------------------------------------------------------------------------*/
// Include standard headers
#include "Main.h"

using namespace Simplex;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_Window* window = SDL_CreateWindow("SDL_DEMO", 50, 50, 600, 600, SDL_WINDOW_OPENGL);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	MeshManager* pMeshMngr = MeshManager::GetInstance();
	pMeshMngr->SetRenderTarget(0, 0, 0, width, height);
	Model* pModel = new Simplex::Model();
	pModel->Load("Lego\\Unikitty.BTO");

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);	// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do

	glEnable(GL_CULL_FACE);

	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
		pMeshMngr->AddSkyboxToRenderList();
		pModel->SetModelMatrix(glm::translate(vector3(0.0f, -5.0f, -15.0f)));
		pModel->PlaySequence();
		pMeshMngr->Render();
		pMeshMngr->ClearRenderList();

		SDL_GL_SwapWindow(window);
	}

	SafeDelete(pModel);
	Simplex::ReleaseAllSingletons();

	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}