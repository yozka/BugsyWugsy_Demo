//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <variant>

#include "render/LayerRenderObjects.h"
#include "tiles/LayerTiles.h"

namespace Game::Map
{
	using VLayer 		= std::variant<ALayerTiles::Ptr, ALayerRenderObjects::Ptr>;

	class VLayers : public std::vector<VLayer>
	{
	public:
		using UPtr		= std::unique_ptr<VLayers>;
		using Ptr		= std::shared_ptr<VLayers>;
		using WeakPtr	= std::weak_ptr<VLayers>;
		
		
		ALayerTiles::Ptr FindLayerTiles(const std::string& name) const
		{
			for (auto& layer : *this) {
				if (std::holds_alternative<ALayerTiles::Ptr>(layer)) {
					const auto ptr = std::get<ALayerTiles::Ptr>(layer);
					if (ptr->Name() == name) {
						return ptr;
					}
				}
			}
			return {};
		}
	};

}
