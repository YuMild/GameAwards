#include "stdafx.h"
#include "Player.h"

#include "RockOn.h"

namespace
{
    //プレイヤー
    Vector3 PLAYER_FIRST_POSITION = { 0.0f,100.0f,0.0f };       //スポーン座標
    float PLAYER_MODEL_SCALE = 1.0f;                            //サイズ
    float PLAYER_COLLISION_SCALE = 10.0f;                       //当たり判定のサイズ
    float PLAYER_GRAVITY = -50000.0f;                           //重力
    float PLAYER_ROLL = 0.5f;                                   //転がりやすさ
    float PLAYER_FRICTION = 5.0f;                               //摩擦力
    float PLAYER_SPEED_DECREASE = 0.997;                        //スピードの減衰率
    float PLAYER_SPEED_DEFAULT = 25000000.0f;                   //スピードデフォルト
    float PLAYER_SPEED_MAX = 5000.0f;                           //スピード上限値

    //チャージ
    float CHARGE_DEFAULT = 0.0f;                                //チャージリセット値
    float CHARGE_ADD = 0.05f;                                   //1f毎にチャージされる値
}

bool Player::Start()
{
    m_position = PLAYER_FIRST_POSITION;
    //球形のモデルを読み込む。
    m_modelRender.Init("Assets/modelData/Stage_0/Player.tkm");
    m_modelRender.SetScale(Vector3::One * PLAYER_MODEL_SCALE);
    m_modelRender.SetPosition(m_position);

    EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/Bound.efk");

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

    m_rockOn = FindGO<RockOn>("rockOn");

    return true;
}

void Player::Update()
{
    Move();
    //モデルの更新処理。
    m_modelRender.Update();

    //デバッグ用
    wchar_t x[256];
    swprintf_s(x, 256, L"X=%d", int(m_position.x));
    m_fontRenderX.SetText(x);
    m_fontRenderX.SetPosition({ 500.0f, 300.0f, 0.0f });
    wchar_t y[256];
    swprintf_s(y, 256, L"Y=%d", int(m_position.y));
    m_fontRenderY.SetText(y);
    m_fontRenderY.SetPosition({ 500.0f, 250.0f, 0.0f });
    wchar_t z[256];
    swprintf_s(z, 256, L"Z=%d", int(m_position.z));
    m_fontRenderZ.SetText(z);
    m_fontRenderZ.SetPosition({ 500.0f, 200.0f, 0.0f });
}

void Player::Render(RenderContext& rc)
{
    //モデルの描画。
    m_modelRender.Draw(rc);

    m_fontRenderX.Draw(rc);
    m_fontRenderY.Draw(rc);
    m_fontRenderZ.Draw(rc);
}

void Player::Move()
{
    //剛体の座標と回転を取得。
    m_rigidBody.GetPositionAndRotation(m_position, m_rotation);
    //剛体の座標と回転をモデルに反映。
    m_modelRender.SetPosition(m_position);
    m_modelRender.SetRotation(m_rotation);

    //プレイヤーが進む方向を決定する。
    
    Vector3 forward = g_camera3D->GetForward();                                 //カメラの前方向
    forward.y = 0.0f;
    forward.Normalize();
    
    Vector3 target = m_rockOn->GetDifference();                                 //ロックオンしているオブジェクトの方向

    m_moveSpeed.y = PLAYER_GRAVITY;

    if (g_pad[0]->IsPress(enButtonLB2))                                         //ボタンを押している時
    {
        m_isPress = true;
        if (m_charge < 1.0f)
        {
            m_charge += CHARGE_ADD;
        }
    }
    else if (m_isPress == true && m_rockOn->GetRockOnJudge() == false)          //ボタンが離されて且つロックオンがオフの時
    {
        m_isPress = false;
        m_rigidBody.SetLinearVelocity({ 0.0f,0.0f,0.0f });                      //スピードを初期化
        m_moveSpeed = (forward * PLAYER_SPEED_DEFAULT) * m_charge;              //前後
        m_charge = CHARGE_DEFAULT;
    }
    else if (m_isPress == true && m_rockOn->GetRockOnJudge() == true)           //ボタンが離されて且つロックオンがオンの時
    {
        m_delay += 0.1;
        m_rigidBody.SetLinearVelocity({ 0.0f,0.0f,0.0f });                      //スピードを初期化
        if (m_delay > 1.0f)
        {
            m_isRockOnFire = true;
            m_isPress = false;
            m_moveSpeed = (target * PLAYER_SPEED_DEFAULT) * (m_charge * 3.0f);  //前後
            m_charge = CHARGE_DEFAULT;
            m_delay = 0.0f;
        }
    }

    if (m_isRockOnFire == false)                                                //ロックオンしてない時
    {
        m_moveSpeed.y = PLAYER_GRAVITY;                                         //重力が掛かる
    }

    m_rigidBody.AddForce
    (
        m_moveSpeed,                                                            //力
        g_vec3Zero                                                              //力を加える剛体の相対位置
    );

    //スピードの上限を設定。
    if (m_isRockOnFire == false && m_rigidBody.GetLinearVelocity().Length() >= PLAYER_SPEED_MAX)
    {
        m_rigidBody.SetLinearVelocity(g_camera3D->GetForward() * PLAYER_SPEED_MAX);
    }

    //スピードを徐々に減衰させる。
    if (m_rigidBody.GetLinearXZVelocity().Length() >= 0)
    {
        m_rigidBody.SetLinearVelocity(m_rigidBody.GetLinearVelocity() * pow(PLAYER_SPEED_DECREASE, 2));
    }

    m_moveSpeed.x = 0.0f;                                                       //スピードの初期化
    m_moveSpeed.y = 0.0f;                                                       //スピードの初期化
    m_moveSpeed.z = 0.0f;                                                       //スピードの初期化
}