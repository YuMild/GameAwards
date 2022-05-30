#include "stdafx.h"
#include "TimeLimit.h"

#include "Game.h"
#include "GameOver.h"

namespace
{
    float SET_TIMELIMIT = 50.0f;
}

TimeLimit::TimeLimit()
{

}

TimeLimit::~TimeLimit()
{

}

bool TimeLimit::Start()
{
    m_game = FindGO<Game>("game");

    m_limitTimer = SET_TIMELIMIT;

    m_fontRender.SetPosition({ 120.0f, 405.0f, 0.0f });
    m_fontRender.SetScale(1.5f);
    m_fontRender.SetColor({ 0.0f, 230.0f, 255.0f,0.0f });
    m_fontRender.SetPivot(1.0f, 0.5f);

    //m_2dAnimation.Init("Assets/sprite/ChargeAnimation/", 340.0f, 340.0f, 29);
    //m_2dAnimation.SetLoopFlag(true);
    //m_2dAnimation.SetDrawSpeed(1);
    //m_2dAnimation.Play();

    return true;
}

void TimeLimit::Update()
{
    Time();

    //m_2dAnimation.Update();
}

void TimeLimit::Render(RenderContext& rc)
{
    if (m_game->GetGameState() == 0)
    {
        m_fadeState = enState_FadeOut;
        m_fontRender.SetColor({ 0.0f, 230.0f, 255.0f,m_currentAlpha });
        m_fontRender.Draw(rc);
    }
}

void TimeLimit::Fade()
{
    switch (m_fadeState) {
    case enState_FadeIn:
        m_currentAlpha -= g_gameTime->GetFrameDeltaTime();
        if (m_currentAlpha <= 0.0f) {
            m_currentAlpha = 0.0f;
            m_fadeState = enState_Idle;
        }
        break;
    case enState_FadeOut:
        m_currentAlpha += g_gameTime->GetFrameDeltaTime();
        if (m_currentAlpha >= 1.0f) {
            m_currentAlpha = 1.0f;
            m_fadeState = enState_Idle;
        }
        break;
    case enState_Idle:
        break;
    }
}

void TimeLimit::Time()
{
    if (m_game->GetGameState() == 1)
    {
        return;
    }

    m_limitTimer -= g_gameTime->GetFrameDeltaTime();

    //時間切れになったら
    if (m_limitTimer <= 0)
    {
        //操作不能にする
        m_game->SetGameState(1);
        //ゲームオーバー演出をする
        m_gameOver = NewGO<GameOver>(0, "gameOver");
        DeleteGO(this);
    }

    if (m_limitTimer < 10)
    {
        m_fontRender.SetPosition({ 130.0f,405.0f,0.0f });
    }

    wchar_t x[256];
    swprintf_s(x, 256, L"%d", int(m_limitTimer));
    m_fontRender.SetText(x);
}