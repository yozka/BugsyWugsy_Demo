//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include "engine/common/eV2.h"
#include "engine/assets/texture/eAssetSprite.h"
#include "engine/assets/eAssetResources.h"

#include "components/ComponentRendering.h"
#include "components/geometry/ComponentGeometry.h"

namespace Game::Components
{

	//Компанент для отрисовки картинки
	class AComponentSprite : public AComponentRendering
	{
	public:
		using UPtr		= std::unique_ptr<AComponentSprite>;
		using Ptr		= std::shared_ptr<AComponentSprite>;
		using WeakPtr	= std::weak_ptr<AComponentSprite>;

	public:
		AComponentSprite();
		~AComponentSprite() override;
		
	public:
		void Destroy() override;
		Engine::FRect Geometry() const override;
		void Render(const Engine::Render::ESpriteBatch::UPtr &context,
					const Engine::IPoint& pos,
					const float scale) override;
		
	public:
		void SetAssets(Engine::Assets::EAssetResources::WeakPtr assets);
		void SetSprite(const std::string &spriteId);
		void SetSprite(const Engine::Assets::EAssetSprite::Ptr &sprite);
		void SetScale(const float value);
		
	private:
		Engine::Assets::EAssetResources::WeakPtr m_assets;
		
		float m_scale = { 1.0f };
		Engine::Assets::EAssetSprite::Ptr m_sprite;
		mutable AComponentGeometry::Ptr m_comGeometry;
	};

}
