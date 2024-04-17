//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "engine/common/eRect.h"
#include "engine/render/eSpriteBatch.h"

namespace Game::Components
{

	//Компанент для отрисовки на карте
	class AComponentRendering : public AComponent
	{
	public:
		using UPtr		= std::unique_ptr<AComponentRendering>;
		using Ptr		= std::shared_ptr<AComponentRendering>;
		using WeakPtr	= std::weak_ptr<AComponentRendering>;

	public:
		virtual Engine::FRect Geometry() const = 0; //Возвратить геометрию игрового объекта
		
		virtual void Render(const Engine::Render::ESpriteBatch::UPtr &context,
							const Engine::IPoint& pos,
							const float scale) = 0;
		
		
	};

}
