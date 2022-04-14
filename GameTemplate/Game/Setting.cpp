#include "stdafx.h"
#include "Setting.h"

#include "Title.h"

Setting::Setting()
{

}

Setting::~Setting()
{

}

bool Setting::Start()
{
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Choice.wav");
	
	m_apply.Init("Assets/sprite/Setting/Apply.dds", 1600.0f, 900.0f);
	m_backGround.Init("Assets/sprite/Setting/BackGround.dds", 1600.0f, 900.0f);
	m_cancel.Init("Assets/sprite/Setting/Cancel.dds", 1600.0f, 900.0f);
	m_controll.Init("Assets/sprite/Setting/Controll.dds", 1600.0f, 900.0f);
	m_sound.Init("Assets/sprite/Setting/Sound.dds", 1600.0f, 900.0f);
	m_stickSensitivity.Init("Assets/sprite/Setting/StickSensitivity.dds", 1600.0f, 900.0f);
	m_vibration.Init("Assets/sprite/Setting/Vibration.dds", 1600.0f, 900.0f);

	return true;
}

void Setting::Update()
{
	Choice();
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_title = NewGO<Title>(0,"title");
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