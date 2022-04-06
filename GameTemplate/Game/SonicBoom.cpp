#include "stdafx.h"
#include "SonicBoom.h"

#include "Player.h"

SonicBoom::SonicBoom()
{

}

SonicBoom::~SonicBoom()
{

}

bool SonicBoom::Start()
{
	m_player = FindGO<Player>("player");

	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/Effect/Selfmade/SonicBoom.efk");
    m_sonicBoom = NewGO<EffectEmitter>(1);
    m_sonicBoom->Init(1);
    m_sonicBoom->SetScale(Vector3::One * 3.0f);
    m_sonicBoom->SetPosition(m_position);
    m_sonicBoom->Play();

    return true;
}

void SonicBoom::Update()
{
    m_position = m_player->GetPosition();
    m_sonicBoom->SetPosition(m_position);

    m_aliveTimer += g_gameTime->GetFrameDeltaTime();
    if (m_aliveTimer > 0.5f)
    {
        m_sonicBoom->Stop();
        DeleteGO(this);
    }
}