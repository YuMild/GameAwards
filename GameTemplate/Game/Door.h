#pragma once

#include <physics/PhysicsGhostObject.h>

class Player;
class RockOn;

class Door : public IGameObject
{
public:

	Door();
	~Door();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
	/// <summary>
	/// �T�C�Y��ݒ�B
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	/// <param name="rotation">��]�B</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

private:

	/// <summary>
	/// �����蔻��̊Ǘ��B
	/// </summary>
	void Hit();

	enum EnAnimationClip {
		enAnimationClip_Open,
		enAnimationClip_Num
	};

	ModelRender						m_modelRender;
	AnimationClip					m_open[enAnimationClip_Num];
	PhysicsGhostObject				m_ghostCollider;

	Vector3							m_position;
	Vector3							m_scale;
	Quaternion						m_rotation;

	Player*							m_player;
	RockOn*							m_rockOn;

	int								m_state = 0;
	bool							m_isHit = false;
	float							m_coolTime = 0.0f;

};