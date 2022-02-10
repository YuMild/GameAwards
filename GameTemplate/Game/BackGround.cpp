#include "stdafx.h"
#include "BackGround.h"

bool BackGround::Start()
{
	m_modelRender.Init("Assets/modelData/Stage.tkm");
	m_modelRender.SetScale(1.0f,1.0f,1.0f);
	m_modelRender.Update();

	// 静的物理オブジェクトを作成。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel() , m_modelRender.GetModel().GetWorldMatrix());

	return true;
}
void BackGround::Update()
{

}
void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}