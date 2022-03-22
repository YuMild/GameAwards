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

    FontRender m_fontRender;                //�t�H���g�����_�[
    SpriteRender m_gaugeRender;             //�摜
    ModelRender m_modelRender;              //���f�������_�[
    SphereCollider m_sphereCollider;        //�~�^�̃R���C�_�[
    RigidBody m_rigidBody;                  //����

    Vector3 m_position;                     //�|�W�V����
    Vector3 m_scale;                        //�T�C�Y
    Vector3 m_cameraForward;                //�J�����̑O����
    Vector3 m_cameraRight;                  //�J�����̍��E����
    Vector3 m_moveSpeed;                    //�v���C���[�̈ړ����x

    Quaternion m_rotation;                  //��]

    bool m_isPress = false;                 //�{�^����������Ă��邩�ۂ��̔���
    float m_charge = 0.0f;                  //�`���[�W
};