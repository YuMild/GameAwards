#include "stdafx.h"
#include "Setting.h"

#include "Title.h"

namespace
{
	float ZOOM = 1.2f;
}

Setting::Setting()
{

}

Setting::~Setting()
{

}

bool Setting::Start()
{
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Choice.wav");
	
	m_apply.Init("Assets/sprite/Setting/Apply.dds", 1000.0f, 1000.0f);
	m_apply.SetPosition({ 200.0f,-300.0f,0.0f });
	m_apply.Update();
	m_backGround.Init("Assets/sprite/Setting/BackGround.dds", 1600.0f, 900.0f);
	m_backGround.SetPosition({ 0.0f,0.0f,0.0f });
	m_backGround.Update();
	m_cancel.Init("Assets/sprite/Setting/Cancel.dds", 1000.0f, 1000.0f);
	m_cancel.SetPosition({ -200.0f,-300.0f,0.0f });
	m_cancel.Update();
	m_controll.Init("Assets/sprite/Setting/Controll.dds", 1000.0f, 1000.0f);
	m_controll.SetPosition({ -250.0f,300.0f,0.0f });
	m_controll.Update();
	m_sound.Init("Assets/sprite/Setting/Sound.dds", 1000.0f, 1000.0f);
	m_sound.SetPosition({ 250.0f,300.0f,0.0f });
	m_sound.Update();
	m_stickSensitivity.Init("Assets/sprite/Setting/StickSensitivity.dds", 1000.0f, 1000.0f);
	m_stickSensitivity.SetPosition({ -200.0f,100.0f,0.0f });
	m_stickSensitivity.Update();
	m_vibration.Init("Assets/sprite/Setting/Vibration.dds", 1000.0f, 1000.0f);
	m_vibration.SetPosition({ -200.0f,0.0f,0.0f });
	m_vibration.Update();

	return true;
}

void Setting::Update()
{
	Choice();
	Sprite();
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(this);
	}
}

void Setting::Render(RenderContext& rc)
{
	m_backGround.Draw(rc);
	m_apply.Draw(rc);
	m_cancel.Draw(rc);
	m_controll.Draw(rc);
	m_sound.Draw(rc);
	m_stickSensitivity.Draw(rc);
	m_vibration.Draw(rc);
}

void Setting::Choice()
{
	if (m_shelf == 0 && g_pad[0]->IsTrigger(enButtonRB1))
	{
		m_shelf = 1;
		m_choiceState = 0;
	}
	else if (m_shelf == 1 && g_pad[0]->IsTrigger(enButtonLB1))
	{
		m_shelf = 0;
		m_choiceState = 0;
	}

	if (m_choiceState >= 0 && m_choiceState < 2 && g_pad[0]->IsTrigger(enButtonDown))
	{
		m_choiceState += 1;
	}

	if (m_choiceState <= 2 && m_choiceState > 0 && g_pad[0]->IsTrigger(enButtonUp))
	{
		m_choiceState += 1;
	}
}

void Setting::Sprite()
{
	if (m_shelf == 0)
	{
		m_controll.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_controll.Update();
	}
	if (m_shelf == 0 && m_choiceState == 0)
	{
		m_stickSensitivity.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_stickSensitivity.Update();
	}
	if (m_shelf == 0 && m_choiceState == 1)
	{
		m_vibration.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_vibration.Update();
	}
	else
	{
		m_vibration.SetScale({ 1.0f,1.0f,1.0f });
		m_vibration.Update();
	}
}