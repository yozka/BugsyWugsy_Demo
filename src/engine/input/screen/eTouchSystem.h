//◦ EggEngine ◦
#pragma once
#include <memory>
#include "engine/CoreSDL.h"
#include "engine/common/eV2.h"

namespace Engine::Input
{

	struct SYSTouch
	{
		int64_t id	= {}; //Индификатор нажатия
		IPoint pos = {};
	};

	class ETouchSystem
	{
	public:
		//Вспомогательные функции обоработки сообщений нажатий
		bool EventInputDown	(SDL_Event& event, SYSTouch& touch);
		bool EventInputMove	(SDL_Event& event, SYSTouch& touch);
		bool EventInputUp	(SDL_Event& event, SYSTouch& touch);
		
		bool IsValid() const { return m_layout; }
		void Init(const int width, const int height);
		
	private:
		bool m_layout = { false }; //Пересчитать размеры рендера
		int m_width = {};
		int m_height = {};
	};

}
