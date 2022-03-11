#include "stdafx.h"
#include "Stage1.h"

bool Stage1::Start()
{
	m_stage_Ground.Init("Assets/modelData/Stage1/Stage_1_Ground.tkm");
	m_stage_Wall.Init("Assets/modelData/Stage1/Stage_1_wall.tkm");
	m_stage_Bumpers.Init("Assets/modelData/Stage1/Stage_1_bumpers.tkm");
	//静的物理オブジェクトを作成。
	m_stage_Ground_PSO.CreateFromModel(m_stage_Ground.GetModel(), m_stage_Ground.GetModel().GetWorldMatrix(),0.0f);
	m_stage_Wall_PSO.CreateFromModel(m_stage_Wall.GetModel(), m_stage_Wall.GetModel().GetWorldMatrix(),0.8f);
	m_stage_Bumpers_PSO.CreateFromModel(m_stage_Bumpers.GetModel(), m_stage_Bumpers.GetModel().GetWorldMatrix(), 1.2f);

	m_stage_Ground.SetScale(1.0f, 1.0f, 1.0f);
	m_stage_Wall.SetScale(1.0f, 1.0f, 1.0f);
	m_stage_Bumpers.SetScale(1.0f, 1.0f, 1.0f);

	m_stage_Ground.Update();
	m_stage_Wall.Update();
	m_stage_Bumpers.Update();

	//m_boxCollider.Create({ 100.0f,100.0f,100.0f });

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

void Stage1::Update()
{

}

void Stage1::Render(RenderContext& rc)
{
	m_stage_Ground.Draw(rc);
	m_stage_Wall.Draw(rc);
	m_stage_Bumpers.Draw(rc);
}