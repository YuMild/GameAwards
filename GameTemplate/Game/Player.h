#pragma once

class Player : public IGameObject
{
public:
    bool Start() override;
    void Render(RenderContext& rc)override;
    void Update() override;

private:
    ModelRender m_modelRender;
    //�ȉ�2�̃N���X���g�p����B
    SphereCollider m_sphereCollider;            //�~�^�̃R���C�_�[�B
    RigidBody m_rigidBody;                        //���́B
    Vector3 m_position;

    bool m_isPress = false;
    float m_gauge = GAUGE_DEFAULT;
    float m_gaugeOld = 0.0f;
};