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