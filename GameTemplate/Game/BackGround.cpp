#include "stdafx.h"
#include "BackGround.h"

bool BackGround::Start()
{
	m_modelRender.Init("Assets/modelData/bg/bg.tkm");
	// 静的物理オブジェクトを作成。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel() , m_modelRender.GetModel().GetWorldMatrix());
	m_modelRender2.Init("Assets/modelData/light.tkm");

	return true;
}
void BackGround::Update()
{
	m_modelRender2.SetPosition(g_sceneLight.GetPointLightPosition());
	m_modelRender2.Update();
}
void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_modelRender2.Draw(rc);
}