#pragma once
class BackGround : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:

	//���f��
	ModelRender m_wall;
	ModelRender m_ground;
	PhysicsStaticObject m_wallPSO;	//�ÓI�����I�u�W�F�N�g�E
	PhysicsStaticObject m_groundPSO;
	BoxCollider m_boxCollider;

	RigidBody m_rigidBody;
};

