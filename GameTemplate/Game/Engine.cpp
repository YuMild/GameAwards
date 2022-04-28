#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{

}

bool Engine::Start()
{
	m_modelRender.Init("Assets/modelData/Stage_0/Engine.tkm",true);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(m_scale);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	return true;
}

void Engine::Update()
{
	m_modelRender.Update();
}

void Engine::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}