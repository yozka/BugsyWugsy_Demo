//◦ EggEngine ◦
#include "GameMap.h"
#include "layers/tiles/RenderTiles.h"
#include "layers/render/RenderObjects.h"

#include "engine/debug/eAssert.h"
using namespace Game::Map;


AGameMap::AGameMap(const std::string& name, const int width, const int height, const int tilewidth, const int tileheight)
	:
	logic		(std::make_shared<AGameLogic>()),
	grid		(std::make_shared<AGrigCollision>(width, height)),
	tilesets	(std::make_shared<ATilesets>()),
	layers		(std::make_shared<VLayers>()),

	m_width		(width),
	m_height	(height),
	m_tilewidth	(tilewidth),
	m_tileheight(tileheight),
	m_name		(name)
{
}


AGameMap::~AGameMap()
{

}


void AGameMap::InitCamera(const ACamera::Ptr &camera)
{
	if (camera) {
		camera->Init(m_width, m_height, m_tilewidth, m_tileheight);
	}
}

void AGameMap::Start()
{
	for (auto& layer : *layers) {
		if (std::holds_alternative<ALayerRenderObjects::Ptr>(layer)) {
			std::get<ALayerRenderObjects::Ptr>(layer)->Start();
		}
	}
	if (logic) {
		logic->Start();
	}
}

void AGameMap::Destroy()
{
	layers->clear();
	if (logic) {
		logic->Destroy();
	}
	if (grid) {
		grid->Destroy();
	}

	if (tilesets) {
		tilesets->Destroy();
	}
	
	for (auto& layer : *layers) {
		if (std::holds_alternative<ALayerTiles::Ptr>(layer)) {
			std::get<ALayerTiles::Ptr>(layer)->Destroy();
		}
		else
		if (std::holds_alternative<ALayerRenderObjects::Ptr>(layer)) {
			std::get<ALayerRenderObjects::Ptr>(layer)->Destroy();
		}
	}
}


void AGameMap::Update(const double dt)
{
	for (const auto &layer : *layers) {
		if (std::holds_alternative<ALayerTiles::Ptr>(layer)) {
			std::get<ALayerTiles::Ptr>(layer)->Update(dt);
		}
	}
	if (logic) {
		logic->Update(dt);
	}
}


void AGameMap::Render(const Engine::Render::ESpriteBatch::UPtr& context, const ACamera::Ptr &camera)
{
	ARenderTiles 	renderTiles(m_width, m_height, m_tilewidth, m_tileheight, *tilesets);
	ARenderObjects	renderObjects(m_width, m_height, m_tilewidth, m_tileheight);
	
	for (const auto &layer : *layers) {
		if (std::holds_alternative<ALayerTiles::Ptr>(layer)) {
			renderTiles.Render(std::get<ALayerTiles::Ptr>(layer), context, camera);
		}
		else
		if (std::holds_alternative<ALayerRenderObjects::Ptr>(layer)) {
			renderObjects.Render(std::get<ALayerRenderObjects::Ptr>(layer), context, camera);
		}
	}
}


void AGameMap::SetGrid(const Engine::IPoint &pos, const EGridType type)
{
	if (grid) {
		grid->SetGrid(pos, type);
	}
}


void AGameMap::AppendObject(const AGameObject::Ptr &obj)
{
	if (logic) {
		logic->Append(obj);
	}
}


Game::AGameObject::Ptr AGameMap::FindObject(const std::string &name) const
{
	if (logic) {
		return logic->FindObject(name);
	}
	return {};
}


void AGameMap::AppendTileset(ATileset::UPtr tileset)
{
	sassert(tileset->Tilewidth() == m_tilewidth);
	sassert(tileset->Tileheight() == m_tileheight);
	tilesets->push_back(std::move(tileset));
}
 
