#include "stdafx.h"
#include "ChargeGauge.h"

ChargeGauge::ChargeGauge()
{

}

ChargeGauge::~ChargeGauge()
{

}

bool ChargeGauge::Start()
{
	m_gauge2D.Init("Assets/sprite/MPbar", 100.0f, 100.0f);
	m_gauge2D.SetPosition(Vector3(-500.0f, -400.0f, 0.0f));
	m_gauge2D.Update();

	return true;
}