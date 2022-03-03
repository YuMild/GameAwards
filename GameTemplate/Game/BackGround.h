#pragma once
class BackGround : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:

	//ƒ‚ƒfƒ‹
	ModelRender m_stage;
	PhysicsStaticObject m_stagePSO;
	BoxCollider m_boxCollider;

	RigidBody m_rigidBody;
};

