#pragma once

/// <summary>
/// �v���C���[
/// </summary>
class Player : public IGameObject
{
public:
    bool Start() override;
    void Render(RenderContext& rc)override;
    void Update() override;

    /// <summary>
    /// ���W��ݒ�
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(Vector3& position)
    {
        m_position = position;
    }

    /// <summary>
    /// ���W���擾
    /// </summary>
    /// <returns></returns>
    Vector3 GetPosition() const
    {
        return m_position;
    }

private:
    ModelRender m_modelRender;
    //�ȉ�2�̃N���X���g�p����B
    SphereCollider m_sphereCollider;            //�~�^�̃R���C�_�[�B
    RigidBody m_rigidBody;                        //���́B
    Vector3 m_position;

    bool m_isPress = false;
    float m_gauge = 0.0f;
    float m_gaugeOld = 0.0f;
};