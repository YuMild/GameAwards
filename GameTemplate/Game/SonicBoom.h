#pragma once

class Player;

/// <summary>
/// ソニックブーム
/// </summary>
class SonicBoom : public IGameObject
{
public:

	SonicBoom();
	~SonicBoom();
	bool Start();
	void Update();

private:

	Vector3 m_position;
	EffectEmitter* m_sonicBoom;
	Player* m_player;

	float m_aliveTimer = 0.0f;
};