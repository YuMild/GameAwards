#include "stdafx.h"
#include "Player.h"

namespace
{
    //�v���C���[
    Vector3 PLAYER_FIRST_POSITION = { 0.0f,100.0f,0.0f };       //�X�|�[�����W
    float PLAYER_MODEL_SCALE = 1.0f;                            //�T�C�Y
    float PLAYER_COLLISION_SCALE = 10.0f;                       //�����蔻��̃T�C�Y
    float PLAYER_GRAVITY = 30.0f;                               //�d��
    float PLAYER_ROLL = 0.5f;                                   //�]����₷��
    float PLAYER_FRICTION = 10.0f;                              //���C��
    float PLAYER_SPEED_DEFAULT = 900000.0f;                    //�X�s�[�h�f�t�H���g
    float PLAYER_SPEED_MAX = 1000.0f;                           //�X�s�[�h����l

    //�`���[�W
    float CHARGE_DEFAULT = 0.0f;                                //�`���[�W���Z�b�g�l
    float CHARGE_ADD = 0.05f;                                   //1f���Ƀ`���[�W�����l
}

bool Player::Start()
{
    m_position = PLAYER_FIRST_POSITION;
    //���`�̃��f����ǂݍ��ށB
    m_modelRender.Init("Assets/modelData/Stage1/Ball.tkm");
    m_modelRender.SetScale(Vector3::One * PLAYER_MODEL_SCALE);
    m_modelRender.SetPosition(m_position);

    //�R���C�_�[���������B
    m_sphereCollider.Create(PLAYER_COLLISION_SCALE);

    //���̂��������B
    RigidBodyInitData rbInitData;
    //����(�d��)��ݒ肷��B
    rbInitData.mass = 30.0f;
    //�R���C�_�[��ݒ肷��B
    rbInitData.collider = &m_sphereCollider;
    //���W��ݒ肷��B
    rbInitData.pos = m_position;
    //��]�̂��₷����ݒ肷��B0�`1
    rbInitData.localInteria.Set(
        0.5f,
        0.5f,
        0.5f
    );
    //�����͂�ݒ肷��B
    //���l��傫������ƁA���˕Ԃ肪�傫���Ȃ�B
    //PhysicsStaticObject�ɂ������͂�ݒ肷��K�v������(Game.cpp�Q��)�B
    rbInitData.restitution = 1.0f;
    //���̂��������B
    m_rigidBody.Init(rbInitData);
    //���C�͂�ݒ肷��B0�`10�܂ŁB
    m_rigidBody.SetFriction(PLAYER_FRICTION);
    //���`�ړ�����v�f��ݒ肷��B
    //0���w�肵�����͈ړ����Ȃ��B
    //�Ⴆ��y��0�Ɏw�肷��ƁAy���W�͈ړ����Ȃ��Ȃ�B
    m_rigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);
    return true;
}
void Player::Update()
{
    Move();
    Death();
    //���f���̍X�V�����B
    m_modelRender.Update();
}

void Player::Render(RenderContext& rc)
{
    //���f���̕`��B
    m_modelRender.Draw(rc);
}

void Player::Move()
{
    //���̂̍��W�Ɖ�]���擾�B
    m_rigidBody.GetPositionAndRotation(m_position, m_rotation);
    //���̂̍��W�Ɖ�]�����f���ɔ��f�B
    m_modelRender.SetPosition(m_position);
    m_modelRender.SetRotation(m_rotation);

    //���̂ɗ͂�������B
    Vector3 force;
    Vector3 forward = g_camera3D->GetForward();
    forward.y = 0.0f;
    forward.Normalize();

    if (g_pad[0]->IsPress(enButtonLB2))
    {
        //g_k2EngineLow->SetFrameRateMode(K2EngineLow::EnFrameRateMode::enFrameRateMode_Variable, 30.0f);
        m_isPress = true;
        m_charge += CHARGE_ADD;
    }
    else if (m_isPress == true)
    {
        g_k2EngineLow->SetFrameRateMode(K2EngineLow::EnFrameRateMode::enFrameRateMode_Variable, 60.0f);
        m_isPress = false;
        m_rigidBody.SetLinearVelocity({ 0.0f,0.0f,0.0f });
        m_moveSpeed = (forward * PLAYER_SPEED_DEFAULT) * m_charge;   //�O��
        m_charge = CHARGE_DEFAULT;
    }

    m_moveSpeed.y = -10000.0f;

    //�͂�������B
    //�͂������邱�Ƃɂ��A���̂������B
    m_rigidBody.AddForce(
        m_moveSpeed,        //��
        g_vec3Zero          //�͂������鍄�̂̑��Έʒu
    );

    if (m_rigidBody.GetLinearXZVelocity().Length() >= PLAYER_SPEED_MAX)
    {
        m_rigidBody.SetLinearVelocity(g_camera3D->GetForward() * PLAYER_SPEED_MAX);
    }

    m_moveSpeed.x = 0.0f;               //�X�s�[�h�̏�����
    m_moveSpeed.z = 0.0f;
}

void Player::Death()
{
}