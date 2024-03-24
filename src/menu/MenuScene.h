//◦ EggEngine ◦
#pragma once
#include <string>
#include <SDL.h>
#include "scene/GameScene.h"

namespace Game
{

	//Игровое меню
	class AMenuScene : public AGameScene
	{
	public:
		using Super 	= AGameScene;
		using UPtr		= std::unique_ptr<AMenuScene>;
		using Ptr		= std::shared_ptr<AMenuScene>;
		using WeakPtr	= std::weak_ptr<AMenuScene>;

	public:
		AMenuScene();
		~AMenuScene() override;
		
	public:
		bool Init() override; 	//Инциализация
		void Done() override;	//Завершение игры
		void EventInput(SDL_Event &event) override;
		void Update(const double dt) override; //Игровой цикл
		void Render(const Engine::Render::ERenderContext::UPtr& context) override; //Отрисовка

	private:
		SDL_Texture* m_texture = {};
		SDL_Surface* m_surface = {};
	};

}
