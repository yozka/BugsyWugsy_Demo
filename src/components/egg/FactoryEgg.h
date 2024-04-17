//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "ComponentEgg.h"
#include "objects/FactoryObject.h"


namespace Game::Components
{

	//Фабрика создания механики яйца
	class AFactoryEgg : public AFactory
	{
	public:
		void Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop) override;
	
	private:
		
	};

}
