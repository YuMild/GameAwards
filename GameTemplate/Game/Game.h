#pragma once
class BackGround;
class PhysicsBall;
class Player;
class Game : public IGameObject
{
public:

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:
	Player* m_player = nullptr;
	PhysicsBall* m_physicsBall = nullptr;
	BackGround* m_backGround = nullptr;
};

