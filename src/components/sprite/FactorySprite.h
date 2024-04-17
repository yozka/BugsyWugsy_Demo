//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "ComponentSprite.h"

#include "objects/FactoryObject.h"
#include "engine/assets/eAssetResources.h"

namespace Game::Components
{

	//Фабрика создания геометрии
	class AFactorySprite : public AFactory
	{
	public:
		AFactorySprite(const Engine::Assets::EAssetResources::Ptr &assets);
		void Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop) override;
		
	private:
		Engine::Assets::EAssetResources::Ptr m_assets;
		
	};

}
