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

	Vector3 GetDifference() const
	{
		return m_difference;
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

	float m_rotation_Num1;
	float m_rotation_Num2;
	float m_rotation_Num3;
	float m_rotation_Num4;
	float m_rotation_Num5;
	float m_rotation_Num6;
	float m_rotation_Num7;
	float m_rotation_Num8;

	Quaternion m_rotation_1;
	Quaternion m_rotation_2;
	Quaternion m_rotation_3;
	Quaternion m_rotation_4;
	Quaternion m_rotation_5;
	Quaternion m_rotation_6;
	Quaternion m_rotation_7;
	Quaternion m_rotation_8;

	Vector3 m_difference;

	Bumper* m_bumper;
	Player* m_player;

	bool m_isReady = false;
	bool m_isRockOn = false;

	float m_rockOnSize_1 = 1.0f;
	float m_rockOnSize_2 = 1.0f;
	float m_rockOnSize_3 = 1.0f;
	float m_rockOnSize_4 = 1.0f;
	float m_angle = 0.0f;
};