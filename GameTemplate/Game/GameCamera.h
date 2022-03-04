#pragma once

#include <SpringCamera.h>

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

private:

	SpringCamera m_springCamera;

	Vector3 m_position;
	Vector3 m_target;
	Vector3 m_toCameraPos = Vector3::One;

	Player* m_player;
};