#pragma once

/// <summary>
/// �`���[�W�Q�[�W
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
	/// �o�[�̕\�����Ǘ�
	/// </summary>
	void Cut();
	/// <summary>
	/// �`���[�W�̏�Ԃ��Ǘ�
	/// </summary>
	void Charge();

	SpriteRender m_gauge2D;
	SpriteRender m_frame2D;

	bool m_isPress = false;

	float m_timer = 0.0f;
	float m_charge = 0.0f;
	float m_chargeOld = 0.0f;
};