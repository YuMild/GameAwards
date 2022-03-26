#pragma once

#include<LevelRender.h>;

class Bumper;
class Drone;
class HoneyCombBlock;
class JumpBoard;
class Player;
class Stage_0_Ground;
class Stage_0_Wall;

class Stage_0 : public IGameObject
{
public:

	Stage_0();
	~Stage_0();
	bool Start();
	void Update();
	void Render(RenderContext(& rc));

private:
	LevelRender					m_levelRender;

	//インスタンス
	Bumper*						m_bumper;
	Drone*						m_drone;
	HoneyCombBlock*				m_honeyCombBlock;
	JumpBoard*					m_jumpBoard;
	Player*						m_player;
	Stage_0_Ground*				m_stage_0_Ground;
	Stage_0_Wall*				m_stage_0_Wall;
};