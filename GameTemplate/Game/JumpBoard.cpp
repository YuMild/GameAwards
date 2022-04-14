#include "stdafx.h"
#include "JumpBoard.h"

#include "Player.h"
#include "RockOn.h"

JumpBoard::JumpBoard()
{

}

JumpBoard::~JumpBoard()
{

}

bool JumpBoard::Start()
{
	m_shoot = { 0.0f,0.0f,-1.0f };
	m_rotation.Apply(m_shoot);
	m_rotation.Normalize();

	m_rockOn = FindGO<RockOn>("rockOn");

	m_modelRender.Init("Assets/modelData/Stage_0/JumpBoard.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	m_player = FindGO<Player>("player");

	m_phyStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	m_ghostCollider.CreateBox(m_position, m_rotation, { 1000.0f,1000.0f,300.0f });

	return true;
}

void JumpBoard::Update()
{
	m_modelRender.Update();
	Hit();

	wchar_t x[256];
	swprintf_s(x, 256, L"X=%f", m_shoot.x);
	m_fontRenderX.SetText(x);
	m_fontRenderX.SetPosition({ -500.0f, 300.0f, 0.0f });
	wchar_t y[256];
	swprintf_s(y, 256, L"Y=%f", m_shoot.y);
	m_fontRenderY.SetText(y);
	m_fontRenderY.SetPosition({ -500.0f, 250.0f, 0.0f });
	wchar_t z[256];
	swprintf_s(z, 256, L"Z=%f", m_shoot.z);
	m_fontRenderZ.SetText(z);
	m_fontRenderZ.SetPosition({ -500.0f, 200.0f, 0.0f });
}

void JumpBoard::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

	if (m_isHit == true)
	{
		m_fontRenderX.Draw(rc);
		m_fontRenderY.Draw(rc);
		m_fontRenderZ.Draw(rc);
	}
}

void JumpBoard::Hit()
{
	m_coolTime += g_gameTime->GetFrameDeltaTime();

	//キャラクタコントローラーとゴーストオブジェクトのあたり判定を行う。
	PhysicsWorld::GetInstance()->ContactTest(m_player->m_rigidBody, [&](const btCollisionObject& contactObject) {
		if (m_ghostCollider.IsSelf(contactObject) == true && m_coolTime >= 0.25f) {
			//m_physicsGhostObjectとぶつかった。
			//フラグをtrueにする。
			m_isHit = true;
		}
		});

	if (m_isHit == true)
	{
		m_coolTime = 0.0f;
		m_shoot *= 5000.0f;
		Vector3 zero = Vector3::Zero;
		m_player->SetMoveSpeed(zero);
		m_player->SetMoveSpeed(m_shoot);
		m_isHit = false;
	}
}