#include "stdafx.h"

#include "Player.h"

#include <stdio.h>
#include <math.h>

namespace
{
    float GAUGE_DEFAULT = 1.0f;
    float SPEED_DEFAULT = 1000000.0f;
}

bool Player::Start()
{
    m_position.y = 1000.0f;
    //���`�̃��f����ǂݍ��ށB
    m_modelRender.Init("Assets/modelData/Ball.tkm");
    m_modelRender.SetScale(Vector3::One * 0.1f);
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
    rbInitData.restitution = 1.5f;
    //���̂��������B
    m_rigidBody.Init(rbInitData);
    //���C�͂�ݒ肷��B0�`10�܂ŁB
    m_rigidBody.SetFriction(10.0f);
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

void Player::Move()
{
 

    //���̂̍��W�Ɖ�]���擾�B
    m_rigidBody.GetPositionAndRotation(m_position, m_rotation);
    //���̂̍��W�Ɖ�]�����f���ɔ��f�B
    m_modelRender.SetPosition(m_position);
    m_modelRender.SetRotation(m_rotation);

    float lStickX = g_pad[0]->GetLStickXF();
    float lStickY = g_pad[0]->GetLStickYF();

    Vector3 moveSpeed;

    if (g_pad[0]->IsTrigger(enButtonB))
    {
        moveSpeed += g_camera3D->GetForward() * SPEED_DEFAULT;   //�O��
    }
   
    //�d��
    moveSpeed.y = -50000.0f;

    //�͂�������B
    //�͂������邱�Ƃɂ��A���̂������B
    m_rigidBody.AddForce(
        moveSpeed,          //��
        g_vec3Zero          //�͂������鍄�̂̑��Έʒu
    );
}

void Player::Render(RenderContext& rc)
{
    //���f���̕`��B
    m_modelRender.Draw(rc);
}
