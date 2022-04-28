#include "stdafx.h"
#include "Door.h"

#include "Player.h"
#include "RockOn.h"

Door::Door()
{

}

Door::~Door()
{

}

bool Door::Start()
{
	m_rockOn = FindGO<RockOn>("rockOn");
	m_player = FindGO<Player>("player");

	m_modelRender.Init("Assets/modelData/Stage_0/Door.tkm",true);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
	m_open[enAnimationClip_Open].Load("Assets/animData/Door.tka");
	m_open[enAnimationClip_Open].SetLoopFlag(false);

	m_ghostCollider.CreateBox(m_position, m_rotation, { 2000.0f,2000.0f,2000.0f });

	return true;
}

void Door::Update()
{
	m_modelRender.Update();
	Hit();
}

void Door::Render(RenderContext& rc)
{
	if (m_state != 1)
	{
		m_modelRender.Draw(rc);
	}
}

void Door::Hit()
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
		m_modelRender.PlayAnimation(enAnimationClip_Open, 0.0f);
		m_state = 1;
		m_isHit = false;
	}
}