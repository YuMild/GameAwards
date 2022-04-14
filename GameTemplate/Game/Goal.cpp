#include "stdafx.h"
#include "Goal.h"

#include "Game.h"
#include "Player.h"

Goal::Goal()
{

}

Goal::~Goal()
{

}

bool Goal::Start()
{
	m_player = FindGO<Player>("player");

	m_modelRender.Init("Assets/modelData/Stage_0/Goal.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_ghostCollider.CreateBox(m_position, m_rotation, { 105.0f,105.0f,105.0f });

	return true;
}

void Goal::Update()
{
	m_modelRender.Update();
	Hit();
}

void Goal::Render(RenderContext& rc)
{
	if (m_state != 1)
	{
		m_modelRender.Draw(rc);
	}
}

void Goal::Hit()
{
	//�L�����N�^�R���g���[���[�ƃS�[�X�g�I�u�W�F�N�g�̂����蔻����s���B
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true) {
			//m_physicsGhostObject�ƂԂ������B
			//�t���O��true�ɂ���B
			m_isHit = true;
		}
		});

	if (m_isHit == true)
	{
		m_state = 1;
		m_ghostCollider.Release();
		m_isHit = false;
		m_game->SetGemeEnd(1);
	}
}