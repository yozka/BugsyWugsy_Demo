//◦ EggEngine ◦
#pragma once
#include <string>
#include <SDL.h>
#include "engine/render/eRenderContext.h"

namespace Game
{
	class AScenesController;

	//Базовая игровая сцена
	//В которой находится все
	class AGameScene
	{
	public:
		using UPtr		= std::unique_ptr<AGameScene>;
		using Ptr		= std::shared_ptr<AGameScene>;
		using WeakPtr	= std::weak_ptr<AGameScene>;

	public:
		AGameScene();
		virtual ~AGameScene();
		
		
	public:
		virtual bool Init() = 0; 	//Инциализация
		virtual void Done() = 0;	//Завершение игры
		virtual void EventInput(SDL_Event &event) = 0;
		virtual void Update(const double dt) = 0; //Игровой цикл
		virtual void Render(const Engine::Render::ERenderContext::UPtr& context) = 0; //Отрисовка


	public:
		void SetController(AScenesController *controller);
		AScenesController* GetController() { return m_controller; }
		
	private:
		AScenesController* m_controller = {};
		
	};

}
