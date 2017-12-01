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
	uint uInstances = 200;
	// planet 0
	
	m_pEntityMngr->AddEntity("Planets\\00_Sun.obj");
	PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	PlanetMass.push_back(rand() % 11);
	PlanetRadius.push_back(1);
	vector3 v3Position = vector3(5,5,5);
	PlanetPos.push_back(v3Position);
	matrix4 m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->Update();
	//planet spawning
	

	for (int i = 0; i < 2; i++)
	{ 
		
			
			spawnplanet();
	
	}
	//for (int i = 0; i < 10; i++) {
	//	spawnplanet();
	//}
	m_uOctantLevels = 1;
m_pRoot = new MyOctant(m_uOctantLevels, 5);

	m_pEntityMngr->Update();
}

void Application::Update(void)
{
	m_pEntityMngr->ClearDimensionSetAll();
	//re-create the octree
	SafeDelete(m_pRoot);
	m_pRoot = new MyOctant(m_uOctantLevels, 5);
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		PlanetForce[0].x += .1f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		PlanetForce[0].x -= .1f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		PlanetForce[0].y -= .1f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		PlanetForce[0].y += .1f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
	{
		PlanetForce[0].z += .1f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	{
		PlanetForce[0].z -= .1f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		spawnplanet();
	}
	m_pLightMngr->SetPosition(vector3(PlanetPos[0].x, PlanetPos[0].y, PlanetPos[0].z), 1);
	for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
	{
		if (PlanetPos[i].x != PlanetPos[0].x) {
			PlanetForce[i].x -= (.006*PlanetMass[i] * PlanetMass[0] / (PlanetPos[i].x - PlanetPos[0].x)*2);
		}
		if (PlanetPos[i].y != PlanetPos[0].y) {
			PlanetForce[i].y -= (.006*PlanetMass[i] * PlanetMass[0] / (PlanetPos[i].y - PlanetPos[0].y)*2);
		}
		if (PlanetPos[i].z != PlanetPos[0].z) {
			PlanetForce[i].z -= (.006*PlanetMass[i] * PlanetMass[0] / (PlanetPos[i].z - PlanetPos[0].z)*2);
		}
		if (PlanetForce[i].x > .5) {
			PlanetForce[i].x = .5;
		}
		else if (PlanetForce[i].x < -.5) {
			PlanetForce[i].x = -.5;
		}
		if (PlanetForce[i].y > .5) {
			PlanetForce[i].y = .5;
		}
		else if (PlanetForce[i].y < -.5) {
			PlanetForce[i].y = -.5;
		}
		if (PlanetForce[i].z > .5) {
			PlanetForce[i].z = .5;
		}
		else if (PlanetForce[i].z < -.5) {
			PlanetForce[i].z = -.5;
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
	for(int i=0;i< m_pEntityMngr->GetEntityCount();i++)
	{
		//PlanetVel[i] = vector3(0, 0, 0);
		PlanetVel[i] += PlanetForce[i] / PlanetMass[i];
		PlanetForce[i] = vector3(0, 0, 0);
		PlanetPos[i] += PlanetVel[i];
		m_pEntityMngr->GetEntity(i)->SetModelMatrix(m_pEntityMngr->GetEntity(i)->GetModelMatrix()*glm::translate(PlanetVel[i]));
		if (glm::distance(PlanetPos[0], PlanetPos[i])>100) {
			std::cout << "Planet got too far away" << std::endl;
		}
		//Planetmodelmatricies[i] *= glm::translate(PlanetVel[i]);
		//Planets[i]->SetModelMatrix(Planetmodelmatricies[i]);
		//m_pMeshMngr->AddAxisToRenderList(Planetmodelmatricies[i]);
		//Planets[i]->AddToRenderList();
	}
	//Update Entity Manager
	m_pEntityMngr->Update();
	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);

}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	m_pRoot->Display(m_uOctantID, C_YELLOW);
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
	//Model* jupiter = new Model();
	int planetnum = rand() % 9;
	if (planetnum == 0) {
		m_pEntityMngr->AddEntity("Planets\\05_Jupiter.obj");
	}
	if (planetnum == 1) {
		m_pEntityMngr->AddEntity("Planets\\01_Mercury.obj");
	}
	if (planetnum == 2) {
		m_pEntityMngr->AddEntity("Planets\\02_Venus.obj");
	}
	if (planetnum == 3) {
		m_pEntityMngr->AddEntity("Planets\\03_Earth.obj");
	}
	if (planetnum == 4) {
		m_pEntityMngr->AddEntity("Planets\\04_Mars.obj");
	}
	if (planetnum == 5) {
		m_pEntityMngr->AddEntity("Planets\\06_Saturn.obj");
	}
	if (planetnum == 6) {
		m_pEntityMngr->AddEntity("Planets\\07_Uranus.obj");
	}
	if (planetnum == 7) {
		m_pEntityMngr->AddEntity("Planets\\08_Neptune.obj");
	}
	if (planetnum == 8) {
		m_pEntityMngr->AddEntity("Planets\\09_Pluto.obj");
	}
	//Planets.push_back(jupiter);	
	//float size = rand() % 2 + 1.0f;
	//Planetscales.push_back(glm::scale(size,size,size) * 2.0f);
	//float px = rand() % 6 - 2.0f;
	//float py = rand() % 6 - 2.0f;
	//float pz = rand() % 6 - 2.0f;
	//PlanetPos.push_back(vector3(px,py,pz));
	float vx = (rand() % 2 + .1f) / 2;
	float vy = (rand() % 2 + .1f) / 2;
	float vz = (rand() % 2 + .1f) / 2;
	PlanetVel.push_back(vector3(vx,vy,0.0f));
	PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	PlanetMass.push_back(rand() % 11);
	PlanetRadius.push_back(1);
	//Planetmodelmatricies.push_back(glm::translate(PlanetPos[PlanetPos.size() - 1])  * Planetscales[Planetscales.size() - 1]);
	
	
	vector3 v3Position = vector3(glm::sphericalRand(34.0f));
	PlanetPos.push_back(v3Position);
	matrix4 m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->Update();
}
