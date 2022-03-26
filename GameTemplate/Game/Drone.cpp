#include "stdafx.h"
#include "Drone.h"

Drone::Drone()
{

}

Drone::~Drone()
{

}

bool Drone::Start()
{
	m_modelRender.Init("Assets/modelData/Stage_0/Drone.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_boxCollider.BoxInit({ 100.0f,100.0f,100.0f }, m_position, 0.5);

	return true;
}

void Drone::Update()
{
	m_modelRender.Update();
}

void Drone::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}