//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>


#include "objects/FactoryObject.h"

namespace Game::Components
{

	//Фабрика создания компанента который следит за следом
	class AFactoryTrailEmitter : public AFactory
	{
	public:
		void Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop) override;
		
	};

}
