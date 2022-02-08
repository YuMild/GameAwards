#pragma once

class BackGround;
class ChargeGauge;
class Player;

class Game : public IGameObject
{
public:

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:

	ChargeGauge* m_chargeGauge = nullptr;
	Player* m_player = nullptr;
	BackGround* m_backGround = nullptr;
};

