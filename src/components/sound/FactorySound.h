//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "ComponentSound.h"

#include "objects/FactoryObject.h"
#include "engine/assets/eAssetResources.h"

namespace Game::Components
{

	//Фабрика создания музыки
	class AFactorySound : public AFactory
	{
	public:
		AFactorySound(const Engine::Assets::EAssetResources::Ptr &assets);
		void Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop) override;
		
	private:
		Engine::Assets::EAssetResources::Ptr m_assets;
		
	};

}
