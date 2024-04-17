//◦ EggEngine ◦
#pragma once
#include <memory>
#include <vector>
#include "components/Component.h"
#include "map/tileset/Tileset.h"

namespace Game::Components
{

	//Компанент, предоставляет доступ тайлсетам
	class AComponentTilesets : public AComponent
	{
	public:
		using UPtr		= std::unique_ptr<AComponentTilesets>;
		using Ptr		= std::shared_ptr<AComponentTilesets>;
		using WeakPtr	= std::weak_ptr<AComponentTilesets>;

	public:
		AComponentTilesets(Game::Map::ATilesets::WeakPtr tilesets);
		void Destroy() override;

	public:
		int FindTile(const std::string &name) const;
		std::vector<int> FindTiles(const std::string &name) const;
		
	private:
		Game::Map::ATilesets::WeakPtr m_tilesets = {};
		
	};

}
