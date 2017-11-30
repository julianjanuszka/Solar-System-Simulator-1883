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
	//planet spawning
	for (int i = 0; i < 10; i++) {
		spawnplanet();
	}
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		spawnplanet();
	}

	PlanetVel[0] = vector3(0, 0, 0);
	PlanetVel[0] += PlanetForce[0] / PlanetMass[0];
	PlanetPos[0] += PlanetVel[0];
	Planetmodelmatricies[0] *= glm::translate(PlanetVel[0]);
	Planets[0]->SetModelMatrix(Planetmodelmatricies[0]);
	//m_pMeshMngr->AddAxisToRenderList(Planetmodelmatricies[i]);
	Planets[0]->AddToRenderList();
	m_pLightMngr->SetPosition(vector3(PlanetPos[0].x, PlanetPos[0].y, PlanetPos[0].z), 1);
	for (int i = 0; i < Planets.size(); i++)
	{
		if (PlanetPos[i].x != PlanetPos[0].x) {
			PlanetForce[i].x -= (.006*PlanetMass[i] * PlanetMass[0] / (PlanetPos[i].x - PlanetPos[0].x));
		}
		if (PlanetPos[i].y != PlanetPos[0].y) {
			PlanetForce[i].y -= (.006*PlanetMass[i] * PlanetMass[0] / (PlanetPos[i].y - PlanetPos[0].y));
		}
		//if (PlanetPos[i].z != PlanetPos[0].z) {
		//	PlanetForce[i].z -= (.0006*PlanetMass[i] * PlanetMass[0] / (PlanetPos[i].z - PlanetPos[0].z));
		//}

		for (int j = 0; j < Planets.size(); j++) {
			
			float magdist = std::powf(std::powf(PlanetPos[i].y - PlanetPos[j].y, 2)+ std::powf(PlanetPos[i].x - PlanetPos[j].x, 2)+ std::powf(PlanetPos[i].z - PlanetPos[j].z, 2), .5);

			if(magdist>1)
			{
			}
			else {
				//if (PlanetPos[i].x != PlanetPos[0].x) {
				//	PlanetForce[i].x += (.00006*PlanetMass[i] * PlanetMass[j] / (PlanetPos[i].x - PlanetPos[j].x))*.0005f;
				//}
				//if (PlanetPos[i].y != PlanetPos[0].y) {
				//	PlanetForce[i].y += (.00006*PlanetMass[i] * PlanetMass[j] / (PlanetPos[i].y - PlanetPos[j].y))*.0005f;
				//}
				//if (PlanetPos[i].z != PlanetPos[0].z) {
				//	PlanetForce[i].z += (.000006*(PlanetMass[i] * PlanetMass[j] / (PlanetPos[i].z - PlanetPos[j].z)))*.0005f;
				//}
			}
			
		}
		if (PlanetForce[i].x > 1) {
			PlanetForce[i].x = 1;
		}
		else if (PlanetForce[i].x < -1) {
			PlanetForce[i].x = -1;
		}
		if (PlanetForce[i].y > 1) {
			PlanetForce[i].y = 1;
		}
		else if (PlanetForce[i].y < -1) {
			PlanetForce[i].y = -1;
		}
		if (PlanetForce[i].z > 1) {
			PlanetForce[i].z = 1;
		}
		else if (PlanetForce[i].z < -1) {
			PlanetForce[i].z = -1;
		}
		if (PlanetVel[i].x > 1.5) {
			PlanetVel[i].x = 1.5;
		}
		else if (PlanetVel[i].x < -1.5) {
			PlanetVel[i].x = -1.5;
		}
		if (PlanetVel[i].y > 1.5) {
			PlanetVel[i].y = 1.5;
		}
		else if (PlanetVel[i].y < -1.5) {
			PlanetVel[i].y = -1.5;
		}
		if (PlanetVel[i].z > 1.5) {
			PlanetVel[i].z = 1.5;
		}
		else if (PlanetVel[i].z < -1.5) {
			PlanetVel[i].z = -1.5;
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
void Simplex::Application::spawnplanet(void)
{
	Model* jupiter = new Model();
	int planetnum = rand() % 9;
	if (planetnum == 0) {
		jupiter->Load("Planets\\05_Jupiter.obj");
	}
	if (planetnum == 1) {
		jupiter->Load("Planets\\01_Mercury.obj");
	}
	if (planetnum == 2) {
		jupiter->Load("Planets\\02_Venus.obj");
	}
	if (planetnum == 3) {
		jupiter->Load("Planets\\03_Earth.obj");
	}
	if (planetnum == 4) {
		jupiter->Load("Planets\\04_Mars.obj");
	}
	if (planetnum == 5) {
		jupiter->Load("Planets\\06_Saturn.obj");
	}
	if (planetnum == 6) {
		jupiter->Load("Planets\\07_Uranus.obj");
	}
	if (planetnum == 7) {
		jupiter->Load("Planets\\08_Neptune.obj");
	}
	if (planetnum == 8) {
		jupiter->Load("Planets\\09_Pluto.obj");
	}
	Planets.push_back(jupiter);	
	float size = rand() % 2 + 1.0f;
	Planetscales.push_back(glm::scale(size,size,size) * 2.0f);
	float px = rand() % 6 - 2.0f;
	float py = rand() % 6 - 2.0f;
	float pz = rand() % 6 - 2.0f;
	PlanetPos.push_back(vector3(px,py,pz));
	float vx = (rand() % 2 + .1f) / 2;
	float vy = (rand() % 2 + .1f) / 2;
	float vz = (rand() % 2 + .1f) / 2;
	PlanetVel.push_back(vector3(vx,vy,0.0f));
	PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	PlanetMass.push_back(rand() % 11);
	PlanetRadius.push_back(Planetscales[PlanetPos.size() - 1][0][0]);
	Planetmodelmatricies.push_back(glm::translate(PlanetPos[PlanetPos.size() - 1])  * Planetscales[Planetscales.size() - 1]);

}
