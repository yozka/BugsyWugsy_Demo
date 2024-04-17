//◦ EggEngine ◦
#include "eSpriteBatch.h"
#include "engine/debug/eAssert.h"
#include "engine/common/eRect.h"

using namespace Engine::Render;

ESpriteBatch::ESpriteBatch()
{
	m_vx.reserve(30000);
	m_indices.reserve(30000);
}


ESpriteBatch::~ESpriteBatch()
{
	sassert(!m_context);
	sassert(!m_texture);
}


int ESpriteBatch::RenderWidth() const
{
	return m_context ? m_context->RenderWidth() : 0;
}


int ESpriteBatch::RenderHeight() const
{
	return m_context ? m_context->RenderHeight() : 0;
}


SDL_Texture* ESpriteBatch::CreateTexture(SDL_Surface* surface)
{
	if (m_context) {
		return m_context->CreateTexture(surface);
	}
	return {};
}


void ESpriteBatch::Begin(const ERenderContext::UPtr &context)
{
	sassert(!m_context);
	m_context = context.get();
	m_texture = {};
}


void ESpriteBatch::End()
{
	Flush();
	m_context = {};
}


void ESpriteBatch::Flush()
{
	if (m_context && m_texture) {
		m_context->RenderGeometry(m_texture, m_vx.data(), static_cast<int>(m_vx.size()), m_indices.data(), static_cast<int>(m_indices.size()));
		m_vx.clear();
		m_indices.clear();
		m_texture = {};
	}
}

void ESpriteBatch::RenderCopyF(SDL_Texture *texture, const SDL_Rect *source, const SDL_FRect *destination)
{
	if (!m_context) return;
	
	if (m_texture && m_texture != texture) {
		Flush();
	}
	
	if (!m_texture) {
		m_texture = texture;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
		sassert(m_width);
		sassert(m_height);
	}
	
	static const SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF};
	const int start = static_cast<int>(m_vx.size());
	
	Engine::FRect dst;
	dst.x1 = destination->x;
	dst.x2 = destination->x + destination->w;
	dst.y1 = destination->y;
	dst.y2 = destination->y + destination->h;

	Engine::FRect src;
	src.x1 = static_cast<float>(source->x) / m_width;
	src.x2 = static_cast<float>(source->x + source->w) / m_width;
	src.y1 = static_cast<float>(source->y) / m_height;
	src.y2 = static_cast<float>(source->y + source->h) / m_height;
	
	if (src.x2 > 1) {
		src.x2 = 1;
	}
	if (src.y2 > 1) {
		src.y2 = 1;
	}
	
	{
		// Верхний левый
		SDL_Vertex vx;
		vx.position.x = dst.x1;
		vx.position.y = dst.y1;
		vx.tex_coord.x = src.x1;
		vx.tex_coord.y = src.y1;
		vx.color = color;
		m_vx.push_back(std::move(vx));
	}

	{
		// Верхний правый
		SDL_Vertex vx;
		vx.position.x = dst.x2;
		vx.position.y = dst.y1;
		vx.tex_coord.x = src.x2;
		vx.tex_coord.y = src.y1;
		vx.color = color;
		m_vx.push_back(std::move(vx));
	}
	
	{
		// Нижний правый
		SDL_Vertex vx;
		vx.position.x = dst.x2;
		vx.position.y = dst.y2;
		vx.tex_coord.x = src.x2;
		vx.tex_coord.y = src.y2;
		vx.color = color;
		m_vx.push_back(std::move(vx));
	}
	

	{
		// Нижний левый
		SDL_Vertex vx;
		vx.position.x = dst.x1;
		vx.position.y = dst.y2;
		vx.tex_coord.x = src.x1;
		vx.tex_coord.y = src.y2;
		vx.color = color;
		m_vx.push_back(std::move(vx));
	}
	
	/*
	// Определение индексов для отрисовки прямоугольника
	Uint16 indices[6] = {
	0, 1, 2, // Первый треугольник
	2, 3, 0  // Второй треугольник
	};
	*/
	m_indices.push_back(start + 0);
	m_indices.push_back(start + 1);
	m_indices.push_back(start + 2);
	m_indices.push_back(start + 2);
	m_indices.push_back(start + 3);
	m_indices.push_back(start + 0);
}

void ESpriteBatch::RenderGeometry(SDL_Texture* texture, const SDL_Vertex *vertexts, const int count, const int *indices, int countIndices)
{
	if (!m_context) return;
	
	if (m_texture && m_texture != texture) {
		Flush();
	}
	
	if (!m_texture) {
		m_texture = texture;
		int width = {};
		int height = {};
		SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);
		sassert(width);
		sassert(height);
		m_width = static_cast<float>(width);
		m_height = static_cast<float>(height);
	}
	const int start = static_cast<int>(m_vx.size());
	auto *vt = vertexts;
	for (int i = 0; i < count; i++) {
		m_vx.push_back(*vt);
		vt++;
	}
	auto *ind = indices;
	for (int i = 0; i < countIndices; i++) {
		m_indices.push_back(*ind + start);
		ind++;
	}
}


void ESpriteBatch::RenderFillRect(const SDL_FRect &rect, const SDL_Color &color)
{
	if (m_context) {
		Flush();
		m_context->RenderFillRect(rect, color);
	}
}
