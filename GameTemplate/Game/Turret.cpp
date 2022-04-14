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
	m_rockOn = FindGO<RockOn>("rockOn");
	m_player = FindGO <Player>("player");

	m_modelRender.Init("Assets/modelData/Stage_0/Turret.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_boxCollider.BoxInit({ 100.0f,100.0f,100.0f }, m_position, 0.5);
	m_ghostCollider.CreateBox(m_position, m_rotation, { 105.0f,105.0f,105.0f });

	return true;
}

void Turret::Update()
{
	m_modelRender.Update();
}

void Turret::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Turret::Hit()
{
	//キャラクタコントローラーとゴーストオブジェクトのあたり判定を行う。
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true) {
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
		DeleteGO(this);
	}
}