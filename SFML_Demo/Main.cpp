#include "Main.h"

using namespace Simplex;

int main()
{
	// create the window
	sf::Window window(sf::VideoMode(800, 600), "SFML_Demo", sf::Style::Default, sf::ContextSettings(32));
	window.setVerticalSyncEnabled(true);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);	// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do

	glEnable(GL_CULL_FACE);

	// load resources, initialize the OpenGL states, ...
	sf::Vector2u size = window.getSize();
	sf::Vector2i pos = window.getPosition();

	SystemSingleton* pSystem = SystemSingleton::GetInstance();
	pSystem->SetWindowX(pos.x);
	pSystem->SetWindowY(pos.y);
	pSystem->SetWindowWidth(size.x);
	pSystem->SetWindowHeight(size.y);

	MeshManager* pMeshMngr = MeshManager::GetInstance();
	pMeshMngr->SetRenderTarget(0, 0, 0, size.x, size.y);
	Model* pModel = new Simplex::Model();
	pModel->Load("Lego\\Unikitty.BTO");

	// run the main loop
	bool running = true;
	while (running)
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// end the program
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// adjust the viewport when the window is resized
				glViewport(0, 0, event.size.width, event.size.height);
				pMeshMngr->SetRenderTarget(0, 0, 0, event.size.width, event.size.height);
				
				pSystem->SetWindowWidth(event.size.width);
				pSystem->SetWindowHeight(event.size.height);
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				if (pos != window.getPosition())
				{
					pos = window.getPosition();
					pSystem->SetWindowX(pos.x);
					pSystem->SetWindowY(pos.y);
				}
			}
		}

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// draw...
		pMeshMngr->AddSkyboxToRenderList();
		pModel->SetModelMatrix(glm::translate(vector3(0.0f, -5.0f, -15.0f)));
		pModel->PlaySequence();
		pMeshMngr->Render();
		pMeshMngr->ClearRenderList();
		
		// end the current frame (internally swaps the front and back buffers)
		window.display();
	}

	// release resources...
	SafeDelete(pModel);
	Simplex::ReleaseAllSingletons();

	return 0;
}