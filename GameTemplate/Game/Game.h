#pragma once

class Bound;
class ChargeShot;
class GameCamera;
class Player;
class PowerCharge;
class RockOn;
class SonicBoom;
class Stage_0;
class Title;
class TimeLimit;

class Game : public IGameObject
{
public:

	Game();
	~Game();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	int SetGemeEnd(const int& state)
	{
		m_state = state;
		return m_state;
	}

private:

	void Death();
	
	Bound*					m_bound;
	ChargeShot*				m_chargeShot;
	GameCamera*				m_gameCamera;
	Player*					m_player;
	PowerCharge*			m_powerCharge;
	RockOn*					m_rockOn;
	SonicBoom*				m_sonicBoom;
	Stage_0*				m_stage_0;
	Title*					m_title;
	TimeLimit*				m_timeLimit;

	int						m_state;
};

