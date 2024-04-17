//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "engine/common/eRect.h"


namespace Game::Components
{

	//Компанент для обновления данных
	class AComponentUpdater : public AComponent
	{
	public:
		using UPtr		= std::unique_ptr<AComponentUpdater>;
		using Ptr		= std::shared_ptr<AComponentUpdater>;
		using WeakPtr	= std::weak_ptr<AComponentUpdater>;

	public:
		virtual void Update(const double dt) = 0;
		
		
	};

}
