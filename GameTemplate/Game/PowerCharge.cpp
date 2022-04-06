#include "stdafx.h"
#include "PowerCharge.h"

#include "Player.h"

PowerCharge::PowerCharge()
{

}

PowerCharge::~PowerCharge()
{

}

bool PowerCharge::Start()
{
    m_player = FindGO<Player>("player");

    EffectEngine::GetInstance()->ResistEffect(2, u"Assets/Effect/Selfmade/PowerCharge.efk");
    m_powerCharge = NewGO<EffectEmitter>(2);
    m_powerCharge->Init(2);
    m_powerCharge->SetScale(Vector3::One * 5.0f);
    m_powerCharge->SetPosition(m_position);
    m_powerCharge->Play();

    return true;
}

void PowerCharge::Update()
{
    m_position = m_player->GetPosition();
    m_powerCharge->SetPosition(m_position);

    m_aliveTimer += g_gameTime->GetFrameDeltaTime();
    if (m_aliveTimer > 0.3f)
    {
        m_powerCharge->Stop();
        DeleteGO(this);
    }
}