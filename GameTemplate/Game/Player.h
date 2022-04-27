#pragma once

class Game;
class GameCamera;
class PowerCharge;
class RockOn;
class SonicBoom;

/// <summary>
/// �v���C���[
/// </summary>
class Player : public IGameObject
{
public:
    bool Start() override;
    void Render(RenderContext& rc)override;
    void Update() override;
    void UpdateOnStop() override;
    /// <summary>
    /// �X�e�[�g��ݒ�
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    int SetState(const int& state)
    {
        m_state = state;
        return m_state;
    }

    /// <summary>
    /// ���W��ݒ�
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(const Vector3& position)
    {
        m_position = position;
    }

    /// <summary>
    /// �傫����ݒ�B
    /// </summary>
    /// <param name="scale">�傫���B</param>
    void SetScale(const float& scale)
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
    /// �v���C���[�̈ړ����x��ݒ�B
    /// </summary>
    /// <param name="moveSpeed"></param>
    void SetMoveSpeed(const Vector3& moveSpeed)
    {
        m_moveSpeed = moveSpeed;
    }

    /// <summary>
    /// ���b�N�I�����ɔ��˂��ꂽ���ۂ��B
    /// </summary>
    /// <param name="judge"></param>
    void SetIsRockOnFire(const bool& judge)
    {
        m_isRockOnFire = judge;
    }

    /// <summary>
    /// ���X�|�[���n�_��ݒ�B
    /// </summary>
    /// <param name="reSpawnPosition"></param>
    void SetReSpawnPosition(Vector3& reSpawnPosition)
    {
        m_reSpawnPosition = reSpawnPosition;
    }

    int GetState() const
    {
        return m_state;
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
    /// �`���[�W�ʂ��擾�B
    /// </summary>
    /// <returns></returns>
    float GetCharge() const
    {
        return m_charge;
    }

    /// <summary>
    /// �v���C���[�̃X�s�[�h���擾
    /// </summary>
    /// <returns></returns>
    float GetPlayerSpeed() const
    {
        return m_rigidBody.GetLinearVelocity().Length();
    }

    bool GetStop() const
    {
        return m_stop;
    }

    RigidBody           m_rigidBody;                //����

private:

    /// <summary>
    /// �f�X�̔���
    /// </summary>
    void Death();

    /// <summary>
    /// ������Ǘ�
    /// </summary>
    void Move();

    EffectEmitter*      m_reSpawn;
    SoundSource*        m_sound;

    FontRender          m_fontRenderX;              //�t�H���g�����_�[
    FontRender          m_fontRenderY;              //�t�H���g�����_�[
    FontRender          m_fontRenderZ;              //�t�H���g�����_�[
    SpriteRender        m_gaugeRender;              //�摜
    ModelRender         m_modelRender;              //���f�������_�[
    SphereCollider      m_sphereCollider;           //�~�^�̃R���C�_�[

    Vector3             m_position;                 //�|�W�V����
    Vector3             m_reSpawnPosition;          //���X�|�[���|�C���g
    Vector3             m_cameraForward;            //�J�����̑O����
    Vector3             m_cameraRight;              //�J�����̍��E����
    Vector3             m_moveSpeed;                //�v���C���[�̈ړ����x

    Quaternion          m_rotation;                 //��]

    bool                m_isEffectStart = true;     //�G�t�F�N�g����񂾂��Đ�������
    bool                m_isPress = false;          //�{�^����������Ă��邩�ۂ��̔���
    bool                m_isRockOnFire = false;     //���b�N�I�����ɔ��˂��ꂽ���ۂ��̔���
    bool                m_isPowerCharge = true;     //�p���[�`���[�W�G�t�F�N�g
    bool                m_stop = false;
    int                 m_state;                    //�X�e�[�g
    float               m_scale = 0.0f;             //�T�C�Y
    float               m_charge = 0.0f;            //�`���[�W
    float               m_delay = 0.0f;             //�f�B���C
    float               m_stopTimer = 0.0f;

    Game*               m_game;
    GameCamera*         m_gameCamera;
    PowerCharge*        m_powerCharge;
    RockOn*             m_rockOn;
    SonicBoom*          m_sonicBoom;
};