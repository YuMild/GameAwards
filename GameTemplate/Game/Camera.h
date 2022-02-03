#pragma once
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();

private:

	Vector3 m_position;
	Vector3 m_target;
	Vector3 m_toCameraPos = Vector3::One;
};