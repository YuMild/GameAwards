#include "stdafx.h"
#include "ChargeShot.h"

#include "Player.h"

namespace
{

}

ChargeShot::ChargeShot()
{

}

ChargeShot::~ChargeShot()
{

}

bool ChargeShot::Start()
{
	m_charge2D.Init("Assets/sprite/Charge/Charge.dds", 700.0f, 700.0f);
	m_charge2D.SetPosition(Vector3(-400.0f, -250.0f, 0.0f));
	m_charge2D.Update();

	m_chargeInside2D.Init("Assets/sprite/Charge/ChargeInside.dds", 315.0f, 315.0f);
	m_chargeInside2D.SetPosition(Vector3(-295.0f, -288.0f, 0.0f));
	m_chargeInside2D.Update();

	m_player = FindGO<Player>("player");

	return true;
}

void ChargeShot::Update()
{
	Cut();
	Speed();
	m_charge2D.Update();
	m_chargeInside2D.Update();
}

void ChargeShot::Render(RenderContext& rc)
{
	//フォントを描画する。
	m_fontRender.Draw(rc);

	m_charge2D.Draw(rc);
	m_chargeInside2D.Draw(rc);
}

void ChargeShot::Cut()
{
	m_chargeInside2D.SetIsDisplayRestrictionRightSide(true);
	m_chargeInside2D.SetLimitedX(m_player->GetCharge());
}

void ChargeShot::Speed()
{
	//m_speed = m_player->GetPlayerSpeed();
	// 速度を1フレームの変位量(実際に動いた量)から算出する。
	Vector3 vSpeed = m_player->GetPositionDeltaValue();
	// 速度をcm/frameからcm/秒に変更する。
	vSpeed /= g_gameTime->GetFrameDeltaTime();

	m_speed = vSpeed.Length();
	

	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%03d", int(m_speed * 3600 / 100000 ));

	m_fontRender.SetText(wcsbuf);

	//フォントの位置を設定。
	m_fontRender.SetPosition({ -630.0f, -330.0f, 0.0f });

	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	m_fontRender.SetColor({ 0.0f, 230.0f, 255.0f,0.0f });
	m_fontRender.SetPivot(1.0f, 0.5f);
}