#pragma once

/// <summary>
/// チャージゲージ
/// </summary>
class ChargeGauge : public IGameObject
{
public:

	ChargeGauge();
	~ChargeGauge();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// バーの表示を管理
	/// </summary>
	void Cut();

	SpriteRender m_gauge2D;
	SpriteRender m_frame2D;

	float m_charge;
};