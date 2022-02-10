#pragma once

class BackGround;
class ChargeGauge;
class GameCamera;
class Player;

class Game : public IGameObject
{
public:

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:

	BackGround* m_backGround;
	ChargeGauge* m_chargeGauge;
	GameCamera* m_gameCamera;
	Player* m_player;
};

