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
		vector3(0.0f, 3.0f, 30.0f), //Position
		vector3(0.0f, 3.0f, 12.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light(0 is reserved for global light)
	
	// planet 0
	Sun = new Model();
	Sun->Load("Planets\\00_Sun.obj");
	Planets.push_back(Sun);
	Planetscales.push_back(glm::scale(1.0f, 1.0f, 1.0f) * 2.0f);
	PlanetPos.push_back(vector3(-5.0f, 5.0f, 0.0f));
	PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	PlanetMass.push_back(18.0f);
	PlanetRadius.push_back(1);
	Planetmodelmatricies.push_back(glm::translate(PlanetPos[0])  * Planetscales[0]);
	//planet 1
	jupiter = new Model();
	jupiter->Load("Planets\\05_Jupiter.obj");
	Planets.push_back(jupiter);
	Planetscales.push_back(glm::scale(1.0f, 1.0f, 1.0f) * 2.0f);
	PlanetPos.push_back(vector3(-1.0f, 0.0f, 0.0f));
	PlanetVel.push_back(vector3(0.1f, 0.0f, 0.0f));
	PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	PlanetMass.push_back(7.0f);
	PlanetRadius.push_back(3);
	Planetmodelmatricies.push_back(glm::translate(PlanetPos[1])  * Planetscales[1]);
	//planet 2
	//mercury = new Model();
	//mercury->Load("Planets\\01_Mercury.obj");
	//Planets.push_back(mercury);
	//Planetscales.push_back(glm::scale(0.5f, 0.5f, 0.5f) * 2.0f);
	//PlanetPos.push_back(vector3(4.0f, 0.0f, 0.0f));
	//PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	//PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	//PlanetMass.push_back(2.0f);
	//PlanetRadius.push_back(.5);
	//Planetmodelmatricies.push_back(glm::translate(PlanetPos[2])  * Planetscales[2]);
	////planet 3
	//earth = new Model();
	//earth->Load("Planets\\03_Earth.obj");
	//Planets.push_back(earth);
	//Planetscales.push_back(glm::scale(0.3f, 0.3f, 0.3f) *2.0f);
	//PlanetPos.push_back(vector3(8.0f, 0.0f, 0.0f));
	//PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	//PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	//PlanetMass.push_back(3.0f);
	//PlanetRadius.push_back(.3);
	//Planetmodelmatricies.push_back(glm::translate(PlanetPos[3])  * Planetscales[3]);
	////planet 4
	//mars = new Model();
	//mars->Load("Planets\\04_Mars.obj");
	//Planets.push_back(mars);
	//Planetscales.push_back(glm::scale(0.2f, 0.2f, 0.2f)*2.0f);
	//PlanetPos.push_back(vector3(12.0f, 0.0f, 0.0f));
	//PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	//PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	//PlanetMass.push_back(5.0f);
	//PlanetRadius.push_back(.2);
	//Planetmodelmatricies.push_back(glm::translate(PlanetPos[4])  * Planetscales[4]);
	////planet 5
	//saturn = new Model();
	//saturn->Load("Planets\\06_Saturn.obj");
	//Planets.push_back(saturn);
	//Planetscales.push_back(glm::scale(2.5f, 2.5f, 2.5f)*2.0f);
	//PlanetPos.push_back(vector3(16.0f, 0.0f, 0.0f));
	//PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	//PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	//PlanetMass.push_back(8.0f);
	//PlanetRadius.push_back(2.5);
	//Planetmodelmatricies.push_back(glm::translate(PlanetPos[5]) * Planetscales[5]);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		PlanetForce[0].x += .01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		PlanetForce[0].x -= .01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		PlanetForce[0].y -= .01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		PlanetForce[0].y += .01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
	{
		PlanetForce[0].z += .01f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		PlanetForce[0].z -= .01f;
	}
	PlanetVel[0] = vector3(0, 0, 0);
	PlanetVel[0] += PlanetForce[0] / PlanetMass[0];
	PlanetPos[0] += PlanetVel[0];
	Planetmodelmatricies[0] *= glm::translate(PlanetVel[0]);
	Planets[0]->SetModelMatrix(Planetmodelmatricies[0]);
	//m_pMeshMngr->AddAxisToRenderList(Planetmodelmatricies[i]);
	Planets[0]->AddToRenderList();

	for (int i = 1; i < Planets.size(); i++)
	{
		float magdist = std::powf(std::powf(PlanetPos[i].y - PlanetPos[0].y, 2)+ std::powf(PlanetPos[i].x - PlanetPos[0].x, 2)+ std::powf(PlanetPos[i].z - PlanetPos[0].z, 2), .5);
		if (PlanetPos[i].x != PlanetPos[0].x) {
			PlanetForce[i].x -= (.006*PlanetMass[i]*PlanetMass[0] /(PlanetPos[i].x - PlanetPos[0].x));
		}
		if (PlanetPos[i].y != PlanetPos[0].y) {
			PlanetForce[i].y -= (.006*PlanetMass[i] * PlanetMass[0] / (PlanetPos[i].y - PlanetPos[0].y));
		}
		//if (PlanetPos[i].z != PlanetPos[0].z) {
		//	PlanetForce[i].z -= (.0006*(PlanetMass[i] * PlanetMass[0] /( PlanetPos[i].z - PlanetPos[0].z)));
		//}
		if (PlanetForce[i].x > .1) {
			PlanetForce[i].x = .1;
		}
		else if (PlanetForce[i].x < -.1) {
			PlanetForce[i].x = -.1;
		}
		if (PlanetForce[i].y > .1) {
			PlanetForce[i].y = .1;
		}
		else if (PlanetForce[i].y < -.1) {
			PlanetForce[i].y = -.1;
		}
		//if (PlanetForce[i].z > 3) {
		//	PlanetForce[i].z = 3;
		//}
		//else if (PlanetForce[i].z < -3) {
		//	PlanetForce[i].z = -3;
		//}
		
		if (PlanetVel[i].x > .5) {
			PlanetVel[i].x = .5;
		}
		else if (PlanetVel[i].x < -.5) {
			PlanetVel[i].x = -.5;
		}
		if (PlanetVel[i].y > .5) {
			PlanetVel[i].y = .5;
		}
		else if (PlanetVel[i].y < -.5) {
			PlanetVel[i].y = -.5;
		}
		
	}

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	
	for(int i=1;i<Planets.size();i++)
	{
		//PlanetVel[i] = vector3(0, 0, 0);
		PlanetVel[i] += PlanetForce[i] / PlanetMass[i];
		PlanetForce[i] = vector3(0, 0, 0);
		PlanetPos[i] += PlanetVel[i];
		Planetmodelmatricies[i] *= glm::translate(PlanetVel[i]);
		Planets[i]->SetModelMatrix(Planetmodelmatricies[i]);
		//m_pMeshMngr->AddAxisToRenderList(Planetmodelmatricies[i]);
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