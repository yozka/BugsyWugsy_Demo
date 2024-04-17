//◦ EggEngine ◦
#include "eScreenKey.h"


using namespace Engine::Input;


EScreenKey::EScreenKey(const std::string& name)
	:
		m_name(name)
{

}


void EScreenKey::Unbinding()
{
	onPressed = {};
	onReleased = {};
}


bool EScreenKey::InputDown(const SYSTouch& touch)
{
	if (m_rect.IsInside(touch.pos)) {
		m_pushed = true;
		m_touchId = touch.id;
		if (onPressed) {
			onPressed();
		}
		return true;
	}
	return false;
}


bool EScreenKey::InputMove(const SYSTouch& touch)
{
	return false;
}


bool EScreenKey::InputUp(const SYSTouch& touch)
{
	if (m_pushed && m_touchId == touch.id) {
		m_pushed = false;
		m_touchId =-1;
		if (onReleased) {
			onReleased();
		}
		return true;
	}
	return false;
}


void EScreenKey::Update(const float dt)
{

}


void EScreenKey::Render(const Engine::Render::ERenderContext::UPtr& context)
{
	SDL_Color ncolor = m_pushed ? m_colorPush : m_color;

	SDL_Vertex vx[4];

	vx[0].position.x = m_rect.x1;
	vx[0].position.y = m_rect.y1;
	vx[0].color = ncolor;

	vx[1].position.x = m_rect.x2;
	vx[1].position.y = m_rect.y1;
	vx[1].color = ncolor;

	vx[2].position.x = m_rect.x2;
	vx[2].position.y = m_rect.y2;
	vx[2].color = ncolor;
	
	vx[3].position.x = m_rect.x1;
	vx[3].position.y = m_rect.y2;
	vx[3].color = ncolor;

	static int indices[6] = {0, 1, 2, 2, 3, 0};
	context->RenderGeometry(nullptr, vx, 4, indices, 6);
}

