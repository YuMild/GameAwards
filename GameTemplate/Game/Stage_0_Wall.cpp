#include "stdafx.h"
#include "Stage_0_Wall.h"

Stage_0_Wall::Stage_0_Wall()
{

}

Stage_0_Wall::~Stage_0_Wall()
{

}

bool Stage_0_Wall::Start()
{
	m_modelRender.Init("Assets/modelData/Stage_0/Stage_0_Wall.tkm");
	m_modelRender.Update();

	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	return true;
}

void Stage_0_Wall::Update()
{
	m_modelRender.Update();
}

void Stage_0_Wall::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}