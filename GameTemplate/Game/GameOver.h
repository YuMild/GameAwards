#pragma once

class Game;

class GameOver : public IGameObject
{
public:

	GameOver();
	~GameOver();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// ‰æ‘œ‚ğŠÇ—B
	/// </summary>
	void Sprite();

	SpriteRender	m_backGround;
	SpriteRender	m_font;

	Game*			m_game;

	float			m_scale = 0.0f;
};