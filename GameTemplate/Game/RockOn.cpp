#include "stdafx.h"
#include "RockOn.h"

#include "Bumper.h"
#include "Player.h"

RockOn::RockOn()
{

}

RockOn::~RockOn()
{

}

bool RockOn::Start()
{
	m_bumper = FindGO<Bumper>("bumper");
	m_player = FindGO<Player>("player");
	
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
	m_difference = m_bumper->GetPosition() - m_player->GetPosition();

	//���������߂�����߉߂���ƃ��b�N�I�����Ȃ�
	if (m_difference.Length() >= 3000.0f || m_difference.Length() < 100.0f)
	{
		m_isReady = false;
	}
	else
	{
		m_isReady = true;
	}

	//���K��
	m_difference.y = 0.0f;
	m_difference.Normalize();

	//���b�N�I������p���쐬
	float angle = acosf(g_camera3D->GetForward().Dot(m_difference));

	//�������K�؂Ŋ����b�N�I������p�ɃI�u�W�F�N�g�������Ă�����
	if (angle < (Math::PI / 180.0f) * 30.0f && m_isReady == true)
	{
		//���b�N�I������
		m_isRockOn == true;
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"RockOn%d", int());
		m_fontRender.SetText(wcsbuf);
		m_fontRender.SetPosition({ 100.0f,100.0f,0.0f });
		//g_camera3D->SetTarget(m_bumper->GetPosition());
	}
	else
	{
		//���b�N�I�����Ȃ�
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"%d", int());
		m_fontRender.SetText(wcsbuf);
		m_fontRender.SetPosition({ 100.0f,100.0f,0.0f });
	}
}