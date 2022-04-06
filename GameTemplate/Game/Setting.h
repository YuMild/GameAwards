#pragma once

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

	int				m_choiceState = 0;
};