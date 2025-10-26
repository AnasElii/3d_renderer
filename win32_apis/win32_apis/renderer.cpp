﻿#include <iostream>

#include "renderer.hpp"

Renderer::Renderer() : m_color_buffer(nullptr), m_buffer_width(0), m_buffer_height(0) {}
Renderer::~Renderer()
{
	// Note: We don't delete m_color_buffer since it's owned by the platform adapter
}

void Renderer::Initialize(uint32_t* color_buffer, int width, int height)
{
	if (!color_buffer) return;
	if (width <= 0 || height <= 0) return;

	m_color_buffer = color_buffer;
	m_buffer_width = width;
	m_buffer_height = height;

}

void Renderer::Shutdown()
{
	m_color_buffer = nullptr;
	m_buffer_width = 0;
	m_buffer_height = 0;
}


void Renderer::ClearColorBuffer(uint32_t color)
{

	if (!m_color_buffer) return;
	if (m_buffer_width <= 0 || m_buffer_height <= 0) return;

	for (int i = 0; i < m_buffer_width * m_buffer_height; ++i)
	{
		m_color_buffer[i] = color;
	}

}

// Set pixel at coordinates (x, y)
void Renderer::SetPixel(int x, int y, uint32_t color)
{
	if (!m_color_buffer)
		return;

	if (m_buffer_width <= 0 || m_buffer_height <= 0)
		return;

	if (m_color_buffer && x >= 0 && x < m_buffer_width
		&& y >= 0 && y < m_buffer_height)
	{
		m_color_buffer[y * m_buffer_width + x] = color;
	}
}

void Renderer::DrawGrid(uint32_t color, int spacing)
{
	if (!m_color_buffer)
		return;

	if (m_buffer_width <= 0 || m_buffer_height <= 0)
		return;

	// Vertical lines
	for (int dy = 0; dy <= m_buffer_width; dy += spacing)
	{
		for (int dx = 0; dx <= m_buffer_width; dx += spacing)
		{
			SetPixel(dx, dy, color);
		}
	}
}

void Renderer::DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color)
{
	if (!m_color_buffer)
		return;

	for (int dy = 0; dy <= height; dy++)
	{
		for (int dx = 0; dx <= width; dx++)
		{
			int new_x = x + dx;
			int new_y = y + dy;

			if (new_x >= 0 && new_x < m_buffer_width
				&& new_y >= 0 && new_y < m_buffer_height)
				SetPixel(new_x, new_y, color);
		}
	}
}