#include "stdafx.h"
#include "TimeLimit.h"

#include "Game.h"

namespace
{
    float SET_TIMELIMIT = 200.0f;
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

    m_2dAnimation.Init("Assets/sprite/ChargeAnimation/", 340.0f, 340.0f, 29);
    m_2dAnimation.SetLoopFlag(true);
    m_2dAnimation.SetDrawSpeed(2);
    m_2dAnimation.Play();

    return true;
}

void TimeLimit::Update()
{
    m_2dAnimation.Update();

    m_limitTimer -= g_gameTime->GetFrameDeltaTime();

    if (m_limitTimer <= 0)
    {
        m_game->SetGameState(2);
    }

    wchar_t x[256];
    swprintf_s(x, 256, L"Time:%f", m_limitTimer);
    m_fontRender.SetText(x);
    m_fontRender.SetPosition({ -500.0f, 300.0f, 0.0f });
}

void TimeLimit::Render(RenderContext& rc)
{
    m_2dAnimation.Draw(rc);

#ifdef K2_DEBUG
    m_fontRender.Draw(rc);
#endif
}