#include "stdafx.h"
#include "Length.h"

#include "Goal.h"

namespace
{

}

Length::Length()
{

}

Length::~Length()
{

}

bool Length::Start()
{
	m_goal = FindGO<Goal>("goal");

	m_length2D.Init("Assets/sprite/Length/Length.dds", 700.0f, 700.0f);
	m_length2D.SetPosition(Vector3(400.0f, -250.0f, 0.0f));
	m_length2D.Update();

	m_lengthInside2D.Init("Assets/sprite/Length/ChargeInside.dds", 315.0f, 315.0f);
	m_lengthInside2D.SetPosition(Vector3(295.0f, -288.0f, 0.0f));
	m_lengthInside2D.Update();

	return true;
}

void Length::Update()
{
	//Cut();
	LengthFont();
	m_length2D.Update();
	m_lengthInside2D.Update();
}

void Length::Render(RenderContext& rc)
{
	//フォントを描画する。
#ifdef K2_DEBUG
	m_fontRender.Draw(rc);
#endif

	m_length2D.Draw(rc);
	m_lengthInside2D.Draw(rc);
}

void Length::Cut()
{
	m_length = m_goal->GetLength();

	m_lengthInside2D.SetIsDisplayRestrictionRightSide(true);
	m_lengthInside2D.SetLimitedX(m_length);
}

void Length::LengthFont()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%03d", int(m_length));

	m_fontRender.SetText(wcsbuf);

	//フォントの位置を設定。
	m_fontRender.SetPosition({ 7500.0f, -330.0f, 0.0f });

	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	m_fontRender.SetColor({ 0.0f, 230.0f, 255.0f,0.0f });
	m_fontRender.SetPivot(1.0f, 0.5f);
}