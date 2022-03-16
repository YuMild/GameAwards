#include "stdafx.h"
#include "GameCamera.h"


#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");
	m_toCameraPos.Set(0.0f, 100.0f, 100.0f);

	g_camera3D->SetFar(10000.0f);

	m_springCamera.Init(
		*g_camera3D,			//	ばねカメラの処理を行うカメラを指定する
		10000.0f				//	カメラの移動速度の最大値
	);
	
	m_springCamera.SetDampingRate(0.7f);

	return true;
}

void GameCamera::Update()
{
	m_target = m_player->GetPosition();
	m_target.y += 0.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	//	パッドの入力を使ってカメラを回す
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//	Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * x);
	qRot.Apply(m_toCameraPos);

	//	X軸周りの回転
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Apply(m_toCameraPos);

	//	カメラの回転の上限をチェックする
	//	注視点から視点までのベクトルを正規化する
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		m_toCameraPos = toCameraPosOld;							//	カメラが上に向き過ぎるのを防ぐ
	}
	else if (toPosDir.y > 0.9f) {
		m_toCameraPos = toCameraPosOld;							//	カメラが下に向き過ぎるのを防ぐ
	}

	//	視点を計算する
	Vector3 pos = m_target + m_toCameraPos;

	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(m_target);
	m_springCamera.Update();
}