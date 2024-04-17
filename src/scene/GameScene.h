//◦ EggEngine ◦
#pragma once
#include <string>

#include "engine/CoreSDL.h"
#include "engine/render/eRenderContext.h"
#include "engine/input/eControls.h"

namespace Game
{

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
		virtual void Done() = 0;	//Завершение игры
		virtual void Input(const Engine::Input::TControls &controls) = 0;
		virtual void Update(const double dt) = 0; //Игровой цикл
		virtual void Render(const Engine::Render::ERenderContext::UPtr& context) = 0; //Отрисовка

		
	};

}
