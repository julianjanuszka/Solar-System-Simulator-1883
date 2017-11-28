#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUp(
		vector3(0.0f, 3.0f, 13.0f), //Position
		vector3(0.0f, 3.0f, 12.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light(0 is reserved for global light)
	
	// planet 0
	Sun = new Model();
	Sun->Load("Planets\\00_Sun.obj");
	Planets.push_back(Sun);
	Planetscales.push_back(glm::scale(1.0f, 1.0f, 1.0f) * 2.0f);
	PlanetPos.push_back(vector3(-5.0f, 0.0f, 0.0f));
	PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	Planetmodelmatricies.push_back(glm::translate(PlanetPos[0])  * Planetscales[0]);
	//planet 1
	jupiter = new Model();
	jupiter->Load("Planets\\05_Jupiter.obj");
	Planets.push_back(jupiter);
	Planetscales.push_back(glm::scale(3.0f, 3.0f, 3.0f) * 2.0f);
	PlanetPos.push_back(vector3(0.0f, 0.0f, 0.0f));
	PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	Planetmodelmatricies.push_back(glm::translate(PlanetPos[1])  * Planetscales[0]);
	//planet 2
	mercury = new Model();
	mercury->Load("Planets\\01_Mercury.obj");
	Planets.push_back(mercury);
	Planetscales.push_back(glm::scale(0.5f, 0.5f, 0.5f) * 2.0f);
	PlanetPos.push_back(vector3(4.0f, 0.0f, 0.0f));
	PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	Planetmodelmatricies.push_back(glm::translate(PlanetPos[2])  * Planetscales[1]);
	//planet 3
	earth = new Model();
	earth->Load("Planets\\03_Earth.obj");
	Planets.push_back(earth);
	Planetscales.push_back(glm::scale(0.3f, 0.3f, 0.3f) *2.0f);
	PlanetPos.push_back(vector3(8.0f, 0.0f, 0.0f));
	PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	Planetmodelmatricies.push_back(glm::translate(PlanetPos[3])  * Planetscales[2]);
	//planet 4
	mars = new Model();
	mars->Load("Planets\\04_Mars.obj");
	Planets.push_back(mars);
	Planetscales.push_back(glm::scale(0.2f, 0.2f, 0.2f)*2.0f);
	PlanetPos.push_back(vector3(12.0f, 0.0f, 0.0f));
	PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	Planetmodelmatricies.push_back(glm::translate(PlanetPos[4])  * Planetscales[3]);
	//planet 5
	saturn = new Model();
	saturn->Load("Planets\\06_Saturn.obj");
	Planets.push_back(saturn);
	Planetscales.push_back(glm::scale(2.5f, 2.5f, 2.5f)*2.0f);
	PlanetPos.push_back(vector3(16.0f, 0.0f, 0.0f));
	PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	Planetmodelmatricies.push_back(glm::translate(PlanetPos[5]) * Planetscales[4]);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		PlanetVel[0].x += .01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		PlanetVel[0].x -= .01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		PlanetVel[0].y -= .01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		PlanetVel[0].y += .01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
	{
		PlanetVel[0].z += .01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		PlanetVel[0].z -= .01f;
	}

	Planetmodelmatricies[0] *= glm::translate(PlanetVel[0]);

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	
	for(int i=0;i<Planets.size();i++)
	{
		Planets[i]->SetModelMatrix(Planetmodelmatricies[i]);
		m_pMeshMngr->AddAxisToRenderList(Planetmodelmatricies[i]);
		Planets[i]->AddToRenderList();
	}

}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList("space3.png");
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}

void Application::Release(void)
{

	//release GUI
	ShutdownGUI();
}