#include "stdafx.h"
#include "BackGround.h"

bool BackGround::Start()
{
	m_wall.Init("Assets/modelData/StageWall.tkm");
	m_wall.SetScale(1.0f,1.0f,1.0f);
	m_wall.Update();

	m_ground.Init("Assets/modelData/StageGround.tkm");
	m_ground.SetScale(1.0f, 1.0f, 1.0f);
	m_ground.Update();

	// 静的物理オブジェクトを作成。
	m_wallPSO.CreateFromModel(m_wall.GetModel() , m_wall.GetModel().GetWorldMatrix(),0.5f);

	m_groundPSO.CreateFromModel(m_ground.GetModel(), m_ground.GetModel().GetWorldMatrix(), 0.0f);

	return true;
}
void BackGround::Update()
{

}
void BackGround::Render(RenderContext& rc)
{
	m_wall.Draw(rc);
	m_ground.Draw(rc);
}