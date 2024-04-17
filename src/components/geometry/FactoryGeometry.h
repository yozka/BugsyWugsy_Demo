//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>


#include "objects/FactoryObject.h"

namespace Game::Components
{

	//Фабрика создания геометрии
	class AFactoryGeometry : public AFactory
	{
	public:
		void Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop) override;
		
	};

}
