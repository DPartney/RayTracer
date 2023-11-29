#include "Canvas.h"
#include <SDL.h>
#include "Renderer.h"

Canvas::Canvas(int width, int height, const Renderer& renderer)
{
	this->m_size = glm::ivec2(width, height);
	this->m_texture = SDL_CreateTexture(renderer.m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	this->m_buffer.resize(width * height);
}

Canvas::~Canvas()
{
	if (this->m_texture != nullptr) {
		SDL_DestroyTexture(this->m_texture);
	}
}

void Canvas::Update()
{
	SDL_UpdateTexture(this->m_texture, NULL, this->m_buffer.data(), this->m_size.x * sizeof(rgba_t));
}

void Canvas::Clear(const color4_t& color)
{
	rgba_t rgba = ColorToRGBA(color);

	std::fill(this->m_buffer.begin(), this->m_buffer.end(), rgba);
}

void Canvas::DrawPoint(const glm::ivec2& point, const color4_t& color)
{
	if ((point.x < 0 || point.x >= m_size.x) || (point.y < 0 || point.y >= m_size.y)) {
		return;
	}
	this->m_buffer[point.x + (point.y * this->m_size.x)] = ColorToRGBA(color);
}
