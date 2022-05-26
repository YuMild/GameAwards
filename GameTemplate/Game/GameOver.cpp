#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

bool GameOver::Start()
{
	m_backGround.Init("Assets/sprite/GameOver/BackGround.dds", 1600.0f, 900.0f);
	
	m_font.Init("Assets/sprite/GameOver/GameOver.dds", 1600.0f, 900.0f);

	return true;
}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_backGround.Draw(rc);
	m_font.Draw(rc);
}