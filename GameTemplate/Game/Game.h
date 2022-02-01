#pragma once
class BackGround;
class Player;
class Game : public IGameObject
{
public:

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:
	Player* m_player = nullptr;
	BackGround* m_backGround = nullptr;
};

