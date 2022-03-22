#include "stdafx.h"
#include "RockOn.h"

#include "Bumper.h"
#include "Player.h"

RockOn::RockOn()
{

}

RockOn::~RockOn()
{

}

bool RockOn::Start()
{
	m_rockOn_1.Init("Assets/sprite/RockOn/RockOn_1.dds", 300.0f, 300.0f);
	m_rockOn_1.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_1.Update();
	m_rockOn_2.Init("Assets/sprite/RockOn/RockOn_2.dds", 300.0f, 300.0f);
	m_rockOn_2.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_2.Update();
	m_rockOn_3.Init("Assets/sprite/RockOn/RockOn_3.dds", 300.0f, 300.0f);
	m_rockOn_3.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_3.Update();
	m_rockOn_4.Init("Assets/sprite/RockOn/RockOn_4.dds", 300.0f, 300.0f);
	m_rockOn_4.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_4.Update();
	m_rockOn_5.Init("Assets/sprite/RockOn/RockOn_5.dds", 300.0f, 300.0f);
	m_rockOn_5.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_5.Update();
	m_rockOn_6.Init("Assets/sprite/RockOn/RockOn_6.dds", 300.0f, 300.0f);
	m_rockOn_6.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_6.Update();
	m_rockOn_7.Init("Assets/sprite/RockOn/RockOn_7.dds", 300.0f, 300.0f);
	m_rockOn_7.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_7.Update();
	m_rockOn_8.Init("Assets/sprite/RockOn/RockOn_8.dds", 300.0f, 300.0f);
	m_rockOn_8.SetPosition(Vector3{ 0.0f,0.0f,0.0f });
	m_rockOn_8.Update();

	m_bumper = FindGO<Bumper>("bumper");
	m_player = FindGO<Player>("player");
	
	return true;
}

void RockOn::Update()
{
	Judge();
}

void RockOn::Render(RenderContext& rc)
{
	m_rockOn_1.Draw(rc);
	m_rockOn_2.Draw(rc);
	m_rockOn_3.Draw(rc);
	m_rockOn_4.Draw(rc);
	m_rockOn_5.Draw(rc);
	m_rockOn_6.Draw(rc);
	m_rockOn_7.Draw(rc);
	m_rockOn_8.Draw(rc);

	m_fontRender.Draw(rc);
}

void RockOn::Judge()
{
	//プレイヤーからバンパーに向かうベクトルを求める
	m_difference = m_bumper->GetPosition() - m_player->GetPosition();

	//距離が遠過ぎたり近過ぎるとロックオンしない
	if (m_difference.Length() >= 3000.0f || m_difference.Length() < 100.0f)
	{
		m_isReady = false;
	}
	else
	{
		m_isReady = true;
	}

	//正規化
	m_difference.y = 0.0f;
	m_difference.Normalize();

	//ロックオン視野角を作成
	float angle = acosf(g_camera3D->GetForward().Dot(m_difference));

	//距離が適切で且つロックオン視野角にオブジェクトが入っていたら
	if (angle < (Math::PI / 180.0f) * 30.0f && m_isReady == true)
	{
		//ロックオンする
		m_isRockOn == true;
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"RockOn%d", int());
		m_fontRender.SetText(wcsbuf);
		m_fontRender.SetPosition({ 100.0f,100.0f,0.0f });
		//g_camera3D->SetTarget(m_bumper->GetPosition());
	}
	else
	{
		//ロックオンしない
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"%d", int());
		m_fontRender.SetText(wcsbuf);
		m_fontRender.SetPosition({ 100.0f,100.0f,0.0f });
	}
}

void RockOn::Sprite()
{
	//m_rockOn_1
}