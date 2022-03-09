#include "stdafx.h"
#include "BackGround.h"

bool BackGround::Start()
{
	m_stage_Ground.Init("Assets/modelData/Stage_1_Ground.tkm");
	m_stage_Wall.Init("Assets/modelData/Stage_1_wall.tkm");
	// 静的物理オブジェクトを作成。
	m_stage_Ground_PSO.CreateFromModel(m_stage_Ground.GetModel(), m_stage_Ground.GetModel().GetWorldMatrix(),0.0f);
	m_stage_Wall_PSO.CreateFromModel(m_stage_Wall.GetModel(), m_stage_Wall.GetModel().GetWorldMatrix(),0.8f);

	return true;
}

void BackGround::Update()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_stage_Ground.Draw(rc);
	m_stage_Wall.Draw(rc);
}