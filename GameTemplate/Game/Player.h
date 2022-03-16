#pragma once

/// <summary>
/// プレイヤー
/// </summary>
class Player : public IGameObject
{
public:
    bool Start() override;
    void Render(RenderContext& rc)override;
    void Update() override;

    /// <summary>
    /// 座標を設定
    /// </summary>
    /// <param name="position"></param>
    void SetPosition(Vector3& position)
    {
        m_position = position;
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
    /// 大きさを設定。
    /// </summary>
    /// <param name="scale">大きさ。</param>
    void SetScale(const Vector3& scale)
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
    /// プレイヤーの移動速度を取得
    /// </summary>
    /// <param name="moveSpeed"></param>
    void SetMoveSpeed(Vector3& moveSpeed)
    {
        m_moveSpeed = moveSpeed;
    }

    /// <summary>
    /// チャージ量を取得
    /// </summary>
    /// <returns></returns>
    float GetCharge() const
    {
        return m_charge;
    }

    /// <summary>
    /// プレーヤーのスピードを取得
    /// </summary>
    /// <returns></returns>
    float GetPlayerSpeed() const
    {
        return m_rigidBody.GetLinearVelocity().Length();
    }
private:

    /// <summary>
    /// 動作を管理
    /// </summary>
    void Move();

    /// <summary>
    /// 死亡判定を管理
    /// </summary>
    void Death();

    FontRender m_fontRender;

    ModelRender m_modelRender;
    SphereCollider m_sphereCollider;        //円型のコライダー
    RigidBody m_rigidBody;                  //剛体

    Vector3 m_position;                     //ポジション
    Vector3 m_scale;
    Vector3 m_cameraForward;
    Vector3 m_cameraRight;
    Vector3 m_moveSpeed;

    Quaternion m_rotation;                  //回転

    SpriteRender m_gaugeRender;

    bool m_isPress = false;
    float m_charge = 0.0f;
    float m_timer = 0.0f;
};