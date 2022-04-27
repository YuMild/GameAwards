#pragma once

class Game;
class GameCamera;
class PowerCharge;
class RockOn;
class SonicBoom;

/// <summary>
/// プレイヤー
/// </summary>
class Player : public IGameObject
{
public:
    bool Start() override;
    void Render(RenderContext& rc)override;
    void Update() override;
    void UpdateOnStop() override;
    /// <summary>
    /// ステートを設定
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    int SetState(const int& state)
    {
        m_state = state;
        return m_state;
    }

    /// <summary>
    /// 座標を設定
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(const Vector3& position)
    {
        m_position = position;
    }

    /// <summary>
    /// 大きさを設定。
    /// </summary>
    /// <param name="scale">大きさ。</param>
    void SetScale(const float& scale)
    {
        m_scale = scale;
    }

    /// <summary>
    /// 回転を設定。
    /// </summary>
    /// <param name="rotation">回転。</param>
    void SetRotation(const Quaternion& rotation)
    {
        m_rotation = rotation;
    }

    /// <summary>
    /// プレイヤーの移動速度を設定。
    /// </summary>
    /// <param name="moveSpeed"></param>
    void SetMoveSpeed(const Vector3& moveSpeed)
    {
        m_moveSpeed = moveSpeed;
    }

    /// <summary>
    /// ロックオン時に発射されたか否か。
    /// </summary>
    /// <param name="judge"></param>
    void SetIsRockOnFire(const bool& judge)
    {
        m_isRockOnFire = judge;
    }

    /// <summary>
    /// リスポーン地点を設定。
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
    /// 座標を取得
    /// </summary>
    /// <returns></returns>
    Vector3 GetPosition() const
    {
        return m_position;
    }

    /// <summary>
    /// チャージ量を取得。
    /// </summary>
    /// <returns></returns>
    float GetCharge() const
    {
        return m_charge;
    }

    /// <summary>
    /// プレイヤーのスピードを取得
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

    RigidBody           m_rigidBody;                //剛体

private:

    /// <summary>
    /// デスの判定
    /// </summary>
    void Death();

    /// <summary>
    /// 動作を管理
    /// </summary>
    void Move();

    EffectEmitter*      m_reSpawn;
    SoundSource*        m_sound;

    FontRender          m_fontRenderX;              //フォントレンダー
    FontRender          m_fontRenderY;              //フォントレンダー
    FontRender          m_fontRenderZ;              //フォントレンダー
    SpriteRender        m_gaugeRender;              //画像
    ModelRender         m_modelRender;              //モデルレンダー
    SphereCollider      m_sphereCollider;           //円型のコライダー

    Vector3             m_position;                 //ポジション
    Vector3             m_reSpawnPosition;          //リスポーンポイント
    Vector3             m_cameraForward;            //カメラの前方向
    Vector3             m_cameraRight;              //カメラの左右方向
    Vector3             m_moveSpeed;                //プレイヤーの移動速度

    Quaternion          m_rotation;                 //回転

    bool                m_isEffectStart = true;     //エフェクトを一回だけ再生させる
    bool                m_isPress = false;          //ボタンが押されているか否かの判定
    bool                m_isRockOnFire = false;     //ロックオン時に発射されたか否かの判定
    bool                m_isPowerCharge = true;     //パワーチャージエフェクト
    bool                m_stop = false;
    int                 m_state;                    //ステート
    float               m_scale = 0.0f;             //サイズ
    float               m_charge = 0.0f;            //チャージ
    float               m_delay = 0.0f;             //ディレイ
    float               m_stopTimer = 0.0f;

    Game*               m_game;
    GameCamera*         m_gameCamera;
    PowerCharge*        m_powerCharge;
    RockOn*             m_rockOn;
    SonicBoom*          m_sonicBoom;
};