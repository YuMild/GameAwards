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

	bool GetRockOnJudge() const
	{
		return m_isRockOn;
	}

private:
	/// <summary>
	/// ロックオンするか否かの判定をする。
	/// </summary>
	void Judge();

	/// <summary>
	/// 画像の描画処理を管理。
	/// </summary>
	void Sprite();

	//画像
	SpriteRender m_rockOn_1;
	SpriteRender m_rockOn_2;
	SpriteRender m_rockOn_3;
	SpriteRender m_rockOn_4;
	SpriteRender m_rockOn_5;
	SpriteRender m_rockOn_6;
	SpriteRender m_rockOn_7;
	SpriteRender m_rockOn_8;

	//フォント
	FontRender m_fontRender;

	Vector3 m_difference;

	Bumper* m_bumper;
	Player* m_player;

	bool m_isReady = false;
	bool m_isRockOn = false;
};