#include "stdafx.h"
#include "TimeLimit.h"

#include "Game.h"

namespace
{
    float SET_TIMELIMIT = 60.0f;
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
    m_2dAnimation.SetDrawSpeed(1);
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
    swprintf_s(x, 256, L"%d", int(m_limitTimer));
    m_fontRender.SetText(x);
    m_fontRender.SetPosition({ 120.0f, 405.0f, 0.0f });
    m_fontRender.SetScale(1.5f);
    m_fontRender.SetColor({ 0.0f, 230.0f, 255.0f,0.0f });
    m_fontRender.SetPivot(1.0f, 0.5f);
}

void TimeLimit::Render(RenderContext& rc)
{
    m_2dAnimation.Draw(rc);

    m_fontRender.Draw(rc);
}