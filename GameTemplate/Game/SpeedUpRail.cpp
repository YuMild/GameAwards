#include "stdafx.h"
#include "SpeedUpRail.h"

#include "Player.h"
#include "RockOn.h"

SpeedUpRail::SpeedUpRail()
{

}

SpeedUpRail::~SpeedUpRail()
{

}

bool SpeedUpRail::Start()
{
	m_shoot = { 0.0f,0.0f,-1.0f };

	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");

	m_rockOn->AddRockOnObject(this);

	m_modelRender.Init("Assets/modelData/Stage_0/SpeedUpRail.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_ghostCollider.CreateBox(m_position, m_rotation, { 220.0f,220.0f,220.0f });

	return true;
}

void SpeedUpRail::Update()
{
	m_modelRender.Update();
	Hit();
}

void SpeedUpRail::Render(RenderContext& rc)
{
	if (m_state != 1)
	{
		m_modelRender.Draw(rc);
	}
}

void SpeedUpRail::Hit()
{
	//�L�����N�^�R���g���[���[�ƃS�[�X�g�I�u�W�F�N�g�̂����蔻����s���B
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true && m_coolTime >= 5.0f) {
			//m_physicsGhostObject�ƂԂ������B
			//�t���O��true�ɂ���B
			m_isHit = true;
		}
		});

	if (m_isHit == true)
	{
		m_coolTime = 0.0f;
		Vector3 zero = Vector3::Zero;				//�X�s�[�h��0�ɂ���B
		m_player->SetMoveSpeed(zero);				//�X�s�[�h��0�ɂ���B
		Vector3 shoot = m_shoot;
		shoot *= 50000000.0f;
		m_player->SetMoveSpeed(shoot);
		m_isHit = false;
	}
}