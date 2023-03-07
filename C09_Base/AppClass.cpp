#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);
	m_sModel = "WallEye.obj";
	m_pModelMngr->LoadModel(m_sModel);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	m_pModelMngr->AddModelToRenderList(m_sModel, ToMatrix4(m_qArcBall));

	static float value = 0.0f;

	m_pCameraMngr->SetPosition(vector3(0.0f, 0.0f, 10.0f));	// change position of camera in world (where I am)
	//m_pCameraMngr->SetTarget(vector3(0.0f, value, 0.0f));		// change rotation of camera (what am i looking at)
	//m_pCameraMngr->SetUpward(vector3(0.0f, 1.0f, 0.0f));		// change vector that determines what is "up" to the camera (what is upward in my world)
	//m_pCameraMngr->SetFOV(90.0f);								// change field of view (how much can I see)
	//m_pCameraMngr->SetNearFarPlanes(0.01f, 15.0f);			// change how much the camera can render in front of it

	value += m_pSystem->GetDeltaTime(0);

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

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