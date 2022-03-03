#pragma once
class BackGround : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:

	//モデル
	ModelRender m_wall;
	ModelRender m_ground;
	PhysicsStaticObject m_wallPSO;	//静的物理オブジェクト・
	PhysicsStaticObject m_groundPSO;
	BoxCollider m_boxCollider;

	RigidBody m_rigidBody;
};

