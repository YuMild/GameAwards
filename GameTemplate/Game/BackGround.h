#pragma once
class BackGround : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:
	ModelRender m_modelRender;					//モデル
	ModelRender m_modelRender2;
	PhysicsStaticObject m_physicsStaticObject;	//静的物理オブジェクト・
	BoxCollider m_boxCollider;

	RigidBody m_rigidBody;
};

