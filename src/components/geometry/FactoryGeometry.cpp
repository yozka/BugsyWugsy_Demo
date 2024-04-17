//◦ EggEngine ◦
#include "FactoryGeometry.h"
#include "ComponentGeometry.h"

using namespace Game::Components;


void AFactoryGeometry::Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop)
{
	if (!prop.GetBool("AComponentGeometry")) return;

	const Engine::FPoint position 	= { prop.GetFloat("x", prop.GetFloat("X")), prop.GetFloat("y", prop.GetFloat("Y"))};
	const Engine::FPoint size 		= { prop.GetFloat("width", prop.GetFloat("Width")), prop.GetFloat("height", prop.GetFloat("Height"))};
	const int tilewidth 			= prop.GetInteger("map_tilewidth");
	const int tileheight 			= prop.GetInteger("map_tileheight");
	
	auto geometry = obj->CreateComponent<Components::AComponentGeometry>();
	geometry->SetPosition(position);
	geometry->SetSize(size);
	geometry->SetTileSize(tilewidth, tileheight);

}
