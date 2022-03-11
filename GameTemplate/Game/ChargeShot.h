#pragma once

class Player;
/// <summary>
/// チャージゲージ
/// </summary>
class ChargeShot: public IGameObject
{
public:

	ChargeShot();
	~ChargeShot();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// バーの表示を管理
	/// </summary>
	void Cut();

	//画像
	SpriteRender m_charge2D;
	SpriteRender m_chargeInside2D;

	//フォント

	bool m_isPress = false;

	float m_timer = 0.0f;
	float m_charge = 0.0f;

	Player* m_player;
};