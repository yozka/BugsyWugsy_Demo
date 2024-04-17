//◦ EggEngine ◦
#pragma once
#include <string>
#include <vector>
#include <memory>

#include "eScreenKey.h"
#include "engine/input/eInputController.h"
#include "eTouchSystem.h"

#include "engine/CoreSDL.h"
#include "engine/render/eRenderContext.h"

namespace Engine::Input
{

	// Виртуальная экранная геймпад
	class EScreenGamepad : public EInputController
	{
	public:
		using Ptr = std::shared_ptr<EScreenGamepad>;
		using WeakPtr = std::weak_ptr<EScreenGamepad>;

	public:
		EScreenGamepad();

	public:
		void EventInput(SDL_Event& event) override;
		void Update(const float dt) override;
		void Render(const Engine::Render::ERenderContext::UPtr& context) override;
		bool HasControls(TControls &controls) const override;
		
	private:
		void CreateKeys();
		EScreenKey::Ptr FindKey(const std::string &name) const;

		
	private:
		ETouchSystem m_touchScreen;
		std::vector<EScreenKey::Ptr> m_keys;
		
		TTouch m_touch;
		TTouch m_touchEvent;
		
		int64_t m_touchId = {-1};
		IPoint m_touchPos;
		bool m_active = {};
		bool m_activeEvent = {};

	};

}
