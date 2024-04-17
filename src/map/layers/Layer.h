//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "engine/CoreSDL.h"

namespace Game::Map
{

	//Слои данных для карты
	class ALayer
	{
	public:
		using UPtr		= std::unique_ptr<ALayer>;
		using Ptr		= std::shared_ptr<ALayer>;
		using WeakPtr	= std::weak_ptr<ALayer>;

	public:
		virtual ~ALayer() = default;
		void Destroy() {};
		
	};

}
