#pragma once

/// <summary>
/// �`���[�W�Q�[�W
/// </summary>
class Window : public IGameObject
{
public:

	Window();
	~Window();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	//�摜
	SpriteRender m_window2D;
};