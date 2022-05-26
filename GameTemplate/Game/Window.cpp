#include "stdafx.h"
#include "Window.h"

Window::Window()
{

}

Window::~Window()
{

}

bool Window::Start()
{
	m_window2D.Init("Assets/sprite/window/UI.dds",1600.0f, 900.0f);

	return true;
}

void Window::Update()
{

}

void Window::Render(RenderContext& rc)
{
	m_window2D.Draw(rc);
}