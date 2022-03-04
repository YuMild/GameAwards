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
	m_gauge2D.Init("Assets/sprite/MPbar.dds", 1000.0f, 1000.0f);
	m_gauge2D.SetPosition(Vector3(-300.0f, -300.0f, 0.0f));
	m_gauge2D.Update();

	m_player = FindGO<Player>("player");

	return true;
}

void ChargeShot::Update()
{
	Cut();
	m_gauge2D.Update();
}

void ChargeShot::Render(RenderContext& rc)
{
	m_gauge2D.Draw(rc);
}

void ChargeShot::Cut()
{
	m_gauge2D.SetIsDisplayRestrictionRightSide(true);
	m_gauge2D.SetLimitedX(m_player->GetCharge());
}