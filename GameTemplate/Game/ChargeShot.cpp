#include "stdafx.h"
#include "ChargeShot.h"

namespace
{
	float GAUGE_DEFAULT = -100.0f;
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
	m_gauge2D.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_gauge2D.Update();

	return true;
}

void ChargeShot::Update()
{
	Cut();
	Charge();
	m_gauge2D.Update();
}

void ChargeShot::Render(RenderContext& rc)
{
	m_gauge2D.Draw(rc);
}

void ChargeShot::Cut()
{
	if (g_pad[0]->IsPress(enButtonA))
	{
		m_isPress = true;
		m_charge += 1.0f;
	}
	else if (m_isPress == true)
	{
		m_isPress = false;
		m_chargeOld = m_charge;
		m_charge = GAUGE_DEFAULT;
	}

	/*if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_charge += 1.0f;
	}*/

	float x = m_charge / 100;
	m_gauge2D.SetIsDisplayRestrictionRightSide(true);
	m_gauge2D.SetLimitedX(x);
}

void ChargeShot::Charge()
{

	/*m_timer += g_gameTime->GetFrameDeltaTime();
	if (m_timer >= 1.0f) {
		m_charge += 1.0f;
		m_timer = 0.0f;
	}*/
}