#include "stdafx.h"
#include "GameCamera.h"

#include "Game.h"
#include "Player.h"
#include "RockOn.h"

namespace
{
	const float FIRST_CAMERA_POSITION = 40.0f;
	const float	DAMPING_RATE_ON_DASH = 1.75f;			// ���b�N�I�����_�b�V���J�n���̃_���s���O���[�g�B
	const float	DAMPING_RATE_ON_NORMAL = 0.5f;			// �ʏ펞�̃_���s���O���[�g�B
}

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	m_dampingRate = DAMPING_RATE_ON_NORMAL;
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");

	m_toCameraPos.Set(0.0f, 600.0f, 500.0f);

	g_camera3D->SetFar(1000000.0f);

	m_springCamera.Refresh();

	m_springCamera.Init
	(
		*g_camera3D,
		100000.0f
	);

	m_springCamera.SetDampingRate(0.5f);

	Quaternion firstCameraPosition;
	firstCameraPosition.SetRotationDegX(FIRST_CAMERA_POSITION);
	firstCameraPosition.Apply(m_toCameraPos);

	return true;
}

void GameCamera::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
}

void GameCamera::NotifyStartDash()
{
	m_dampingRate = DAMPING_RATE_ON_DASH;
}

void GameCamera::Update()
{
	if (m_player->GetIsPressState() == true)
	{
		NotifyStartDash();
		m_player->SetIsPressState(false);
	}

	wchar_t x[256];
	swprintf_s(x, 256, L"rate%f", m_dampingRate);
	m_fontRender.SetText(x);
	m_fontRender.SetPosition({ -500.0f, 250.0f, 0.0f });

	m_coolTime += g_gameTime->GetFrameDeltaTime();

	m_target = m_player->GetPosition();
	m_target.y += 0.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	//	�p�b�h�̓��͂��g���ăJ��������
	if (m_game->GetGameState() != 1)
	{
		m_rotationX = g_pad[0]->GetRStickXF();
		m_rotationY = g_pad[0]->GetRStickYF();
	}

	//	Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 5.0f * m_rotationX);
	qRot.Apply(m_toCameraPos);

	//	X������̉�]
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 5.0f * m_rotationY);
	qRot.Apply(m_toCameraPos);

	//	�J�����̉�]�̏�����`�F�b�N����
	//	�����_���王�_�܂ł̃x�N�g���𐳋K������
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.1f) {
		m_toCameraPos = toCameraPosOld;									//	�J��������Ɍ����߂���̂�h��
	}
	else if (toPosDir.y > 0.55f) {
		m_toCameraPos = toCameraPosOld;									//	�J���������Ɍ����߂���̂�h��
	}

	//	���_���v�Z����
	Vector3 pos = m_target + m_toCameraPos;

	// �_���s���O���[�g���v�Z����B
	m_dampingRate += (DAMPING_RATE_ON_NORMAL - m_dampingRate) * 0.03f; // �_���s���O���[�g�����X�ɗ��Ƃ��Ă����B
	// DAMPING_RATE_ON_NORMAL��菬�����Ȃ�Ȃ��悤��max�֐��ŕ␳����B
	m_dampingRate = std::max<float>(m_dampingRate, DAMPING_RATE_ON_NORMAL);

	m_springCamera.SetDampingRate(m_dampingRate);
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(m_target);
	m_springCamera.Update();
}