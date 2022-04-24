#include "stdafx.h"
#include "Game.h"

#include "Bound.h"
#include "ChargeShot.h"
#include "First.h"
#include "GameCamera.h"
#include "GameLight.h"
#include "Player.h"
#include "PowerCharge.h"
#include "RockOn.h"
#include "SonicBoom.h"
#include "Stage_0.h"
#include "TimeLimit.h"

Game::Game()
{

}

Game::~Game()
{
	//エフェクト
	const auto& bounds = FindGOs<Bound>("bound");
	int buondSize = bounds.size();
	for (int i = 0; i < buondSize; i++)
	{
		DeleteGO(bounds[i]);
	}
	const auto& powerChages = FindGOs<PowerCharge>("powerCharge");
	int powerChargeSize = powerChages.size();
	for (int i = 0; i < powerChargeSize; i++)
	{
		DeleteGO(powerChages[i]);
	}
	const auto& rockOns = FindGOs<RockOn>("rockOn");
	int rockOnSize = rockOns.size();
	for (int i = 0; i < rockOnSize; i++)
	{
		DeleteGO(rockOns[i]);
	}
	const auto& sonicBooms = FindGOs<SonicBoom>("sonicBoom");
	int sonicBoomSize = sonicBooms.size();
	for (int i = 0; i < sonicBoomSize; i++)
	{
		DeleteGO(sonicBooms[i]);
	}
	DeleteGO(m_chargeShot);
	DeleteGO(m_gameCamera);
	DeleteGO(m_gameLight);
	DeleteGO(m_player);
	DeleteGO(m_stage_0);
	DeleteGO(m_timeLimit);
}

bool Game::Start()
{
	m_chargeShot = NewGO<ChargeShot>(0, "chargeShot");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_gameLight = NewGO<GameLight>(0, "gameLight");
	m_player = NewGO<Player>(0, "player");
	m_rockOn = NewGO<RockOn>(0, "rockOn");
	m_stage_0 = NewGO<Stage_0>(0, "stage_0");
	m_timeLimit = NewGO<TimeLimit>(0, "timeLimit");

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
	if (m_state == 2)
	{
		DeleteGO(this);
		m_first = NewGO<First>(0, "first");
		m_state = 0;
	}
}