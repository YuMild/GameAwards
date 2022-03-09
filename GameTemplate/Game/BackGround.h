#pragma once
class BackGround : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:

	//ƒ‚ƒfƒ‹
	ModelRender m_stage_Ground;
	ModelRender m_stage_Wall;
	PhysicsStaticObject m_stage_Ground_PSO;
	PhysicsStaticObject m_stage_Wall_PSO;
	BoxCollider m_boxCollider;

	RigidBody m_rigidBody;
};

