#pragma once

class Stage1;
class ChargeShot;
class GameCamera;
class Player;

class Game : public IGameObject
{
public:

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:

	void Death();

	Stage1* m_stage1;
	ChargeShot* m_chargeShot;
	GameCamera* m_gameCamera;
	Player* m_player;
};

