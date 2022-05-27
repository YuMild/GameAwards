#include "stdafx.h"
#include "ReSpawnPoint.h"

#include "Game.h"
#include "Player.h"
#include "RockOn.h"

namespace
{
	const float EFFECT_SIZE = 230.0f;
}

ReSpawnPoint::ReSpawnPoint()
{

}

ReSpawnPoint::~ReSpawnPoint()
{

}

bool ReSpawnPoint::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");

	m_rockOn->AddRockOnObject(this);

	m_modelRender.Init("Assets/modelData/Stage_0/RespawnPoint.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	EffectEngine::GetInstance()->ResistEffect(16, u"Assets/Effect/Selfmade/CheckPoint.efk");
	m_reSpawnPointEF = NewGO<EffectEmitter>(16);
	m_reSpawnPointEF->Init(16);
	m_reSpawnPointEF->SetPosition({ m_position.x, m_position.y + 150.0f, m_position.z });
	m_reSpawnPointEF->SetScale(Vector3::One * EFFECT_SIZE);

	EffectEngine::GetInstance()->ResistEffect(17, u"Assets/Effect/Selfmade/CheckPointDelete.efk");

	m_ghostCollider.CreateBox(m_position, m_rotation, { 220.0f,220.0f,220.0f });

	return true;
}

void ReSpawnPoint::Update()
{
	Hit();
	Effect();
}

void ReSpawnPoint::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void ReSpawnPoint::Hit()
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
		//エフェクトを止める。
		m_reSpawnPointEF->Stop();

		//デリート時のエフェクトを再生する。
		m_reSpawnPointDeleteEF = NewGO<EffectEmitter>(17);
		m_reSpawnPointDeleteEF->Init(17);
		m_reSpawnPointDeleteEF->SetScale(Vector3::One * EFFECT_SIZE);
		m_reSpawnPointDeleteEF->Play();

		m_player->SetReSpawnPosition(m_position);
		m_state = 1;
		m_ghostCollider.Release();
		m_isHit = false;
	}
}