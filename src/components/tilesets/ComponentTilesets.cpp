//◦ EggEngine ◦
#include "ComponentTilesets.h"
#include "engine/common/eUtils.h"

using namespace Game::Components;

AComponentTilesets::AComponentTilesets(Game::Map::ATilesets::WeakPtr tilesets)
	:
		m_tilesets(std::move(tilesets))
{
	
}


void AComponentTilesets::Destroy()
{
	m_tilesets = {};
}

int AComponentTilesets::FindTile(const std::string &name) const
{
	if (auto tilesets = m_tilesets.lock()) {
		return tilesets->FindTile(name);
	}
	return 0;
}


std::vector<int> AComponentTilesets::FindTiles(const std::string &name) const
{
	std::vector<int> list;
	if (auto tilesets = m_tilesets.lock()) {
		for(auto id : Engine::Split(name, '|')) {
			int tileId = tilesets->FindTile(id);
			if (tileId > 0) {
				list.push_back(tileId);
			}
		}
	}
	return list;
}
