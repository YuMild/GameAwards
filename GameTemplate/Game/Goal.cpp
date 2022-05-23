#include "stdafx.h"
#include "Goal.h"

#include "Game.h"
#include "Player.h"
#include "RockOn.h"

Goal::Goal()
{

}

Goal::~Goal()
{

}

bool Goal::Start()
{
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_rockOn = FindGO<RockOn>("rockOn");

	m_rockOn->AddRockOnObject(this);

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
	Length();
}

void Goal::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);

	if (m_state != 1)
	{
		m_modelRender.Draw(rc);
	}
}

void Goal::Hit()
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
		m_game->SetGameState(2);
	}
}

void Goal::Length()
{
	m_length = m_player->GetPosition() - m_position;

	wchar_t x[256];
	swprintf_s(x, 256, L"Length=%f", m_length.Length());
	m_fontRender.SetText(x);
	m_fontRender.SetPosition({ -500.0f, 200.0f,0.0f });
}