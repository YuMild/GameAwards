#pragma once

#include <RockOnObject.h>
#include <physics/PhysicsGhostObject.h>

class Player;
class RockOn;

class Turret : public RockOnObject
{
public:

	Turret();
	~Turret();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// 座標を設定。
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const override
	{
		return m_position;
	}
	/// <summary>
	/// サイズを設定。
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// 回転を設定。
	/// </summary>
	/// <param name="rotation">回転。</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	///	ステートを取得。
	/// </summary>
	/// <returns></returns>
	int GetState() const override
	{
		return m_state;
	}


private:

	/// <summary>
	/// 当たり判定の管理。
	/// </summary>
	void Hit();

	ModelRender						m_modelRender;
	CharacterController				m_boxCollider;
	PhysicsGhostObject				m_ghostCollider;
	PhysicsGhostObject				m_beamCollider;

	Vector3							m_position;
	Vector3							m_scale;
	Vector3							m_direction;
	Quaternion						m_rotation;
	Quaternion						m_beamRotation;

	Player* m_player;
	RockOn* m_rockOn;

	int								m_state = 0;
	bool							m_isHit = false;
	float							m_aliveTime = 0.0f;
};