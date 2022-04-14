#include "stdafx.h"
#include "Game.h"

#include "Bumper.h"
#include "ChargeShot.h"
#include "GameCamera.h"
#include "Player.h"
#include "RockOn.h"
#include "Stage_0.h"

bool Game::Start()
{
	m_stage_0 = NewGO<Stage_0>(0, "stage_0");
	m_chargeShot = NewGO<ChargeShot>(0, "chargeShot");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_player = NewGO<Player>(0, "player");
	m_rockOn = NewGO<RockOn>(0, "rockOn");
	
	//m_player = FindGO<Player>("player");

	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

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
	if (m_state == 1)
	{
		DeleteGO(m_chargeShot);
		DeleteGO(m_gameCamera);
		DeleteGO(m_player);
		DeleteGO(m_stage_0);
		DeleteGO(m_rockOn);
		m_chargeShot = NewGO<ChargeShot>(0, "chargeShot");
		m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
		m_player = NewGO<Player>(0, "player");
		m_stage_0 = NewGO<Stage_0>(0, "stage_0");
		m_rockOn = NewGO<RockOn>(0, "rockOn");
		m_state = 0;
	}
}