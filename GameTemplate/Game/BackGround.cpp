#include "stdafx.h"
#include "BackGround.h"

bool BackGround::Start()
{
	m_stage.Init("Assets/modelData/Stage_1.tkm");
	// �ÓI�����I�u�W�F�N�g���쐬�B
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