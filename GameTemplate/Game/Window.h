#pragma once

/// <summary>
/// チャージゲージ
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

	//画像
	SpriteRender m_window2D;
};