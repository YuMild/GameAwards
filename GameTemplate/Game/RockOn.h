#pragma once

class Bumper;
class Player;

class RockOn : public IGameObject
{
public:
	RockOn();
	~RockOn();
	bool Start();
	void Render(RenderContext& rc);
	void Update();

private:
	/// <summary>
	/// ロックオンするか否かの判定をする。
	/// </summary>
	void Judge();

	//フォント
	FontRender m_fontRender;

	Vector3 m_difference;

	Bumper* m_bumper;
	Player* m_player;

	bool m_isReady = false;
	bool m_isRockOn = false;
};