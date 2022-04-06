#include "stdafx.h"
#include "Setting.h"

Setting::Setting()
{

}

Setting::~Setting()
{

}

bool Setting::Start()
{
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Choice.wav");
	
	return true;
}

void Setting::Update()
{
	Choice();
}

void Setting::Render(RenderContext& rc)
{

}

void Setting::Choice()
{
	if (m_choiceState >= 0 && m_choiceState < 2 && g_pad[0]->IsTrigger(enButtonDown))
	{
		m_choiceState += 1;
	}

	if (m_choiceState <= 2 && m_choiceState > 0 && g_pad[0]->IsTrigger(enButtonUp))
	{
		m_choiceState += 1;
	}
}