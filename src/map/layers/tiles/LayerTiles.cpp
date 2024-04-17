//◦ EggEngine ◦
#include "LayerTiles.h"
#include "engine/debug/eAssert.h"


using namespace Game::Map;


ALayerTiles::ALayerTiles(const std::string& name, const int width, const int height)
	:
		m_name(name),
		m_width(width),
		m_height(height)
{
	m_data.resize(width * height);
}


ALayerTiles::~ALayerTiles()
{

}


void ALayerTiles::Destroy()
{
	m_width = {};
	m_height = {};
	m_name.clear();
	m_data.clear();
}

void ALayerTiles::Update(const double dt)
{
	m_time += dt;
}

void ALayerTiles::SetTileId(const Engine::IPoint &pos, const int tileId)
{
	SetTileId(pos.x, pos.y, tileId);
}

void ALayerTiles::SetTileId(const int x, const int y, const int tileId)
{
	sassert(x >= 0 && x < m_width);
	sassert(y >= 0 && y < m_height);
	auto &data = m_data[x + y * m_width];
	//data.tile = { tileId };
	data = { tileId };
}

void ALayerTiles::AppendAnimation(const int x, const int y, const int tileId, const float time)
{
	sassert(x >= 0 && x < m_width);
	sassert(y >= 0 && y < m_height);
	auto &data = m_data[x + y * m_width];
	if (data.tile.tileId == 0) {
		data.tile = { tileId };
	}
	data.animation = true;
	data.animationTiles.push_back({tileId, time});
}

ATileData& ALayerTiles::Tile(const int x, const int y)
{
	auto &data = m_data[x + y * m_width];
	if (data.animation) {
		if (data.time < m_time) {
			data.animationIndex++;
			if (data.animationIndex >= data.animationTiles.size()) {
				data.animationIndex = 0;
			}
			data.time = m_time + data.animationTiles[data.animationIndex].time;
		}
		sassert(data.animationIndex < data.animationTiles.size());
		return data.animationTiles[data.animationIndex];
	}
	return data.tile;
}
