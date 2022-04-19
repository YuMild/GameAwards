#include "stdafx.h"
#include "Setting.h"

#include "Title.h"

namespace
{
	float ZOOM = 1.3f;
}

Setting::Setting()
{

}

Setting::~Setting()
{

}

bool Setting::Start()
{
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/Choice.wav");
	
	m_apply.Init("Assets/sprite/Setting/Apply.dds", 800.0f, 800.0f);
	m_apply.SetPosition({ 200.0f,-300.0f,0.0f });
	m_apply.Update();
	m_applyChoice.Init("Assets/sprite/Setting/ApplyChoice.dds", 800.0f, 800.0f);
	m_applyChoice.SetPosition({ 200.0f,-300.0f,0.0f });
	m_applyChoice.Update();
	m_backGround.Init("Assets/sprite/Setting/BackGround.dds", 1600.0f, 900.0f);
	m_backGround.SetPosition({ 0.0f,0.0f,0.0f });
	m_backGround.Update();
	m_cancel.Init("Assets/sprite/Setting/Cancel.dds", 800.0f, 800.0f);
	m_cancel.SetPosition({ -200.0f,-300.0f,0.0f });
	m_cancel.Update();
	m_cancelChoice.Init("Assets/sprite/Setting/CancelChoice.dds", 800.0f, 800.0f);
	m_cancelChoice.SetPosition({ -200.0f,-300.0f,0.0f });
	m_cancelChoice.Update();
	m_controll.Init("Assets/sprite/Setting/Controll.dds", 800.0f, 800.0f);
	m_controll.SetPosition({ -250.0f,300.0f,0.0f });
	m_controll.Update();
	m_controllChoice.Init("Assets/sprite/Setting/ControllChoice.dds", 800.0f, 800.0f);
	m_controllChoice.SetPosition({ -250.0f,300.0f,0.0f });
	m_controllChoice.Update();
	m_sound.Init("Assets/sprite/Setting/Sound.dds", 800.0f, 800.0f);
	m_sound.SetPosition({ 250.0f,300.0f,0.0f });
	m_sound.Update();
	m_soundChoice.Init("Assets/sprite/Setting/SoundChoice.dds", 800.0f, 800.0f);
	m_soundChoice.SetPosition({ 250.0f,300.0f,0.0f });
	m_soundChoice.Update();
	m_stickSensitivity.Init("Assets/sprite/Setting/StickSensitivity.dds", 800.0f, 800.0f);
	m_stickSensitivity.SetPosition({ -400.0f,100.0f,0.0f });
	m_stickSensitivity.Update();
	m_stickSensitivityChoice.Init("Assets/sprite/Setting/StickSensitivityChoice.dds", 800.0f, 800.0f);
	m_stickSensitivityChoice.SetPosition({ -400.0f,100.0f,0.0f });
	m_stickSensitivityChoice.Update();
	m_stickSensitivityBar.Init("Assets/sprite/Setting/StickSensitivityBar.dds", 800.0f, 800.0f);
	m_stickSensitivityBar.SetPosition({ 400.0f,100.0f,0.0f });
	m_stickSensitivityBar.Update();
	m_stickSensitivityBarChoice.Init("Assets/sprite/Setting/StickSensitivityBarChoice.dds", 800.0f, 800.0f);
	m_stickSensitivityBarChoice.SetPosition({ 400.0f,100.0f,0.0f });
	m_stickSensitivityBarChoice.Update();
	m_vibration.Init("Assets/sprite/Setting/Vibration.dds", 800.0f, 800.0f);
	m_vibration.SetPosition({ -400.0f,0.0f,0.0f });
	m_vibration.Update();
	m_vibrationChoice.Init("Assets/sprite/Setting/VibrationChoice.dds", 800.0f, 800.0f);
	m_vibrationChoice.SetPosition({ -400.0f,0.0f,0.0f });
	m_vibrationChoice.Update();

	return true;
}

void Setting::Update()
{
	Choice();
	Sprite();
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		DeleteGO(this);
	}
}

void Setting::Render(RenderContext& rc)
{
	m_backGround.Draw(rc);
	
	//�R���g���[��
	if (m_shelf == 0)
	{
		m_controllChoice.Draw(rc);
	}
	else
	{
		m_controll.Draw(rc);
	}
	if (m_shelf == 0 && m_choiceState == 0)
	{
		m_stickSensitivityChoice.Draw(rc);
		m_stickSensitivityBarChoice.Draw(rc);
	}
	else
	{
		m_stickSensitivity.Draw(rc);
		m_stickSensitivityBar.Draw(rc);
	}
	if (m_shelf == 0 && m_choiceState == 1)
	{
		m_vibrationChoice.Draw(rc);
	}
	else
	{
		m_vibration.Draw(rc);
	}
	if (m_shelf == 0 && m_choiceState == 2)
	{
		m_cancelChoice.Draw(rc);
	}
	else
	{
		m_cancel.Draw(rc);
	}
	if (m_shelf == 0 && m_choiceState == 3)
	{
		m_applyChoice.Draw(rc);
	}
	else
	{
		m_apply.Draw(rc);
	}

	//�T�E���h
	if (m_shelf == 1)
	{
		m_soundChoice.Draw(rc);
	}
	else
	{
		m_sound.Draw(rc);
	}
}

void Setting::Choice()
{
	//�R���g���[���ƃT�E���h�̐ؑ�
	if (m_shelf == 0 && g_pad[0]->IsTrigger(enButtonRB1))
	{
		m_shelf = 1;
		m_choiceState = 0;
	}
	else if (m_shelf == 1 && g_pad[0]->IsTrigger(enButtonLB1))
	{
		m_shelf = 0;
		m_choiceState = 0;
	}

	//�I���Ȗڂ̐ؑ�
	if (m_choiceState >= 0 && m_choiceState < 2 && g_pad[0]->IsTrigger(enButtonDown))
	{
		m_choiceState += 1;
	}

	if (m_choiceState <= 2 && m_choiceState > 0 && g_pad[0]->IsTrigger(enButtonUp))
	{
		m_choiceState -= 1;
	}

	if (m_choiceState == 2 && g_pad[0]->IsTrigger(enButtonRight))
	{
		m_choiceState += 1;
	}

	if (m_choiceState == 3 && g_pad[0]->IsTrigger(enButtonLeft))
	{
		m_choiceState -= 1;
	}

	if (m_choiceState == 3 && g_pad[0]->IsTrigger(enButtonUp))
	{
		m_choiceState -= 2;
	}
}

void Setting::Sprite()
{
	//�R���g���[��
	if (m_shelf == 0)
	{
		m_controllChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_controllChoice.Update();
	}
	else
	{
		m_controllChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_controllChoice.Update();
	}
	//�X�e�B�b�N���x
	if (m_shelf == 0 && m_choiceState == 0)
	{
		m_stickSensitivityChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_stickSensitivityChoice.Update();
		m_stickSensitivityBarChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_stickSensitivityBarChoice.Update();
	}
	else
	{
		m_stickSensitivityChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_stickSensitivityChoice.Update();
		m_stickSensitivityBarChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_stickSensitivityBarChoice.Update();
	}
	//�o�C�u���[�V����
	if (m_shelf == 0 && m_choiceState == 1)
	{
		m_vibrationChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_vibrationChoice.Update();
	}
	else
	{
		m_vibrationChoice.SetScale({ 1.0f,1.0f,1.0f });
		m_vibrationChoice.Update();
	}
	//�L�����Z��
	if (m_shelf == 0 && m_choiceState == 2)
	{
		m_cancelChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_cancelChoice.Update();
	}
	else
	{
		m_cancelChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_cancelChoice.Update();
	}
	//�K�p
	if (m_shelf == 0 && m_choiceState == 3)
	{
		m_applyChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_applyChoice.Update();
	}
	else
	{
		m_applyChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_applyChoice.Update();
	}

	//�T�E���h
	if (m_shelf == 1)
	{
		m_soundChoice.SetScale({ ZOOM ,ZOOM ,0.0f });
		m_soundChoice.Update();
	}
	else
	{
		m_soundChoice.SetScale({ 1.0f ,1.0f ,0.0f });
		m_soundChoice.Update();
	}
}