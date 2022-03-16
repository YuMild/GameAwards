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

    /// <summary>
    /// �傫����ݒ�B
    /// </summary>
    /// <param name="scale">�傫���B</param>
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

    /// <summary>
    /// �v���C���[�̈ړ����x���擾
    /// </summary>
    /// <param name="moveSpeed"></param>
    void SetMoveSpeed(Vector3& moveSpeed)
    {
        m_moveSpeed = moveSpeed;
    }

    /// <summary>
    /// �`���[�W�ʂ��擾
    /// </summary>
    /// <returns></returns>
    float GetCharge() const
    {
        return m_charge;
    }

    /// <summary>
    /// �v���[���[�̃X�s�[�h���擾
    /// </summary>
    /// <returns></returns>
    float GetPlayerSpeed() const
    {
        return m_rigidBody.GetLinearVelocity().Length();
    }
private:

    /// <summary>
    /// ������Ǘ�
    /// </summary>
    void Move();

    /// <summary>
    /// ���S������Ǘ�
    /// </summary>
    void Death();

    FontRender m_fontRender;

    ModelRender m_modelRender;
    SphereCollider m_sphereCollider;        //�~�^�̃R���C�_�[
    RigidBody m_rigidBody;                  //����

    Vector3 m_position;                     //�|�W�V����
    Vector3 m_scale;
    Vector3 m_cameraForward;
    Vector3 m_cameraRight;
    Vector3 m_moveSpeed;

    Quaternion m_rotation;                  //��]

    SpriteRender m_gaugeRender;

    bool m_isPress = false;
    float m_charge = 0.0f;
    float m_timer = 0.0f;
};