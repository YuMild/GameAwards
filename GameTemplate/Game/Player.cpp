#include "stdafx.h"
#include "Player.h"

bool Player::Start()
{
	//アニメーションクリップをロードする。
	m_animationClipArray[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/animData/walk.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	//tkmファイルのファイルパスを指定する。
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);
	m_charaCon.Init(25.0f, 75.0f, m_position);
	return true;
}

void Player::Update()
{
	
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		m_modelRender.PlayAnimation(enAnimClip_Run, 0.1f);
	}
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		m_modelRender.PlayAnimation(enAnimClip_Idle, 0.1f);
	}
	if (g_pad[0]->IsPress(enButtonY))
	{
		m_rotation.AddRotationDegY(5.0f);
		m_modelRender.SetRotation(m_rotation);
	}
	Vector3 moveSpeed;
	moveSpeed.x = g_pad[0]->GetLStickXF() * 120.0f;
	moveSpeed.z = g_pad[0]->GetLStickYF() * 120.0f;
	m_position=m_charaCon.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	//m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	g_sceneLight.SetPointLightPosition(m_position);


}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}