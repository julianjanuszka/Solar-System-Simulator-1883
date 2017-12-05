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
	PlanetMass.push_back(15);
	PlanetRadius.push_back(5);
	vector3 v3Position = vector3(0,0,0);
	PlanetPos.push_back(v3Position);
	matrix4 m4Position = glm::scale(vector3(5,5,5))*glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->Update();
	//planet spawning
	
	//m_pEntityMngr->AddEntity("Planets\\00_Sun.obj");
	//m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityCount() - 1)->setIsPlanet(false);
	//PlanetVel.push_back(vector3(0.0f, 0.0f, 0.0f));
	//PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	//PlanetMass.push_back(15);
	//PlanetRadius.push_back(5);
	//vector3 v3Position2 = vector3(5, 5, 5);
	//PlanetPos.push_back(v3Position2);
	//matrix4 m4Position2 = glm::scale(vector3(5, 5, 5))*glm::translate(v3Position2);
	//m_pEntityMngr->SetModelMatrix(m4Position2);
	//m_pEntityMngr->Update();

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
		{
			m_pEntityMngr->GetEntity(i)->GetRigidBody()->SetVisibleARBB(false);
			m_pEntityMngr->GetEntity(i)->GetRigidBody()->SetVisibleBS(false);
			m_pEntityMngr->GetEntity(i)->GetRigidBody()->SetVisibleOBB(false);
			boxesshowing = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
		{
			m_pEntityMngr->GetEntity(i)->GetRigidBody()->SetVisibleARBB(true);
			m_pEntityMngr->GetEntity(i)->GetRigidBody()->SetVisibleBS(true);
			m_pEntityMngr->GetEntity(i)->GetRigidBody()->SetVisibleOBB(true);
			boxesshowing = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		for (int i = 1; i < m_pEntityMngr->GetEntityCount(); i++)
		{
			m_pEntityMngr->RemoveEntity(i);
			PlanetVel.erase(PlanetVel.begin() + i);
			PlanetForce.erase(PlanetForce.begin() + i);
			PlanetMass.erase(PlanetMass.begin() + i);
			PlanetPos.erase(PlanetPos.begin() + i);
			PlanetRadius.erase(PlanetRadius.begin() + i);
			m_pEntityMngr->ClearDimensionSetAll();
			SafeDelete(m_pRoot);
			m_pRoot = new MyOctant(m_uOctantLevels, 5);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		for (int i = 0; i < 100; i++)
		{
			spawnplanet();
		}
	}
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		spawnMeteor();
	}
	m_pLightMngr->SetPosition(vector3(PlanetPos[0].x, PlanetPos[0].y, PlanetPos[0].z), 1);
	for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++)
	{
		if (m_pEntityMngr->GetEntity(i)->getIsPlanet()) {
			if (PlanetPos[i].x != PlanetPos[0].x) {
				PlanetForce[i].x -= (.006*PlanetMass[i] * PlanetMass[0] / (PlanetPos[i].x - PlanetPos[0].x) * 2);
			}
			if (PlanetPos[i].y != PlanetPos[0].y) {
				PlanetForce[i].y -= (.006*PlanetMass[i] * PlanetMass[0] / (PlanetPos[i].y - PlanetPos[0].y) * 2);
			}
			if (PlanetPos[i].z != PlanetPos[0].z) {
				PlanetForce[i].z -= (.006*PlanetMass[i] * PlanetMass[0] / (PlanetPos[i].z - PlanetPos[0].z) * 2);
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
		if (glm::distance (PlanetPos[0], PlanetPos[i]) > 150)
		{
			m_pEntityMngr->RemoveEntity(i);
			PlanetVel.erase(PlanetVel.begin() + i);
			PlanetForce.erase(PlanetForce.begin() + i);
			PlanetMass.erase(PlanetMass.begin() + i);
			PlanetPos.erase(PlanetPos.begin() + i);
			PlanetRadius.erase(PlanetRadius.begin() + i);
			std::cout << "Something got too far away!" << std::endl;
		}

		if (m_pEntityMngr->GetEntity(i)->GetRigidBody()->GetcollidingSetSize() > 0) {
			/*
			Put Deletion code here
			*/
			if (i == 0)
			{
				std::cout << "Something Hit the Sun!" << std::endl;
			}
			else {
				m_pEntityMngr->RemoveEntity(i);
				PlanetVel.erase(PlanetVel.begin() + i);
				PlanetForce.erase(PlanetForce.begin() + i);
				PlanetMass.erase(PlanetMass.begin() + i);
				PlanetPos.erase(PlanetPos.begin() + i);
				PlanetRadius.erase(PlanetRadius.begin() + i);
				m_pEntityMngr->ClearDimensionSetAll();
				SafeDelete(m_pRoot);
				m_pRoot = new MyOctant(m_uOctantLevels, 5);
			}
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
	if (boxesshowing) {
		m_pRoot->Display(m_uOctantID, C_YELLOW);
	}
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList("space.png");
	
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
	float randScale = (rand() % 6 + 1.5f);
	matrix4 scaleMatrix = glm::scale(vector3(randScale, randScale, randScale));
	matrix4 m4Position = glm::translate(v3Position) * scaleMatrix;
	m_pEntityMngr->SetModelMatrix(m4Position);
	m_pEntityMngr->Update();

	m_pEntityMngr->ClearDimensionSetAll();

	
}

void Simplex::Application::spawnMeteor(void)
{
	m_pEntityMngr->AddEntity("Planets\\03A_Moon.obj");
	m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityCount() - 1)->setIsPlanet(false);
	PlanetVel.push_back(m_pCameraMngr->GetForward());
	PlanetForce.push_back(vector3(0.0f, 0.0f, 0.0f));
	PlanetMass.push_back(15);
	PlanetRadius.push_back(5);
	vector3 v3Position2 = m_pCameraMngr->GetPosition();
	PlanetPos.push_back(v3Position2);
	matrix4 m4Position2 = glm::translate(v3Position2);
	m_pEntityMngr->SetModelMatrix(m4Position2);
	m_pEntityMngr->Update();
}
