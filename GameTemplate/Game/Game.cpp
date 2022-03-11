#include "stdafx.h"
#include "Game.h"

#include "Stage1.h"
#include "ChargeShot.h"
#include "GameCamera.h"
#include "Player.h"

bool Game::Start()
{
	m_stage1 = NewGO<Stage1>(0, "stage1");
	m_chargeShot = NewGO<ChargeShot>(0, "chargeShot");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_player = NewGO<Player>(0, "player");
	return true;
}
void Game::Update()
{
	Death();
}
void Game::Render(RenderContext& rc)
{

}

void Game::Death()
{
	if (m_player->GetPosition().y <= -300.0f || g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(m_player);
		DeleteGO(m_gameCamera);
		DeleteGO(m_chargeShot);
		m_chargeShot = NewGO<ChargeShot>(0, "chargeShot");
		m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
		m_player = NewGO<Player>(0, "player");
	}
}