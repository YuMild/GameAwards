#include "stdafx.h"
#include "GameCamera.h"

#include "Player.h"
#include "RockOn.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");
	m_toCameraPos.Set(0.0f, 100.0f, 100.0f);

	g_camera3D->SetFar(1000000.0f);

	m_rockOn = FindGO<RockOn>("rockOn");

	return true;
}

void GameCamera::Update()
{
	m_target = m_player->GetPosition();
	m_target.y += 0.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	//	�p�b�h�̓��͂��g���ăJ��������
	m_rotationX = g_pad[0]->GetRStickXF();
	m_rotationY = g_pad[0]->GetRStickYF();
	
	//	Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * m_rotationX);
	qRot.Apply(m_toCameraPos);

	//	X������̉�]
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * m_rotationY);
	qRot.Apply(m_toCameraPos);

	//	�J�����̉�]�̏�����`�F�b�N����
	//	�����_���王�_�܂ł̃x�N�g���𐳋K������
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.4f) {
		m_toCameraPos = toCameraPosOld;							//	�J��������Ɍ����߂���̂�h��
	}
	else if (toPosDir.y > 0.7f) {
		m_toCameraPos = toCameraPosOld;							//	�J���������Ɍ����߂���̂�h��
	}

	//	���_���v�Z����
	Vector3 pos = m_target + m_toCameraPos;

	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(m_target);
	g_camera3D->Update();

	//m_springCamera.SetPosition(pos);
	//m_springCamera.SetTarget(m_target);
	//m_springCamera.Update();
}