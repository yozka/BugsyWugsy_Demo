//◦ EggEngine ◦
#include "eControllers.h"

using namespace Engine::Input;



void EControllers::EventInput(SDL_Event& event)
{
	for (const auto &controller : m_controllers) {
		controller->EventInput(event);
	}
}


void EControllers::Update(const float dt)
{
	for (const auto &controller : m_controllers) {
		controller->Update(dt);
	}
}


void EControllers::Render(const Engine::Render::ERenderContext::UPtr& context)
{
	for (const auto &controller : m_controllers) {
		controller->Render(context);
	}
}


bool EControllers::HasControls(TControls &controls) const
{
	bool active = {};
	for (const auto &controller : m_controllers) {
		active |= controller->HasControls(controls);
	}
	return active;
}


void EControllers::Append(EInputController::UPtr controller)
{
	m_controllers.emplace_back(std::move(controller));
}
