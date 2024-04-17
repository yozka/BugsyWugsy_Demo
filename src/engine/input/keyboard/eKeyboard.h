//◦ EggEngine ◦
#pragma once
#include <string>
#include <vector>
#include <memory>

#include "engine/CoreSDL.h"
#include "engine/input/eInputController.h"

namespace Engine::Input
{

	// Клавиатура
	class EKeyboard : public EInputController
	{
	public:
		using Ptr = std::shared_ptr<EKeyboard>;
		using WeakPtr = std::weak_ptr<EKeyboard>;

	public:
		void EventInput(SDL_Event& event) override;
		void Update(const float dt) override;
		void Render(const Engine::Render::ERenderContext::UPtr& context) override {}
		bool HasControls(TControls &controls) const override;
		
	private:
		bool EventKey(const SDL_Event& event, TKey &keynote, SDL_Keycode sym);
		void ControlKey(const TKey &keynote, TKey &key) const;
		
	private:
		TKeyControls m_keys;
		TKeyControls m_keysEvent;
		
		bool m_active = {};
		bool m_activeEvent = {};
	};

}
