#pragma once

class ChargeShot;
class GameCamera;
class Player;
class RockOn;
class Stage_0;

class Game : public IGameObject
{
public:

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:

	void Death();

	ChargeShot* m_chargeShot;
	GameCamera* m_gameCamera;
	Player* m_player;
	RockOn* m_rockOn;
	Stage_0* m_stage_0;
};

