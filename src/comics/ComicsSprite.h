//◦ EggEngine ◦
#pragma once
#include <memory>

#include "ComicsWidget.h"
#include "engine/CoreSDL.h"
#include "engine/assets/texture/eAssetSprite.h"
#include "engine/common/eRect.h"

namespace Comics
{

	//Картинка
	class AComicsSprite : public AComicsWidget
	{
	public:
		using Super 	= AComicsWidget;
		using UPtr		= std::unique_ptr<AComicsSprite>;
		using Ptr		= std::shared_ptr<AComicsSprite>;
		using WeakPtr	= std::weak_ptr<AComicsSprite>;

	public:
		void Load(Engine::Xml::Node *root, const Engine::Assets::EAssetResources::Ptr &assets) override;
		void Render(const Engine::Render::ESpriteBatch::UPtr& context) override;
		
	private:
		Engine::Assets::EAssetSprite::Ptr m_sprite;
		SDL_FRect m_dest;
		
	};

}
