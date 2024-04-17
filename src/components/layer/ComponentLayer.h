//◦ EggEngine ◦
#pragma once
#include <memory>
#include "components/Component.h"
#include "map/layers/Layers.h"
#include "map/logic/GameLogic.h"

namespace Game::Components
{

	//Компанент, предоставляет доступ к слою где находятся объекты
	class AComponentLayer : public AComponent
	{
	public:
		using UPtr		= std::unique_ptr<AComponentLayer>;
		using Ptr		= std::shared_ptr<AComponentLayer>;
		using WeakPtr	= std::weak_ptr<AComponentLayer>;

	public:
		AComponentLayer(Game::Map::VLayers::WeakPtr layers, Game::Map::ALayerRenderObjects::WeakPtr layer, Game::Map::AGameLogic::WeakPtr logic);
		void Destroy() override;

	public:
		void AppendObject(const AGameObject::Ptr &obj);
		Game::Map::ALayerTiles::Ptr FindLayerTiles(const std::string& name) const;
		AGameObject::Ptr FindObject(const std::string &name) const;
		
		
		template<typename T>
		std::vector<std::shared_ptr<T>> GetComponents() const
		{
			if (auto logic = m_logic.lock()) {
				return logic->GetComponents<T>();
			}
			return {};
		}
		
	private:
		Game::Map::ALayerRenderObjects::WeakPtr m_currentLayer = {};
		Game::Map::AGameLogic::WeakPtr m_logic = {};
		Game::Map::VLayers::WeakPtr m_layers = {};
		
	};

}
