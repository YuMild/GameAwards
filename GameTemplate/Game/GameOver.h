#pragma once
class GameOver : public IGameObject
{
public:

	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	SpriteRender	m_backGround;
	SpriteRender	m_font;
};