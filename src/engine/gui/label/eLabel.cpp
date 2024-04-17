//◦ EggEngine ◦
#include "eLabel.h"
#include "engine/debug/eAssert.h"
#include "engine/common/eRect.h"

using namespace Engine::GUI;


ELabel::ELabel()
{

}


ELabel::~ELabel()
{
	Destroy();
}


void ELabel::Destroy()
{
	if (m_texture) {
		SDL_DestroyTexture(m_texture);
		m_texture = {};
	}
	m_sizeTexture = {};
}


void ELabel::SetPosition(const FPoint &pos)
{
	if (m_position != pos) {
		m_position = pos;
		CalcQuad();
	}
}


void ELabel::SetScale(const FPoint &scale)
{
	m_scale = scale;
	CalcQuad();
}

void ELabel::SetScale(const float scale)
{
	m_scale.x = scale;
	m_scale.y = scale;
	CalcQuad();
}


void ELabel::SetColor(const SDL_Color &color)
{
	Destroy();
	m_color = color;
}


void ELabel::SetText(const std::string &text)
{
	Destroy();
	m_text = text;
}


void ELabel::SetFont(const Engine::Assets::EAssetFont::Ptr &font)
{
	Destroy();
	m_font = font;
}

void ELabel::SetAlignH(const EAlign align)
{
	m_alignH = align;
	CalcQuad();
}

void ELabel::SetAlignV(const EAlign align)
{
	m_alignV = align;
	CalcQuad();
}


//Отрисовка спрайта ввиде квадрата с растяжением во все стороны
void ELabel::CalcQuad()
{
	if (m_sizeTexture.x == 0 || m_sizeTexture.y == 0) {
		return;
	}
	
	FPoint size = m_scale * m_sizeTexture;
	float x = m_position.x;
	float y = m_position.y;
	switch (m_alignH) {
		case EAlign::left: 		x = m_position.x; break;
		case EAlign::right: 	x = m_position.x - size.x; break;
		case EAlign::center:	x = m_position.x - size.x * 0.5f; break;
			
		case EAlign::top: break;
		case EAlign::bottom: break;
	}
	
	switch (m_alignV) {
		case EAlign::top: 		y = m_position.y; break;
		case EAlign::bottom: 	y = m_position.y - size.y; break;
		case EAlign::center:	y = m_position.y - size.y * 0.5f; break;

		case EAlign::left: break;
		case EAlign::right: break;
	}
	
	FRect dst;
	dst.x1 = x;
	dst.x2 = x + size.x;
	dst.y1 = y;
	dst.y2 = y + size.y;
	
	
	FRect src;
	src.x1 = 0;
	src.x2 = 1;
	src.y1 = 0;
	src.y2 = 1;
	
	m_vx[0].position.x = dst.x1;
	m_vx[0].position.y = dst.y1;
	m_vx[0].tex_coord.x = src.x1;
	m_vx[0].tex_coord.y = src.y1;
	m_vx[0].color = m_color;

	m_vx[1].position.x = dst.x2;
	m_vx[1].position.y = dst.y1;
	m_vx[1].tex_coord.x = src.x2;
	m_vx[1].tex_coord.y = src.y1;
	m_vx[1].color = m_color;

	m_vx[2].position.x = dst.x2;
	m_vx[2].position.y = dst.y2;
	m_vx[2].tex_coord.x = src.x2;
	m_vx[2].tex_coord.y = src.y2;
	m_vx[2].color = m_color;
	
	
	m_vx[3].position.x = dst.x1;
	m_vx[3].position.y = dst.y2;
	m_vx[3].tex_coord.x = src.x1;
	m_vx[3].tex_coord.y = src.y2;
	m_vx[3].color = m_color;
}


void ELabel::Render(const Engine::Render::ESpriteBatch::UPtr& context)
{
	if (!m_text.empty()) {
		if (!m_texture && m_font) {
			m_texture = m_font->MakeText(context, m_text, m_color);
			SDL_QueryTexture(m_texture, nullptr, nullptr, &m_sizeTexture.x, &m_sizeTexture.y);
			CalcQuad();
		}
		if (m_texture) {
			static int indices[6] = {0, 1, 2, 2, 3, 0};
			context->RenderGeometry(m_texture, m_vx, 4, indices, 6);
		}
	}
}


