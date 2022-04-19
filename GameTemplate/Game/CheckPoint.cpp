#include "stdafx.h"
#include "CheckPoint.h"

#include "Player.h"
#include "RockOn.h"

CheckPoint::CheckPoint()
{

}

CheckPoint::~CheckPoint()
{

}

bool CheckPoint::Start()
{
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");

	m_rockOn->AddRockOnObject(this);

	m_modelRender.Init("Assets/modelData/Stage_0/RespawnPoint.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_boxCollider.BoxInit({ 200.0f,200.0f,200.0f }, m_position, 0.05f);
	m_ghostCollider.CreateBox(m_position, m_rotation, { 220.0f,220.0f,220.0f });

	return true;
}

void CheckPoint::Update()
{
	m_modelRender.Update();
	Hit();
}

void CheckPoint::Render(RenderContext& rc)
{
	if (m_state != 1)
	{
		m_modelRender.Draw(rc);
	}
}

void CheckPoint::Hit()
{
	//キャラクタコントローラーとゴーストオブジェクトのあたり判定を行う。
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true && m_player->GetPlayerSpeed() >= 500.0f) {
			//m_physicsGhostObjectとぶつかった。
			//フラグをtrueにする。
			m_isHit = true;
		}
		});

	if (m_isHit == true)
	{
		m_aliveTime += g_gameTime->GetFrameDeltaTime();
	}
	if (m_aliveTime >= 0.05f && m_isHit == true)
	{
		m_player->SetReSpawnPosition(m_position);
		m_state = 1;
		m_boxCollider.RemoveRigidBoby();
		m_ghostCollider.Release();
		m_isHit = false;
	}
}