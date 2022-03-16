#include "stdafx.h"
#include "GameCamera.h"


#include "Player.h"

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

	g_camera3D->SetFar(10000.0f);

	m_springCamera.Init(
		*g_camera3D,			//	�΂˃J�����̏������s���J�������w�肷��
		10000.0f				//	�J�����̈ړ����x�̍ő�l
	);
	
	m_springCamera.SetDampingRate(0.7f);

	return true;
}

void GameCamera::Update()
{
	m_target = m_player->GetPosition();
	m_target.y += 0.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	//	�p�b�h�̓��͂��g���ăJ��������
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//	Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_toCameraPos);

	//	X������̉�]
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toCameraPos);

	//	�J�����̉�]�̏�����`�F�b�N����
	//	�����_���王�_�܂ł̃x�N�g���𐳋K������
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		m_toCameraPos = toCameraPosOld;							//	�J��������Ɍ����߂���̂�h��
	}
	else if (toPosDir.y > 0.9f) {
		m_toCameraPos = toCameraPosOld;							//	�J���������Ɍ����߂���̂�h��
	}

	//	���_���v�Z����
	Vector3 pos = m_target + m_toCameraPos;

	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(m_target);
	m_springCamera.Update();
}