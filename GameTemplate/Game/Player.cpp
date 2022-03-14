#include "stdafx.h"
#include "Player.h"

namespace
{
    //プレイヤー
    Vector3 PLAYER_FIRST_POSITION = { 0.0f,100.0f,0.0f };       //スポーン座標
    float PLAYER_MODEL_SCALE = 1.0f;                            //サイズ
    float PLAYER_COLLISION_SCALE = 10.0f;                       //当たり判定のサイズ
    float PLAYER_GRAVITY = 30.0f;                               //重力
    float PLAYER_ROLL = 0.5f;                                   //転がりやすさ
    float PLAYER_FRICTION = 10.0f;                              //摩擦力
    float PLAYER_SPEED_DEFAULT = 900000.0f;                    //スピードデフォルト
    float PLAYER_SPEED_MAX = 1000.0f;                           //スピード上限値

    //チャージ
    float CHARGE_DEFAULT = 0.0f;                                //チャージリセット値
    float CHARGE_ADD = 0.05f;                                   //1f毎にチャージされる値
}

bool Player::Start()
{
    m_position = PLAYER_FIRST_POSITION;
    //球形のモデルを読み込む。
    m_modelRender.Init("Assets/modelData/Stage1/Ball.tkm");
    m_modelRender.SetScale(Vector3::One * PLAYER_MODEL_SCALE);
    m_modelRender.SetPosition(m_position);

    //コライダーを初期化。
    m_sphereCollider.Create(PLAYER_COLLISION_SCALE);

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
    rbInitData.restitution = 1.0f;
    //剛体を初期化。
    m_rigidBody.Init(rbInitData);
    //摩擦力を設定する。0～10まで。
    m_rigidBody.SetFriction(PLAYER_FRICTION);
    //線形移動する要素を設定する。
    //0を指定した軸は移動しない。
    //例えばyを0に指定すると、y座標は移動しなくなる。
    m_rigidBody.SetLinearFactor(1.0f, 1.0f, 1.0f);
    return true;
}
void Player::Update()
{
    Move();
    Death();
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
        m_moveSpeed = (forward * PLAYER_SPEED_DEFAULT) * m_charge;   //前後
        m_charge = CHARGE_DEFAULT;
    }

    m_moveSpeed.y = -10000.0f;

    //力を加える。
    //力を加えることにより、剛体が動く。
    m_rigidBody.AddForce(
        m_moveSpeed,        //力
        g_vec3Zero          //力を加える剛体の相対位置
    );

    if (m_rigidBody.GetLinearXZVelocity().Length() >= PLAYER_SPEED_MAX)
    {
        m_rigidBody.SetLinearVelocity(g_camera3D->GetForward() * PLAYER_SPEED_MAX);
    }

    m_moveSpeed.x = 0.0f;               //スピードの初期化
    m_moveSpeed.z = 0.0f;
}

void Player::Death()
{
}