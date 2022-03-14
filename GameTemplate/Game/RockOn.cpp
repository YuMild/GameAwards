#include "stdafx.h"
#include "RockOn.h"

#include "Player.h"
#include "Stage1.h"

RockOn::RockOn()
{

}

RockOn::~RockOn()
{

}

bool RockOn::Start()
{
	m_player = FindGO<Player>("player");
	m_stage1 = FindGO<Stage1>("stage1");
	return true;
}

void RockOn::Update()
{
	Judge();
}

void RockOn::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
}

void RockOn::Judge()
{
	//�v���C���[����o���p�[�Ɍ������x�N�g�������߂�
	m_difference = m_stage1->GetBumperPosition() - m_player->GetPosition();

	//�v���C���[�ɋ߂�������
	if (m_difference.Length() <= 1000.0f)
	{
		//�v���C���[����o���p�[�Ɍ������x�N�g���𐳋K��
		//m_difference.Normalize();
		//�J�����̐��ʂ̃x�N�g���ƃv���C���[����o���p�[�Ɍ������x�N�g���̓��ς����߂�
		//float cos = g_camera3D->GetForward().Dot(m_difference);
		//���ς���p�x�����߂�
		//float angle = acosf(cos);
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"%d", int(1));
		m_fontRender.SetText(wcsbuf);
		m_fontRender.SetPosition({ 100.0f,100.0f,0.0f });
		//�p�x��120����菬���������烍�b�N�I������
		/*if (angle <= (Math::PI / 180.0f) * 60.0f);
		{
			wchar_t wcsbuf[256];
			swprintf_s(wcsbuf, 256, L"%d", int(1));
			m_fontRender.SetText(wcsbuf);
			m_fontRender.SetPosition({ 100.0f,100.0f,0.0f });
		}*/
	}
	else
	{
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"%d", int(2));
		m_fontRender.SetText(wcsbuf);
		m_fontRender.SetPosition({ 100.0f,100.0f,0.0f });
	}
}