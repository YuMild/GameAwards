#pragma once

class Player;
class RockOn;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

private:

	Vector3			m_position;
	Vector3			m_target;
	Vector3			m_toCameraPos = Vector3::One;

	Player*			m_player;
	RockOn*			m_rockOn;

	bool			m_isRockOnJudge = false;
	float			m_rotationX = 0.0f;
	float			m_rotationY = 0.0f;
};