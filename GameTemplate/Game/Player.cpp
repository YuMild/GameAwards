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
    //球形のモデルを読み込む。
    m_modelRender.Init("Assets/modelData/Ball.tkm");
    m_modelRender.SetScale(Vector3::One * 1.0f);
    m_modelRender.SetPosition(m_position);

    //コライダーを初期化。
    m_sphereCollider.Create(10.0f);

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
    rbInitData.restitution = 0.0f;
    //剛体を初期化。
    m_rigidBody.Init(rbInitData);
    //摩擦力を設定する。0～10まで。
    m_rigidBody.SetFriction(3.0f);
    //線形移動する要素を設定する。
    //0を指定した軸は移動しない。
    //例えばyを0に指定すると、y座標は移動しなくなる。
    m_rigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);
    return true;
}
void Player::Update()
{
    Move();
    //モデルの更新処理。
    m_modelRender.Update();
}

void Player::Render(RenderContext& rc)
{
    //モデルの描画。
    m_modelRender.Draw(rc);
}

void Player::Move()
{
    //剛体の座標と回転を取得。
    m_rigidBody.GetPositionAndRotation(m_position, m_rotation);
    //剛体の座標と回転をモデルに反映。
    m_modelRender.SetPosition(m_position);
    m_modelRender.SetRotation(m_rotation);

    //剛体に力を加える。
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
        m_moveSpeed = (forward * SPEED_DEFAULT) * m_charge / 100;   //前後
        m_charge = CHARGE_DEFAULT;
    }

    m_moveSpeed.y = -10000.0f;

    //力を加える。
    //力を加えることにより、剛体が動く。
    m_rigidBody.AddForce(
        m_moveSpeed,        //力
        g_vec3Zero          //力を加える剛体の相対位置
    );

    if (m_rigidBody.GetLinearVelocity().Length() >= 1000.0f)
    {
        m_rigidBody.SetLinearVelocity(g_camera3D->GetForward() * 1000.0f);
    }

    m_moveSpeed.x = 0.0f;               //スピードの初期化
    m_moveSpeed.z = 0.0f;
}