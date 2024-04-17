//◦ EggEngine ◦
#pragma once
#include <string>
#include <functional>

#include "scene/GameScene.h"
#include "map/GameMap.h"
#include "map/camera/Camera.h"

#include "CameraMoving.h"

#include "engine/CoreSDL.h"
#include "engine/assets/eAssetResources.h"
#include "engine/render/eSpriteBatch.h"
#include "engine/gui/button/eButton.h"
#include "engine/gui/button/eIconButton.h"

namespace Game
{

	//Игровая сцена
	class APlaybleScene : public AGameScene
	{
	public:
		using Super 	= AGameScene;
		using UPtr		= std::unique_ptr<APlaybleScene>;
		using Ptr		= std::shared_ptr<APlaybleScene>;
		using WeakPtr	= std::weak_ptr<APlaybleScene>;

	public:
		APlaybleScene();
		~APlaybleScene() override;
		
	public:
		std::function<void()> onGameWin = {};
		std::function<void()> onGameLose = {};
		
	public:
		bool Init(const Engine::Assets::EAssetResources::Ptr &assets); //Инциализация
		
	public:
		void Done() override;	//Завершение игры
		void Input(const Engine::Input::TControls &controls) override;
		void Update(const double dt) override; //Игровой цикл
		void Render(const Engine::Render::ERenderContext::UPtr& context) override; //Отрисовка

	private:
		void GameWin();
		void GameLose();
		
	private:
		Engine::Assets::EAssetResources::Ptr	m_assets;
		Engine::Render::ESpriteBatch::UPtr		m_spriteBatch;
		
		Map::AGameMap::UPtr 		m_map;
		Map::ACamera::Ptr 			m_camera;
		Engine::GUI::EWidget::Ptr	m_control;
		
		ACameraMoving				m_cameraMoving;
		
		bool m_active = { true };
		bool m_start = { false };
		bool m_win = { false };
		bool m_lose = { false };
		
		
		Engine::GUI::EIconButton m_buttonCamera;
		
	};

}
