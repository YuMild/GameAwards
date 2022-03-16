#pragma once

class Player;
class Stage_0;

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

	Player* m_player;
	Stage_0* m_stage_0;
};