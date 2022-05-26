#pragma once

class Goal;
/// <summary>
/// チャージゲージ
/// </summary>
class Length : public IGameObject
{
public:

	Length();
	~Length();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// バーの表示を管理
	/// </summary>
	void Cut();

	/// <summary>
	/// スピード表記の管理
	/// </summary>
	void LengthFont();

	//画像
	SpriteRender m_length2D;
	SpriteRender m_lengthInside2D;

	//フォント
	FontRender m_fontRender;

	bool m_isPress = false;

	float m_timer = 0.0f;
	float m_charge = 0.0f;
	float m_length = 0.0f;

	Goal* m_goal;
};