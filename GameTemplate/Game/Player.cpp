#include "stdafx.h"

#include "Player.h"

#include <stdio.h>
#include <math.h>

namespace
{
    float GAUGE_DEFAULT = 1.0f;
}

bool Player::Start()
{
    m_position.y = 250.0f;
    //���`�̃��f����ǂݍ��ށB
    m_modelRender.Init("Assets/modelData/Ball.tkm");
    m_modelRender.SetScale(Vector3::One * 0.1f);
    m_modelRender.SetPosition(m_position);

    //�R���C�_�[���������B
    m_sphereCollider.Create(30.0f);

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
    rbInitData.restitution = 0.8f;
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
    if (g_pad[0]->IsPress(enButtonA))
    {
        m_isPress = true;
        m_gauge * 2;
    }
    else if (m_isPress = true)
    {
        m_isPress = false;
        m_gaugeOld = m_gauge;
        m_gauge = GAUGE_DEFAULT;
    }
 
    Vector3 pos;
    Quaternion rot;
    //���̂̍��W�Ɖ�]���擾�B
    m_rigidBody.GetPositionAndRotation(pos, rot);
    //���̂̍��W�Ɖ�]�����f���ɔ��f�B
    m_modelRender.SetPosition(pos);
    m_modelRender.SetRotation(rot);
    //���̂ɗ͂�������B
    Vector3 force;
    force.y = -10000.0f;
    //���X�e�B�b�N�œ������B
    force.x = g_pad[0]->GetLStickXF() * 50000.0f;
    force.z = g_pad[0]->GetLStickYF() * 50000.0f;
   
    //�͂�������B
    //�͂������邱�Ƃɂ��A���̂������B
    m_rigidBody.AddForce(
        force,        //��
        g_vec3Zero    //�͂������鍄�̂̑��Έʒu
    );

    //���f���̍X�V�����B
    m_modelRender.Update();

    //�J�����̏����B
    Vector3 toCamere = g_camera3D->GetPosition() - g_camera3D->GetTarget();
    g_camera3D->SetTarget(pos);
    toCamere.y = 100.0f;
    g_camera3D->SetPosition(pos + toCamere);
}
void Player::Render(RenderContext& rc)
{
    //���f���̕`��B
    m_modelRender.Draw(rc);
}
