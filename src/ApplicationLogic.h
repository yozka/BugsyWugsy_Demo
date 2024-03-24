//◦ EggEngine ◦
#pragma once
#include <SDL.h>
#include <string>
#include <memory>
#include <vector>

#include "scene/GameScene.h"
#include "scene/ScenesController.h"

#include "engine/render/eRenderContext.h"

namespace Game
{


	class AApplicationLogic : public AScenesController
	{
	public:
		using UPtr		= std::unique_ptr<AApplicationLogic>;
		using Ptr		= std::shared_ptr<AApplicationLogic>;
		using WeakPtr	= std::weak_ptr<AApplicationLogic>;

	public:
		AApplicationLogic();
		virtual ~AApplicationLogic();

	public:
		bool Init();
		void Done();	//Завершение игры
		
		void EventInput(SDL_Event &event);
		void Update(const double dt); //Игровой цикл
		void Render(const Engine::Render::ERenderContext::UPtr& context); //Отрисовка

		AGameScene::Ptr CurrentScene() const { return m_scene; }
		
	public:
		void PushScene(const AGameScene::Ptr &scene) override;
		void PopScene() override;
		
	private:
		AGameScene::Ptr m_scene; //Текущая сцена
		std::vector<AGameScene::Ptr> m_scenes; //Список всех сцен

	};

}
