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
	m_charge2D.Init("Assets/sprite/Charge.dds", 700.0f, 700.0f);
	m_charge2D.SetPosition(Vector3(-400.0f, -250.0f, 0.0f));
	//m_charge2D.Init("Assets/sprite/Charge2.dds", 600.0f, 600.0f);
	//m_charge2D.SetPosition(Vector3(-400.0f, -200.0f, 0.0f));
	m_charge2D.Update();

	m_chargeInside2D.Init("Assets/sprite/ChargeInside.dds", 315.0f, 315.0f);
	m_chargeInside2D.SetPosition(Vector3(-295.0f, -288.0f, 0.0f));
	//m_chargeInside2D.Init("Assets/sprite/ChargeInside2.dds", 195.0f, 195.0f);
	//m_chargeInside2D.SetPosition(Vector3(-253.0f, -222.0f, 0.0f));
	m_chargeInside2D.Update();

	m_player = FindGO<Player>("player");

	return true;
}

void ChargeShot::Update()
{
	Cut();
	m_charge2D.Update();
	m_chargeInside2D.Update();
}

void ChargeShot::Render(RenderContext& rc)
{
	m_charge2D.Draw(rc);
	m_chargeInside2D.Draw(rc);
}

void ChargeShot::Cut()
{
	m_chargeInside2D.SetIsDisplayRestrictionRightSide(true);
	m_chargeInside2D.SetLimitedX(m_player->GetCharge());
}