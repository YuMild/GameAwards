#pragma once

/// <summary>
/// �`���[�W�Q�[�W
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
	/// �o�[�̕\�����Ǘ�
	/// </summary>
	void Cut();

	SpriteRender m_gauge2D;
	SpriteRender m_frame2D;

	float m_charge;
};