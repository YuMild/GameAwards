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
    //球形のモデルを読み込む。
    m_modelRender.Init("Assets/modelData/Ball.tkm");
    m_modelRender.SetScale(Vector3::One * 0.1f);
    m_modelRender.SetPosition(m_position);

    //コライダーを初期化。
    m_sphereCollider.Create(30.0f);

    //剛体を初期化。
    RigidBodyInitData rbInitData;
    //質量(重さ)を設定する。
    rbInitData.mass = 30.0f;
    //コライダーを設定する。
    rbInitData.collider = &m_sphereCollider;
    //座標を設定する。
    rbInitData.pos = m_position;
    //回転のしやすさを設定する。0～1
    rbInitData.localInteria.Set(
        0.5f,
        0.5f,
        0.5f
    );
    //反発力を設定する。
    //数値を大きくすると、跳ね返りが大きくなる。
    //PhysicsStaticObjectにも反発力を設定する必要がある(Game.cpp参照)。
    rbInitData.restitution = 0.8f;
    //剛体を初期化。
    m_rigidBody.Init(rbInitData);
    //摩擦力を設定する。0～10まで。
    m_rigidBody.SetFriction(10.0f);
    //線形移動する要素を設定する。
    //0を指定した軸は移動しない。
    //例えばyを0に指定すると、y座標は移動しなくなる。
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
    //剛体の座標と回転を取得。
    m_rigidBody.GetPositionAndRotation(pos, rot);
    //剛体の座標と回転をモデルに反映。
    m_modelRender.SetPosition(pos);
    m_modelRender.SetRotation(rot);
    //剛体に力を加える。
    Vector3 force;
    force.y = -10000.0f;
    //左スティックで動かす。
    force.x = g_pad[0]->GetLStickXF() * 50000.0f;
    force.z = g_pad[0]->GetLStickYF() * 50000.0f;
   
    //力を加える。
    //力を加えることにより、剛体が動く。
    m_rigidBody.AddForce(
        force,        //力
        g_vec3Zero    //力を加える剛体の相対位置
    );

    //モデルの更新処理。
    m_modelRender.Update();

    //カメラの処理。
    Vector3 toCamere = g_camera3D->GetPosition() - g_camera3D->GetTarget();
    g_camera3D->SetTarget(pos);
    toCamere.y = 100.0f;
    g_camera3D->SetPosition(pos + toCamere);
}
void Player::Render(RenderContext& rc)
{
    //モデルの描画。
    m_modelRender.Draw(rc);
}
