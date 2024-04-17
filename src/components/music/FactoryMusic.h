//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "ComponentMusic.h"

#include "objects/FactoryObject.h"
#include "engine/assets/eAssetResources.h"

namespace Game::Components
{

	//Фабрика создания музыки
	class AFactoryMusic : public AFactory
	{
	public:
		AFactoryMusic(const Engine::Assets::EAssetResources::Ptr &assets);
		void Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop) override;
		
	private:
		Engine::Assets::EAssetResources::Ptr m_assets;
		
	};

}
