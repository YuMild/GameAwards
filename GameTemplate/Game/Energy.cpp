#include "stdafx.h"
#include "Energy.h"

#include "Player.h"
#include "RockOn.h"
#include "TimeLimit.h"

Energy::Energy()
{

}

Energy::~Energy()
{

}

bool Energy::Start()
{
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");
	m_timeLimit = FindGO<TimeLimit>("timeLimit");

	EffectEngine::GetInstance()->ResistEffect(4, u"Assets/Effect/Selfmade/BrokenExplosion.efk");

	m_modelRender.Init("Assets/modelData/Stage_0/Item.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_ghostCollider.CreateBox(m_position, m_rotation, { 105.0f,105.0f,105.0f });

	return true;
}

void Energy::Update()
{
	m_modelRender.Update();
	Hit();
}

void Energy::Render(RenderContext& rc)
{
	if (m_state != 1)
	{
		m_modelRender.Draw(rc);
	}
}

void Energy::Hit()
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
		m_timeLimit->AddTime(1.0f);
		m_explosion = NewGO<EffectEmitter>(4);
		m_explosion->Init(4);
		m_explosion->SetScale(Vector3::One * 5.0f);
		m_explosion->SetPosition({ m_position.x,m_position.y,m_position.z });
		m_explosion->Play();
		m_state = 1;
		m_ghostCollider.Release();
		m_isHit = false;
	}
}