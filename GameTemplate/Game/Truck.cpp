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

	m_boxCollider.BoxInit({ 500.0f,500.0f,2000.0f }, m_position, 0.5);
	Vector3 vec = { 0.0f,150.0f,800.0f };
	m_rotation.Apply(vec);

	Vector3 vec1 = m_position - vec;

	m_boxCollider.GetRigidBody()->SetPositionAndRotation(vec1, m_rotation);
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