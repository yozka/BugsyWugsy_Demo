//◦ EggEngine ◦
#pragma once
#include <memory>
#include <vector>
#include "ComicsWidget.h"

#include "engine/xml/eTinyxml.h"
#include "engine/CoreSDL.h"
#include "engine/assets/sound/eAssetMusic.h"
#include "engine/assets/sound/eAssetSample.h"

namespace Comics
{

	//Один слайд комикса
	class AComicsSlide
	{
	public:
		using UPtr		= std::unique_ptr<AComicsSlide>;
		using Ptr		= std::shared_ptr<AComicsSlide>;
		using WeakPtr	= std::weak_ptr<AComicsSlide>;

	public:
		void Load(Engine::Xml::Node *root, const Engine::Assets::EAssetResources::Ptr &assets);
		void Render(const Engine::Render::ESpriteBatch::UPtr& context);
	
		void Activate();
		
	private:
		void LoadText(Engine::Xml::Node *node, const Engine::Assets::EAssetResources::Ptr &assets);
		void LoadSprite(Engine::Xml::Node *node, const Engine::Assets::EAssetResources::Ptr &assets);
		
	private:
		std::vector<AComicsWidget::Ptr> m_widgets;
		SDL_Color m_color;
		bool m_drawColor = {true};
		
		Engine::Assets::EAssetMusic::Ptr m_music = {};
		bool m_loop = { false };
		int m_fade = { 500 };
		
		Engine::Assets::EAssetSample::Ptr m_sample = {};
	};

}
