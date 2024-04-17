//◦ EggEngine ◦
#include "FactoryFinal.h"
#include "engine/assets/sound/eSoundLoader.h"

using namespace Game::Components;



void AFactoryFinal::Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop)
{
	if (!prop.GetBool("AComponentFinal")) return;
	
	auto fin = obj->CreateComponent<Components::AComponentFinal>();

	fin->SetWinEgg(prop.GetInteger("Final_WinEgg"));
	
}
