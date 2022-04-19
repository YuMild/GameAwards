#include "stdafx.h"
#include "Turret.h"

#include "Player.h"
#include "RockOn.h"

Turret::Turret()
{

}

Turret::~Turret()
{

}

bool Turret::Start()
{
	m_direction = { 0.0f,0.5f,0.5f };
	m_beamRotation.Apply(m_direction);
	m_beamRotation.Normalize();

	m_rockOn = FindGO<RockOn>("rockOn");
	m_player = FindGO <Player>("player");

	m_modelRender.Init("Assets/modelData/Stage_0/Turret.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_boxCollider.BoxInit({ 100.0f,100.0f,100.0f }, m_position, 0.1);
	m_ghostCollider.CreateBox(m_position, m_rotation, { 105.0f,105.0f,105.0f });
	m_beamCollider.CreateBox(m_position, m_beamRotation, { 50.0f,1000.0f,50.0f });

	return true;
}

void Turret::Update()
{
	m_modelRender.Update();
	Hit();
}

void Turret::Render(RenderContext& rc)
{
	if (m_state != 1)
	{
		m_modelRender.Draw(rc);
	}
}

void Turret::Hit()
{
	//キャラクタコントローラーとゴーストオブジェクトのあたり判定を行う。
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_beamCollider.IsSelf(contactObject) == true) {
			//m_physicsGhostObjectとぶつかった。
			//フラグをtrueにする。
			m_isHit = true;
		}
		});

	if (m_isHit == true)
	{
		m_aliveTime += g_gameTime->GetFrameDeltaTime();
	}
	if (m_aliveTime >= 0.05f)
	{
		m_state = 1;
		m_boxCollider.RemoveRigidBoby();
		m_ghostCollider.Release();
		m_beamCollider.Release();
		m_isHit = false;
	}
}