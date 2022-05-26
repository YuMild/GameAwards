#pragma once

class Player;

/// <summary>
/// ƒQ[ƒ€‰æ–Ê‚ÌÂ‚¢ƒ‰ƒCƒ“
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