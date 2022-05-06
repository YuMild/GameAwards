#include "stdafx.h"
#include "ReSpawnPoint.h"

#include "Player.h"
#include "RockOn.h"

ReSpawnPoint::ReSpawnPoint()
{

}

ReSpawnPoint::~ReSpawnPoint()
{

}

bool ReSpawnPoint::Start()
{
	m_rockOn = FindGO<RockOn>("rockOn");
	m_player = FindGO<Player>("player");

	m_modelRender.Init("Assets/modelData/Stage_0/ReSpawnPoint.tkm", true);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_ghostCollider.CreateBox(m_position, m_rotation, { 300.0f,300.0f,300.0f });

	return true;
}

void ReSpawnPoint::Update()
{
	m_modelRender.Update();
	Hit();
}

void ReSpawnPoint::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void ReSpawnPoint::Hit()
{
	m_coolTime += g_gameTime->GetFrameDeltaTime();

	//キャラクタコントローラーとゴーストオブジェクトのあたり判定を行う。
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true && m_coolTime >= 1.0f) {
			//m_physicsGhostObjectとぶつかった。
			//フラグをtrueにする。
			m_isHit = true;
		}
		});

	if (m_isHit == true)
	{
		m_coolTime = 0.0f;
		m_isHit = false;
	}
}