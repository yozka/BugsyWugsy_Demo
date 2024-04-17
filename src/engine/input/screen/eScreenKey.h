//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <functional>


#include "engine/input/eInputController.h"
#include "eTouchSystem.h"
#include "engine/render/eRenderContext.h"
#include "engine/common/eRect.h"
#include "engine/CoreSDL.h"

namespace Engine::Input
{

	// Экранная кнопка
	class EScreenKey
	{
	public:
		using Ptr = std::shared_ptr<EScreenKey>;

	public:
		EScreenKey(const std::string &name);

	public:
		std::string GetName() const { return m_name; }
		void Unbinding();

		bool InputDown(const SYSTouch& touch);
		bool InputMove(const SYSTouch& touch);
		bool InputUp(const SYSTouch& touch);

		void Update(const float dt);
		void Render(const Engine::Render::ERenderContext::UPtr& context);

	public:
		void SetRect(const IRect &rect) { m_rect = rect; }
		void SetColor(const SDL_Color& color) { m_color = color; }
		void SetColorPush(const SDL_Color& color) { m_colorPush = color; }

	public:
		std::function<void()> onPressed = {};
		std::function<void()> onReleased = {};
		
	private:
		std::string m_name;
		IRect m_rect = {};
		SDL_Color m_color = {};
		SDL_Color m_colorPush = {};

		bool m_pushed = {};
		int64_t m_touchId = {-1};
		

	};


}
