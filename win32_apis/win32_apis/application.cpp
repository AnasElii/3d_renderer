#pragma once

#include <stdexcept>
#include <iostream>

#include "application.hpp"
#include "iplatform_adapter.hpp"
#include "platform_factory.hpp"

Application::Application()
{
	m_platform_adapter = GetPlatformAdapter();
	if (!m_platform_adapter)
	{
		throw std::runtime_error("Unsupported platform!");
	}

	m_renderer = new Renderer();

}

Application::~Application()
{
	delete m_platform_adapter;
	delete m_renderer;
}

void Application::SetupRenderer(uint32_t* color_buffer, int width, int height)
{
	if (!m_renderer)
	{
		std::cerr << "Failed renderer not initialized!\n";
		return;
	}

	m_renderer->Initialize(color_buffer, width, height);
}

void Application::StartWindowed(int x, int y, int width, int height, int antialiasing)
{
	m_platform_adapter->StartWindowed(
		x, 
		y, 
		width, 
		height, 
		antialiasing, 
		*this
	);
}

void Application::finish()
{
	if (m_renderer)
	{
		m_renderer->Shutdown();
	}
	m_platform_adapter->finish(*this);
}

