#pragma once

class Player : public IGameObject
{
public:
    bool Start() override;
    void Render(RenderContext& rc)override;
    void Update() override;

private:
    ModelRender m_modelRender;
    //以下2つのクラスを使用する。
    SphereCollider m_sphereCollider;            //円型のコライダー。
    RigidBody m_rigidBody;                        //剛体。
    Vector3 m_position;
};