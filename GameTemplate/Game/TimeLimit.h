#pragma once

class Game;

class TimeLimit : public IGameObject
{
public:

	TimeLimit();
	~TimeLimit();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void AddTime(const float addTime)
	{
		m_limitTimer += addTime;
	}

private:

	FontRender	m_fontRender;

	Game*		m_game;

	float		m_limitTimer = 0.0f;
};

