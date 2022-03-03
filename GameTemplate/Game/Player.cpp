#include "stdafx.h"
#include "Player.h"

namespace
{
    float SPEED_DEFAULT = 1000000.0f;
    float CHARGE_DEFAULT = 0.0f;
}

bool Player::Start()
{
    m_position.y = 100.0f;
    //���`�̃��f����ǂݍ��ށB
    m_modelRender.Init("Assets/modelData/Ball.tkm");
    m_modelRender.SetScale(Vector3::One * 1.0f);
    m_modelRender.SetPosition(m_position);

    //�R���C�_�[���������B
    m_sphereCollider.Create(10.0f);

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
    rbInitData.restitution = 0.0f;
    //���̂��������B
    m_rigidBody.Init(rbInitData);
    //���C�͂�ݒ肷��B0�`10�܂ŁB
    m_rigidBody.SetFriction(3.0f);
    //���`�ړ�����v�f��ݒ肷��B
    //0���w�肵�����͈ړ����Ȃ��B
    //�Ⴆ��y��0�Ɏw�肷��ƁAy���W�͈ړ����Ȃ��Ȃ�B
    m_rigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);
    return true;
}
void Player::Update()
{
    Move();
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

    if (g_pad[0]->IsPress(enButtonB))
    {
        m_isPress = true;
        m_charge += 5.0f;
    }
    else if (m_isPress == true)
    {
        m_isPress = false;
        m_rigidBody.SetLinearVelocity({ 0.0f,0.0f,0.0f });
        m_moveSpeed = (forward * SPEED_DEFAULT) * m_charge / 100;   //�O��
        m_charge = CHARGE_DEFAULT;
    }

    m_moveSpeed.y = -10000.0f;

    //�͂�������B
    //�͂������邱�Ƃɂ��A���̂������B
    m_rigidBody.AddForce(
        m_moveSpeed,        //��
        g_vec3Zero          //�͂������鍄�̂̑��Έʒu
    );

    if (m_rigidBody.GetLinearVelocity().Length() >= 1000.0f)
    {
        m_rigidBody.SetLinearVelocity(g_camera3D->GetForward() * 1000.0f);
    }

    m_moveSpeed.x = 0.0f;               //�X�s�[�h�̏�����
    m_moveSpeed.z = 0.0f;
}