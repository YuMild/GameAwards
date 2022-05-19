#include "stdafx.h"
#include "Pipe.h"

Pipe::Pipe()
{

}

Pipe::~Pipe()
{

}

bool Pipe::Start()
{
	m_modelRender.Init("Assets/modelData/Stage_0/Pipe.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_boxCollider.BoxInit({ 200.0f,4000.0f,200.0f }, m_position, 0.5);

	return true;
}

void Pipe::Update()
{
	m_modelRender.Update();
}

void Pipe::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}