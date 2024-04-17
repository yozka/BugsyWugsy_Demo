//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "ComponentFinal.h"
#include "objects/FactoryObject.h"


namespace Game::Components
{

	//Фабрика создания механики яйца
	class AFactoryFinal : public AFactory
	{
	public:
		void Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop) override;
	
	private:
		
	};

}
