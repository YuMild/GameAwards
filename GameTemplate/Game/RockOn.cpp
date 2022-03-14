#include "stdafx.h"
#include "RockOn.h"

#include "Player.h"
#include "Stage1.h"

RockOn::RockOn()
{

}

RockOn::~RockOn()
{

}

bool RockOn::Start()
{
	m_player = FindGO<Player>("player");
	m_stage1 = FindGO<Stage1>("stage1");
	return true;
}

void RockOn::Update()
{

}

void RockOn::Render(RenderContext& rc)
{

}

void RockOn::Judge()
{
	m_difference = m_player->GetPosition() - m_stage1->GetBumperPosition();

	if (m_difference.LengthSq() <= 1000.0f * 100.0f)
	{
		m_difference.Normalize();
		float cos=m_player.
	}
}