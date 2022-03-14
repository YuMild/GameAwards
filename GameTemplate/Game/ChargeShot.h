#pragma once

#include <FontRender.h>

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
	
	/// <summary>
	/// スピード表記の管理
	/// </summary>
	void Speed();

	//画像
	SpriteRender m_charge2D;
	SpriteRender m_chargeInside2D;

	//フォント
	FontRender m_fontRender;

	bool m_isPress = false;

	float m_timer = 0.0f;
	float m_charge = 0.0f;
	float m_speed = 0.0f;

	Player* m_player;
};