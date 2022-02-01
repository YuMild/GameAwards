#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include"BackGround.h"

bool Game::Start()
{
	m_player = NewGO<Player>(0, "player");
	m_backGround = NewGO<BackGround>(0, "background");
	return true;
}
void Game::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		Vector3 red{ 1.0f,1.0f,5.0f };
		g_sceneLight.SetAmbientLight(red);
	}
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		g_sceneLight.SetPointLightPosition({ 0.0f, 0.0f, 0.0f });
	}
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		g_sceneLight.SetPointLightPosition({ 0.0f, 25.0f, 0.0f });
	}
}
void Game::Render(RenderContext& rc)
{

}