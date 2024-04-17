//◦ EggEngine ◦
#pragma once
#include <memory>
#include <vector>
#include <functional>

#include "ComicsSlide.h"

#include "scene/GameScene.h"

#include "engine/CoreSDL.h"
#include "engine/assets/eAssetResources.h"
#include "engine/render/eSpriteBatch.h"
#include "engine/gui/label/eLabel.h"

namespace Comics
{

	//Коимксы
	class AComicsScene : public Game::AGameScene
	{
	public:
		using Super 	= Game::AGameScene;
		using UPtr		= std::unique_ptr<AComicsScene>;
		using Ptr		= std::shared_ptr<AComicsScene>;
		using WeakPtr	= std::weak_ptr<AComicsScene>;

	public:
		AComicsScene();
		virtual ~AComicsScene();

	public:
		bool Init(const Engine::Assets::EAssetResources::Ptr &assets, const std::string &fileName); //Инциализация
	
	public:
		void Done() override;	//Завершение игры
		void Input(const Engine::Input::TControls &controls) override;
		void Update(const double dt) override; //Игровой цикл
		void Render(const Engine::Render::ERenderContext::UPtr& context) override; //Отрисовка
		
	public:
		std::function<void()> onCompleted = {};
	
	private:
		void NextSlide();
		
	private:
		Engine::Assets::EAssetResources::Ptr 	m_assets;
		Engine::Render::ESpriteBatch::UPtr		m_spriteBatch;
		
		std::vector<AComicsSlide::Ptr> m_slides;
		size_t m_currentSlide = {};
		bool m_tap = {};
		bool m_key = {};
		
		bool m_firstActivate = { false };
		
	};

}
