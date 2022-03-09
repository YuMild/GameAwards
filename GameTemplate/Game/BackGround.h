#pragma once
class BackGround : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
private:

	//モデル
	ModelRender m_stage_Ground;					//地面
	ModelRender m_stage_Wall;					//壁
	ModelRender m_stage_Bumpers;				//バンパー

	//PhysicsStaticObject
	PhysicsStaticObject m_stage_Ground_PSO;
	PhysicsStaticObject m_stage_Wall_PSO;
	PhysicsStaticObject m_stage_Bumpers_PSO;
	BoxCollider m_boxCollider;

	RigidBody m_rigidBody;
};

