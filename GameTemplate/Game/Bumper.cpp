#include "stdafx.h"
#include "Bumper.h"

Bumper::Bumper()
{

}

Bumper::~Bumper()
{

}

bool Bumper::Start()
{
	m_modelRender.Init("Assets/modelData/Stage_0/Bumper.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void Bumper::Update()
{
	m_modelRender.Update();
}

void Bumper::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}