//◦ EggEngine ◦
#include "FactoryTrail.h"
#include "ComponentTrailEmitter.h"

using namespace Game::Components;


void  AFactoryTrailEmitter::Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop)
{
	if (!prop.GetBool("AComponentTrailEmitter")) return;

	
	auto trail = obj->CreateComponent<Components::AComponentTrailEmitter>();
	trail->SetTileName(prop.GetString("TrailEmitter_tile"));
	trail->SetlayerName(prop.GetString("TrailEmitter_layer"));
	trail->SetTrailLive(prop.GetFloat("TrailEmitter_timeLive"));
}
