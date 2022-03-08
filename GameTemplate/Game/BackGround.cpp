#include "stdafx.h"
#include "BackGround.h"

bool BackGround::Start()
{
	m_stage.Init("Assets/modelData/Stage_1.tkm");
	// 静的物理オブジェクトを作成。
	m_stagePSO.CreateFromModel(m_stage.GetModel(), m_stage.GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Update()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_stage.Draw(rc);
}