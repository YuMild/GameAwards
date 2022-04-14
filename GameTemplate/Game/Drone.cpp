#include "stdafx.h"
#include "Drone.h"

#include "Player.h"
#include "RockOn.h"

Drone::Drone()
{

}

Drone::~Drone()
{

}

bool Drone::Start()
{
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");

	m_rockOn->AddRockOnObject(this);
	
	m_modelRender.Init("Assets/modelData/Stage_0/Drone.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_boxCollider.BoxInit({ 100.0f,100.0f,100.0f }, m_position, 0.1);
	m_ghostCollider.CreateBox(m_position, m_rotation, { 105.0f,105.0f,105.0f });

	return true;
}

void Drone::Update()
{
	m_modelRender.Update();
}

void Drone::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Drone::Hit()
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