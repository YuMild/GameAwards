#pragma once

#include <FontRender.h>

class Player;
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
	/// �X�s�[�h�\�L�̊Ǘ�
	/// </summary>
	void Speed();

	//�摜
	SpriteRender m_charge2D;
	SpriteRender m_chargeInside2D;

	//�t�H���g
	FontRender m_fontRender;

	bool m_isPress = false;

	float m_timer = 0.0f;
	float m_charge = 0.0f;
	float m_speed = 0.0f;

	Player* m_player;
};