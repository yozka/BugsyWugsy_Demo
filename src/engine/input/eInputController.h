//◦ EggEngine ◦
#pragma once
#include <string>
#include <functional>
#include <memory>

#include "eControls.h"
#include "engine/CoreSDL.h"
#include "engine/render/eRenderContext.h"

namespace Engine::Input
{


	// Система управления
	class EInputController
	{
	public:
		using UPtr		= std::unique_ptr<EInputController>;
		using Ptr 		= std::shared_ptr<EInputController>;
		using WeakPtr 	= std::weak_ptr<EInputController>;

	public:
		virtual ~EInputController() = default;

	public:
		virtual void EventInput(SDL_Event& event) = 0;
		virtual void Update(const float dt) = 0;
		virtual void Render(const Engine::Render::ERenderContext::UPtr& context) = 0;
		virtual bool HasControls(TControls &controls) const = 0;
		
	};

}
