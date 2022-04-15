#include "stdafx.h"
#include "TimeLimit.h"

#include "Game.h"

namespace
{
    float SET_TIMELIMIT = 100.0f;
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

    return true;
}

void TimeLimit::Update()
{
    m_limitTimer -= g_gameTime->GetFrameDeltaTime();

    if (m_limitTimer <= 0)
    {
        m_game->SetGemeEnd(1);
    }

    wchar_t x[256];
    swprintf_s(x, 256, L"Time:%f", m_limitTimer);
    m_fontRender.SetText(x);
    m_fontRender.SetPosition({ -500.0f, 300.0f, 0.0f });
}

void TimeLimit::Render(RenderContext& rc)
{
    m_fontRender.Draw(rc);
}