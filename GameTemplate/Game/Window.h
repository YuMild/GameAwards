#pragma once

class Player;

/// <summary>
/// �Q�[����ʂ̐����C��
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

};