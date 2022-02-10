#include "stdafx.h"
#include "Game.h"

#include "BackGround.h"
#include "ChargeGauge.h"
#include "GameCamera.h"
#include "Player.h"

bool Game::Start()
{
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_chargeGauge = NewGO<ChargeGauge>(0, "chargeGauge");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_player = NewGO<Player>(0, "player");
	return true;
}
void Game::Update()
{
	
}
void Game::Render(RenderContext& rc)
{

}