//◦ EggEngine ◦
#include "Tileset.h"
#include "engine/debug/eAssert.h"

using namespace Game::Map;


ATileset::ATileset()
{

}


ATileset::~ATileset()
{

}


ATileset::UPtr ATileset::Create(const std::string& name,
							 const int firstgid,
							 const int tilewidth,
							 const int tileheight,
							 const int tilecount,
							 const int columns,
							 const Engine::Assets::EAssetSprite::Ptr &texture)
{
	auto tileset = std::make_unique<ATileset>();
	tileset->m_firstgid		= firstgid;
	tileset->m_tilewidth	= tilewidth;
	tileset->m_tileheight	= tileheight;
	tileset->m_tilecount	= tilecount;
	tileset->m_columns		= columns;
	tileset->m_texture		= texture;
	tileset->m_name			= name;
	return tileset;
}

void ATileset::Destroy()
{
	m_firstgid		= {};
	m_tilewidth		= {};
	m_tileheight	= {};
	m_tilecount		= {};
	m_columns		= {};
	m_texture 		= {};
	m_name.clear();
}

bool ATileset::Compare(const int tileId) const
{
	return tileId >= m_firstgid && tileId < (m_firstgid + m_tilecount);
}

SDL_Rect ATileset::GetSource(const int tileId) const
{
	const int id = tileId - m_firstgid;
	sassert(id > 0 && id < m_tilecount);
	
	const int x = id % m_columns;
	const int y = id / m_columns;
	SDL_Rect rect;
	rect.x = x * m_tilewidth;
	rect.y = y * m_tileheight;
	rect.w = m_tilewidth;
	rect.h = m_tileheight;
	return rect;
}


void ATileset::AppendTile(const std::string &name, const int tileId)
{
	m_tiles[name] = tileId;
}

int ATileset::FindTile(const std::string &name) const
{
	const auto it = m_tiles.find(name);
	if (it != m_tiles.end()) {
		return it->second + m_firstgid;
	}
	return 0;
}
