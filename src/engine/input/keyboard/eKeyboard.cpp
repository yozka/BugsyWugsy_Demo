//◦ EggEngine ◦
#include "eKeyboard.h"
#include "engine/debug/eAssert.h"

using namespace Engine::Input;


void EKeyboard::EventInput(SDL_Event& event)
{
	/*
	if (event.type == SDL_WINDOWEVENT) {
		if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
			m_keysEvent = {};
			
			return;
		}
		return;
	}*/
	
	if (event.type != SDL_KEYDOWN && event.type != SDL_KEYUP) {
		return;
	}
	if (EventKey(event, m_keysEvent.up, 	SDLK_UP))		return;
	if (EventKey(event, m_keysEvent.down,	SDLK_DOWN))		return;
	if (EventKey(event, m_keysEvent.left,	SDLK_LEFT))		return;
	if (EventKey(event, m_keysEvent.right,	SDLK_RIGHT))	return;
	if (EventKey(event, m_keysEvent.jump,	SDLK_SPACE))	return;
	if (EventKey(event, m_keysEvent.action,	SDLK_RETURN))	return;
	if (EventKey(event, m_keysEvent.menu,	SDLK_ESCAPE))	return;
}


bool EKeyboard::EventKey(const SDL_Event& event, TKey &keynote, SDL_Keycode sym)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == sym) {
			keynote.pressed = true;
			m_activeEvent = true;
			return true;
		}
	}

	if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == sym) {
			keynote.released = true;
			m_activeEvent = true;
			return true;
		}
	}
	
	return false;
}


void EKeyboard::Update(const float /*dt*/)
{
	m_active = m_activeEvent;
	if (m_active) {
		m_keys = m_keysEvent;
		m_keysEvent = {};
		m_activeEvent = false;
	}
}


bool EKeyboard::HasControls(TControls &controls) const
{
	if (!m_active) return false;
	ControlKey(m_keys.up,		controls.up);
	ControlKey(m_keys.down,		controls.down);
	ControlKey(m_keys.left,		controls.left);
	ControlKey(m_keys.right,	controls.right);
	ControlKey(m_keys.jump,		controls.jump);
	ControlKey(m_keys.action,	controls.action);
	ControlKey(m_keys.menu,		controls.menu);
	return true;
}

void EKeyboard::ControlKey(const TKey &keynote, TKey &key) const
{
	if (keynote.pressed)	key.pressed = true;
	if (keynote.released)	key.released = true;
}
