#include "stdafx.h"
#include "Truck.h"

Truck::Truck()
{

}

Truck::~Truck()
{

}

bool Truck::Start()
{
	m_modelRender.Init("Assets/modelData/Stage_0/Truck.tkm",false);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_boxCollider.BoxInit({ 100.0f,100.0f,100.0f }, m_position, 0.5);

	return true;
}

void Truck::Update()
{
	m_modelRender.Update();
}

void Truck::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}