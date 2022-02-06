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

private:
    ModelRender m_modelRender;
    //以下2つのクラスを使用する。
    SphereCollider m_sphereCollider;            //円型のコライダー。
    RigidBody m_rigidBody;                        //剛体。
    Vector3 m_position;

    bool m_isPress = false;
    float m_gauge = 0.0f;
    float m_gaugeOld = 0.0f;
};