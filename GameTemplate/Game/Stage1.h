#pragma once

class Stage1 : public IGameObject
{
public:

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	Vector3 GetBumperPosition() const
	{
		return m_stage_Bumpers.GetPosition();
	}

private:

	//���f��
	ModelRender m_stage_Ground;					//�n��
	ModelRender m_stage_Wall;					//��
	ModelRender m_stage_Bumpers;				//�o���p�[

	//PhysicsStaticObject
	PhysicsStaticObject m_stage_Ground_PSO;
	PhysicsStaticObject m_stage_Wall_PSO;
	PhysicsStaticObject m_stage_Bumpers_PSO;
	BoxCollider m_boxCollider;
};

