#pragma once

/// <summary>
/// İ’è‰æ–Ê
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
	/// ‘I‘ğ‚ÌŠÇ—B
	/// </summary>
	void Choice();

	int				m_choiceState = 0;
};