#pragma once

class Title;

/// <summary>
/// �ݒ���
/// </summary>
class Setting : public IGameObject
{
public:

	Setting();
	~Setting();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// �I���̊Ǘ��B
	/// </summary>
	void Choice();

	/// <summary>
	/// �摜���Ǘ��B
	/// </summary>
	void Sprite();

	SoundSource*	m_choiceSE;

	SpriteRender	m_apply;
	SpriteRender	m_backGround;
	SpriteRender	m_cancel;
	SpriteRender	m_controll;
	SpriteRender	m_sound;
	SpriteRender	m_stickSensitivity;
	SpriteRender	m_vibration;

	Title*			m_title;

	int				m_shelf = 0;
	int				m_choiceState = 0;
};