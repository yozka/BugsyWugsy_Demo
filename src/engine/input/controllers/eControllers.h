//◦ EggEngine ◦
#pragma once
#include <memory>
#include <vector>
#include "engine/input/eInputController.h"

namespace Engine::Input
{

	// Объеденяющий контроллер
	class EControllers : public EInputController
	{
	public:
		using Ptr = std::shared_ptr<EControllers>;
		using WeakPtr = std::weak_ptr<EControllers>;

	public:
		void EventInput(SDL_Event& event) override;
		void Update(const float dt) override;
		void Render(const Engine::Render::ERenderContext::UPtr& context) override;
		bool HasControls(TControls &controls) const override;
		
	public:
		void Append(EInputController::UPtr controller);
		
	private:
		std::vector<EInputController::UPtr> m_controllers;

	};

}
