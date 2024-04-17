//◦ EggEngine ◦
#include "FactoryEgg.h"
#include "engine/assets/sound/eSoundLoader.h"

using namespace Game::Components;



void AFactoryEgg::Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop)
{
	if (!prop.GetBool("AComponentEgg")) return;
	
	auto egg = obj->CreateComponent<Components::AComponentEgg>();
	egg->SetMaster(prop.GetString("Egg_master"));
	egg->SetChecken(prop.GetString("Egg_chicken"));
	
	
}
