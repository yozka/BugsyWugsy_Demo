//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>

#include "scene/GameScene.h"

#include "engine/CoreSDL.h"
#include "engine/render/eRenderContext.h"
#include "engine/assets/eAssetResources.h"
#include "engine/input/eInputController.h"

namespace Game
{


	class AApplicationLogic
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
		
	protected:
		void PushScene(const AGameScene::Ptr &scene);
		void PopScene();
		
	private:
		void InitInput();
		
	private:
		void OnStartComics();
		void OnStartGame();
		void OnGameWin();
		void OnGameLose();
		void OnMenu();
		
	private:
		AGameScene::Ptr 						m_scene; 	//Текущая сцена
		std::vector<AGameScene::Ptr> 			m_scenes; 	//Список всех сцен
		Engine::Assets::EAssetResources::Ptr 	m_assets; 	//Ресурсы игры
		Engine::Input::EInputController::Ptr	m_input; 	//Подсистема ввода

	};

}
