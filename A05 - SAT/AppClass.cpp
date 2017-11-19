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

	jupiter = new Model();
	jupiter->Load("Planets\\05_Jupiter.obj");
	
	mercury = new Model();
	mercury->Load("Planets\\01_Mercury.obj");

	earth = new Model();
	earth->Load("Planets\\03_Earth.obj");

	mars = new Model();
	mars->Load("Planets\\04_Mars.obj");

	saturn = new Model();
	saturn->Load("Planets\\06_Saturn.obj");
	
	//creeper
	m_pCreeper = new Model();
	m_pCreeper->Load("Minecraft\\Creeper.obj");
	m_pCreeperRB = new MyRigidBody(m_pCreeper->GetVertexList());

	//steve
	m_pSteve = new Model();
	m_pSteve->Load("Minecraft\\Steve.obj");
	m_pSteveRB = new MyRigidBody(m_pSteve->GetVertexList());
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
	matrix4 jupiterScale = glm::scale(3.0f, 3.0f, 3.0f) * 2.0f;
	matrix4 earthScale = glm::scale(0.5f,0.5f,0.5f) * 2.0f;
	matrix4 marsScale = glm::scale(0.3f,0.3f,0.3f) *2.0f;
	matrix4 mercuryScale = glm::scale(0.2f,0.2f,0.2f)*2.0f;
	matrix4 saturnScale = glm::scale(2.5f,2.5f,2.5f)*2.0f;



	matrix4 mJupiter = glm::translate(vector3(0.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z) * jupiterScale;
	jupiter->SetModelMatrix(mJupiter);
	m_pMeshMngr->AddAxisToRenderList(mJupiter);

	matrix4 mMercury = glm::translate(vector3(4.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z) * mercuryScale;
	mercury->SetModelMatrix(mMercury);
	m_pMeshMngr->AddAxisToRenderList(mMercury);

	matrix4 mEarth = glm::translate(vector3(8.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z) * earthScale;
	earth->SetModelMatrix(mEarth);
	m_pMeshMngr->AddAxisToRenderList(mEarth);


	matrix4 mSaturn = glm::translate(vector3(12.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z) * saturnScale;
	saturn->SetModelMatrix(mSaturn);
	m_pMeshMngr->AddAxisToRenderList(mSaturn);

	matrix4 mMars = glm::translate(vector3(16.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z) * marsScale;
	mars->SetModelMatrix(mMars);
	m_pMeshMngr->AddAxisToRenderList(mMars);
	//Set model matrix to the creeper
	matrix4 mCreeper = glm::translate(m_v3Creeper) * ToMatrix4(m_qCreeper) * ToMatrix4(m_qArcBall);
	m_pCreeper->SetModelMatrix(mCreeper);
	m_pCreeperRB->SetModelMatrix(mCreeper);
	//m_pMeshMngr->AddAxisToRenderList(mCreeper);

	//Set model matrix to Steve
	matrix4 mSteve = glm::translate(vector3(2.25f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z);
	m_pSteve->SetModelMatrix(mSteve);
	m_pSteveRB->SetModelMatrix(mSteve);
	//m_pMeshMngr->AddAxisToRenderList(mSteve);

	bool bColliding = m_pCreeperRB->IsColliding(m_pSteveRB);

	jupiter->AddToRenderList();
	mercury->AddToRenderList();
	earth->AddToRenderList();
	mars->AddToRenderList();
	saturn->AddToRenderList();




	//m_pCreeper->AddToRenderList();
	//m_pCreeperRB->AddToRenderList();

	//m_pSteve->AddToRenderList();
	//m_pSteveRB->AddToRenderList();

	m_pMeshMngr->Print("Colliding: ");
	if (bColliding)
		m_pMeshMngr->PrintLine("YES!", C_RED);
	else
		m_pMeshMngr->PrintLine("no", C_YELLOW);
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

	//release the model
	SafeDelete(m_pCreeper);

	//release the rigid body for the model
	SafeDelete(m_pCreeperRB);

	//release the model
	SafeDelete(m_pSteve);

	//release the rigid body for the model
	SafeDelete(m_pSteveRB);

	//release GUI
	ShutdownGUI();
}