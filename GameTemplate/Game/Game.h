#pragma once

class BackGround;
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

	BackGround* m_backGround;
	ChargeShot* m_chargeShot;
	GameCamera* m_gameCamera;
	Player* m_player;
};

