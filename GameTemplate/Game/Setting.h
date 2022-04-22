#pragma once

class First;
class Title;

/// <summary>
/// 設定画面
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
	/// 選択の管理。
	/// </summary>
	void Choice();

	/// <summary>
	/// 画像を管理。
	/// </summary>
	void Sprite();

	SoundSource*	m_choiceSE;

	SpriteRender	m_apply;
	SpriteRender	m_applyChoice;
	SpriteRender	m_backGround;
	SpriteRender	m_cancel;
	SpriteRender	m_cancelChoice;
	SpriteRender	m_controll;
	SpriteRender	m_controllChoice;
	SpriteRender	m_sound;
	SpriteRender	m_soundChoice;
	SpriteRender	m_stickSensitivity;
	SpriteRender	m_stickSensitivityChoice;
	SpriteRender	m_stickSensitivityBar;
	SpriteRender	m_stickSensitivityBarChoice;
	SpriteRender	m_vibration;
	SpriteRender	m_vibrationChoice;

	First*			m_first;
	Title*			m_title;

	int				m_shelf = 0;
	int				m_choiceState = 0;
};