#include "stdafx.h"
#include "JumpBoard.h"

JumpBoard::JumpBoard()
{

}

JumpBoard::~JumpBoard()
{

}

bool JumpBoard::Start()
{
	m_modelRender.Init("Assets/modelData/Stage_0/JumpBoard.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void JumpBoard::Update()
{
	m_modelRender.Update();
}

void JumpBoard::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}