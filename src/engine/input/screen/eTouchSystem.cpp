//◦ EggEngine ◦
#include "eTouchSystem.h"
#include "engine/CoreSDL.h"

using namespace Engine::Input;

void ETouchSystem::Init(const int width, const int height)
{
	m_layout = true;
	m_width = width;
	m_height = height;
}


bool ETouchSystem::EventInputDown(SDL_Event& event, Engine::Input::SYSTouch& touch)
{
	if (!m_layout) return false;
	
#ifdef EN_DESKTOP
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		touch.id = 0;
		touch.pos.x = event.button.x;
		touch.pos.y = event.button.y;
		return true;
	}
#endif // EN_DESKTOP

#ifdef EN_MOBILE
	if (event.type == SDL_FINGERDOWN) {
		touch.id = event.tfinger.fingerId;
		touch.pos.x = m_width * event.tfinger.x;
		touch.pos.y = m_height * event.tfinger.y;
		return true;
	}
#endif // EM_MOBILE


	return false;
}


bool ETouchSystem::EventInputMove(SDL_Event& event, Engine::Input::SYSTouch& touch)
{
	if (!m_layout) return false;
#ifdef EN_DESKTOP
	if (event.type == SDL_MOUSEMOTION) {
		touch.id = 0;
		touch.pos.x = event.motion.x;
		touch.pos.y = event.motion.y;
		return true;
	}
#endif // EN_DESKTOP

#ifdef EN_MOBILE
	if (event.type == SDL_FINGERMOTION) {
		touch.id = event.tfinger.fingerId;
		touch.pos.x = m_width * event.tfinger.x;
		touch.pos.y = m_height * event.tfinger.y;
		return true;
	}
#endif // EM_MOBILE
	
	return false;
}


bool ETouchSystem::EventInputUp(SDL_Event& event, Engine::Input::SYSTouch& touch)
{
	if (!m_layout) return false;
#ifdef EN_DESKTOP
	if (event.type == SDL_MOUSEBUTTONUP) {
		touch.id = 0;
		touch.pos.x = event.button.x;
		touch.pos.y = event.button.y;
		return true;
	}
#endif // EN_DESKTOP

#ifdef EN_MOBILE
	if (event.type == SDL_FINGERUP) {
		touch.id = event.tfinger.fingerId;
		touch.pos.x = m_width * event.tfinger.x;
		touch.pos.y = m_height * event.tfinger.y;
		return true;
	}
#endif // EM_MOBILE
	
	return false;
}

