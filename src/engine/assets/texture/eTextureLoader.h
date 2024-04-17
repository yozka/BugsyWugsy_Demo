//◦ EggEngine ◦
#pragma once
#include <string>

#include "eAssetSprite.h"
#include "engine/assets/eAssetResources.h"

namespace Engine::Assets
{

	class ETextureLoader
	{
	public:
		using Ptr = std::shared_ptr<ETextureLoader>;
		using UPtr = std::unique_ptr<ETextureLoader>;
		
	public:
		ETextureLoader(const EAssetResources::Ptr& resources);
		virtual ~ETextureLoader() = default;
	
	public:
		EAssetSprite::Ptr LoadSprite(const std::string& group, const std::string& spriteName, const std::string &fileName = "");
		bool LoadSprites(const std::string &fileName);
		bool LoadAtlas(const std::string &fileName);
		
	private:
		EAssetSprite::Ptr LoadTexture(const std::string& name, const std::string& group, const std::string &fileName);
		void AddSubTexture(const EAssetSprite::Ptr& atlas, const std::string& name, const int x, const int y, const int width, const int height);
		
	private:
		EAssetResources::Ptr m_resources = {};
		
	};

}
