//◦ EggEngine ◦
#pragma once
#include <string>
#include <functional>

#include "scene/GameScene.h"

#include "engine/CoreSDL.h"
#include "engine/assets/eAssetResources.h"
#include "engine/render/eSpriteBatch.h"
#include "engine/gui/label/eLabel.h"

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
		bool Init(const Engine::Assets::EAssetResources::Ptr &assets); //Инциализация
	
	public:
		void Done() override;	//Завершение игры
		void Input(const Engine::Input::TControls &controls) override;
		void Update(const double dt) override; //Игровой цикл
		void Render(const Engine::Render::ERenderContext::UPtr& context) override; //Отрисовка

	public:
		std::function<void()> onStart = {};
		
	private:
		Engine::Assets::EAssetResources::Ptr 	m_assets;
		Engine::Render::ESpriteBatch::UPtr		m_spriteBatch;
		
		float m_bugX = {50};
		float m_bugY = {50};
		float m_movingX = {};
		float m_movingY = {};
		
		int m_start = { 2 };
		
		Engine::GUI::ELabel m_caption;
	};

}
