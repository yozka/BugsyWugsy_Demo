//◦ EggEngine ◦
#include "ComponentLayer.h"
#include "components/ComponentRendering.h"

using namespace Game::Components;

AComponentLayer::AComponentLayer(Game::Map::VLayers::WeakPtr layers, Game::Map::ALayerRenderObjects::WeakPtr layer, Game::Map::AGameLogic::WeakPtr logic)
	:
		m_layers(std::move(layers)),
		m_currentLayer(std::move(layer)),
		m_logic(std::move(logic))
{
	
}


void AComponentLayer::Destroy()
{
	m_currentLayer = {};
	m_logic = {};
}



void AComponentLayer::AppendObject(const AGameObject::Ptr &obj)
{
	if (obj->GetComponent<AComponentRendering>()) {
		if (auto ptr = m_currentLayer.lock()) {
			ptr->Append(obj);
		}
	}
	
	if (auto ptr = m_logic.lock()) {
		ptr->Append(obj);
	}
}


Game::Map::ALayerTiles::Ptr AComponentLayer::FindLayerTiles(const std::string& name) const
{
	if (auto layers = m_layers.lock()) {
		return layers->FindLayerTiles(name);
	}
	return {};
}


Game::AGameObject::Ptr AComponentLayer::FindObject(const std::string &name) const
{
	if (auto layer = m_currentLayer.lock()) {
		if (auto obj = layer->FindObject(name)) {
			return obj;
		}
	}
	
	if (auto ptr = m_logic.lock()) {
		if (auto obj = ptr->FindObject(name)) {
			return obj;
		}
	}
	return {};
}
