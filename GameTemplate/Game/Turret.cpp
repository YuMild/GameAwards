#include "stdafx.h"
#include "Turret.h"

#include "Player.h"
#include "RockOn.h"

namespace
{
	float COOL_TIME = 3.0f;
	float ALIVE_TIME = 1.0f;
}

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

	EffectEngine::GetInstance()->ResistEffect(5, u"Assets/Effect/Selfmade/Beam.efk");

	m_boxCollider.BoxInit({ 200.0f,200.0f,200.0f }, m_position, 0.1);

	m_effectRotation = m_rotation;
	m_effectRotation.AddRotationDegY(0.0f);

	return true;
}

void Turret::Update()
{
	m_modelRender.Update();
	Hit();

	wchar_t x[256];
	swprintf_s(x, 256, L"Fire");
	m_fontRender.SetText(x);
	m_fontRender.SetPosition({ -500.0f, 50.0f, 0.0f });
}

void Turret::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

	if (m_state == 1)
	{
		m_fontRender.Draw(rc);
	}
}

void Turret::Hit()
{
	m_coolTime += g_gameTime->GetFrameDeltaTime();

	if (m_coolTime >= COOL_TIME)
	{
		if (m_effectCoolTime == false)
		{
			m_beam = NewGO<EffectEmitter>(5);
			m_beam->Init(5);
			m_beam->SetRotation(m_effectRotation);
			m_beam->SetScale(Vector3::One * 100.0f);
			m_beam->SetPosition({ m_position.x,m_position.y + 70.0f,m_position.z });
			m_beam->Play();
			m_effectCoolTime = true;
		}
		m_beamCollider.CreateBox(m_position, m_rotation, { 30.0f,30.0f,3000.0f });
		m_state = 1;
		m_aliveTime += g_gameTime->GetFrameDeltaTime();
	}

	if (m_aliveTime >= ALIVE_TIME)
	{
		m_beamCollider.Release();
		m_effectCoolTime = false;
		m_state = 0;
		m_coolTime = 0.0f;
		m_aliveTime = 0.0f;
	}

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
		m_player->SetState(1);
		m_isHit = false;
	}
}