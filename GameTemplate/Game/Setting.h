#pragma once

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

	int				m_choiceState = 0;
};