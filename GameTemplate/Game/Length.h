#pragma once

class Goal;
/// <summary>
/// �`���[�W�Q�[�W
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
	/// �o�[�̕\�����Ǘ�
	/// </summary>
	void Cut();

	/// <summary>
	/// �X�s�[�h�\�L�̊Ǘ�
	/// </summary>
	void LengthFont();

	//�摜
	SpriteRender m_length2D;
	SpriteRender m_lengthInside2D;

	//�t�H���g
	FontRender m_fontRender;

	bool m_isPress = false;

	float m_timer = 0.0f;
	float m_charge = 0.0f;
	float m_length = 0.0f;

	Goal* m_goal;
};