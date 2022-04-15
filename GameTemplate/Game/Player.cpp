#include "stdafx.h"
#include "Player.h"

#include "Game.h"
#include "PowerCharge.h"
#include "RockOn.h"
#include "SonicBoom.h"

namespace
{
    //�v���C���[
    Vector3 PLAYER_FIRST_POSITION = { 0.0f,100.0f,0.0f };       //�X�|�[�����W
    float PLAYER_MODEL_SCALE = 1.0f;                            //�T�C�Y
    float PLAYER_COLLISION_SCALE = 10.0f;                       //�����蔻��̃T�C�Y
    float PLAYER_GRAVITY = -50000.0f;                           //�d��
    float PLAYER_ROLL = 1.0f;                                   //�]����₷��
    float PLAYER_FRICTION = 1.0f;                               //���C��
    float PLAYER_SPEED_DECREASE = 0.997;                        //�X�s�[�h�̌�����
    float PLAYER_SPEED_DEFAULT = 25000000.0f;                   //�X�s�[�h�f�t�H���g
    float PLAYER_SPEED_MAX = 5000.0f;                           //�X�s�[�h����l

    //�`���[�W
    float CHARGE_DEFAULT = 0.0f;                                //�`���[�W���Z�b�g�l
    float CHARGE_ADD = 0.05f;                                   //1f���Ƀ`���[�W�����l
}

bool Player::Start()
{
    m_position = PLAYER_FIRST_POSITION;
    //���`�̃��f����ǂݍ��ށB
    m_modelRender.Init("Assets/modelData/Stage_0/Player.tkm");
    m_modelRender.SetScale(Vector3::One * PLAYER_MODEL_SCALE);
    m_modelRender.SetPosition(m_position);

    EffectEngine::GetInstance()->ResistEffect(2, u"Assets/Effect/Selfmade/PowerCharge.efk");
    m_reSpawn = NewGO<EffectEmitter>(2);
    m_reSpawn->Init(2);
    m_reSpawn->SetScale(Vector3::One * 2.0f);
    m_reSpawn->SetPosition({ m_position.x,m_position.y += 10.0f,m_position.z });
    m_reSpawn->Play();

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

    m_game = FindGO<Game>("game");
    m_rockOn = FindGO<RockOn>("rockOn");

    return true;
}

void Player::Update()
{
    Death();
    Move();
    //���f���̍X�V�����B
    m_modelRender.Update();

    //�f�o�b�O�p
    wchar_t x[256];
    swprintf_s(x, 256, L"X=%f", m_position.x);
    m_fontRenderX.SetText(x);
    m_fontRenderX.SetPosition({ 500.0f, 300.0f, 0.0f });
    wchar_t y[256];
    swprintf_s(y, 256, L"Y=%f", m_position.y);
    m_fontRenderY.SetText(y);
    m_fontRenderY.SetPosition({ 500.0f, 250.0f, 0.0f });
    wchar_t z[256];
    swprintf_s(z, 256, L"Z=%f", m_position.z);
    m_fontRenderZ.SetText(z);
    m_fontRenderZ.SetPosition({ 500.0f, 200.0f, 0.0f });
}

void Player::Render(RenderContext& rc)
{
    //���f���̕`��B
    m_modelRender.Draw(rc);

    m_fontRenderX.Draw(rc);
    m_fontRenderY.Draw(rc);
    m_fontRenderZ.Draw(rc);
}

void Player::Death()
{
    if (m_position.y <= -100 || g_pad[0]->IsTrigger(enButtonStart))
    {
        m_game->SetGemeEnd(1);
    }
}

void Player::Move()
{
    if (m_scale <= 1.0f)
    {
        m_scale += 0.1;
    }
    m_modelRender.SetScale(Vector3::One * m_scale);

    //���̂̍��W�Ɖ�]���擾�B
    m_rigidBody.GetPositionAndRotation(m_position, m_rotation);
    //���̂̍��W�Ɖ�]�����f���ɔ��f�B
    m_modelRender.SetPosition(m_position);
    m_modelRender.SetRotation(m_rotation);

    //�v���C���[���i�ޕ��������肷��B
    
    Vector3 forward = g_camera3D->GetForward();                                 //�J�����̑O����
    forward.y = 0.0f;
    forward.Normalize();
    
    Vector3 target = m_rockOn->GetDifference();                                 //���b�N�I�����Ă���I�u�W�F�N�g�̕���

    m_moveSpeed.y = PLAYER_GRAVITY;

    if (g_pad[0]->IsPress(enButtonLB2))                                         //�{�^���������Ă��鎞
    {
        m_isPress = true;
        if (m_charge < 1.0f)
        {
            m_charge += CHARGE_ADD;
        }
    }
    else if (m_isPress == true && m_rockOn->GetRockOnJudge() == false)          //�{�^����������Ċ����b�N�I�����I�t�̎�
    {
        m_isPress = false;
        m_rigidBody.SetLinearVelocity({ 0.0f,0.0f,0.0f });                      //�X�s�[�h��������
        m_moveSpeed = (forward * PLAYER_SPEED_DEFAULT) * m_charge;              //�O��
        m_charge = CHARGE_DEFAULT;
    }
    else if (m_isPress == true && m_rockOn->GetRockOnJudge() == true)           //�{�^����������Ċ����b�N�I�����I���̎�
    {
        if (m_isPowerCharge == true)
        {
            m_powerCharge = NewGO<PowerCharge>(0, "powerCharge");
        }
        m_isPowerCharge = false;
        m_delay += 0.1;
        m_rigidBody.SetLinearVelocity({ 0.0f,0.0f,0.0f });                      //�X�s�[�h��������
        if (m_delay > 2.0f)
        {
            m_isRockOnFire = true;
            m_isPress = false;
            m_isPowerCharge = true;
            m_sonicBoom = NewGO<SonicBoom>(0, "sonicBoom");
            m_moveSpeed = (target * PLAYER_SPEED_DEFAULT) * (m_charge * 2.0f);  //�O��
            m_charge = CHARGE_DEFAULT;
            m_delay = 0.0f;
        }
    }

    if (m_isRockOnFire == false)                                                //���b�N�I�����ĂȂ���
    {
        m_moveSpeed.y = PLAYER_GRAVITY;                                         //�d�͂��|����
    }

    m_rigidBody.AddForce
    (
        m_moveSpeed,                                                            //��
        g_vec3Zero                                                              //�͂������鍄�̂̑��Έʒu
    );

    //�X�s�[�h�̏����ݒ�B
    if (m_isRockOnFire == false && m_rigidBody.GetLinearVelocity().Length() >= PLAYER_SPEED_MAX)
    {
        m_rigidBody.SetLinearVelocity(g_camera3D->GetForward() * PLAYER_SPEED_MAX);
    }

    //�X�s�[�h�����X�Ɍ���������B
    if (m_rigidBody.GetLinearXZVelocity().Length() >= 0)
    {
        m_rigidBody.SetLinearVelocity(m_rigidBody.GetLinearVelocity() * pow(PLAYER_SPEED_DECREASE, 2));
    }

    m_moveSpeed.x = 0.0f;                                                       //�X�s�[�h�̏�����
    m_moveSpeed.y = 0.0f;                                                       //�X�s�[�h�̏�����
    m_moveSpeed.z = 0.0f;                                                       //�X�s�[�h�̏�����
}