//◦ EggEngine ◦
#include "RenderTiles.h"
#include "engine/debug/eAssert.h"


using namespace Game::Map;


ARenderTiles::ARenderTiles(const int width, const int height, const int tilewidth, const int tileheight, const std::vector<ATileset::UPtr> &tilesets)
	:
		m_width(width),
		m_height(height),
		m_tilewidth(tilewidth),
		m_tileheight(tileheight),
		m_tilesets(tilesets)
		
{

}


ARenderTiles::~ARenderTiles()
{

}


void ARenderTiles::Render(const ALayerTiles::Ptr &layer,
						  const Engine::Render::ESpriteBatch::UPtr &context,
						  const ACamera::Ptr &camera)
{
	const auto vision = camera->GetVisionTiles();
	
	float screenY = vision.screenStartY;
	for(int y = vision.yBegin; y < vision.yEnd; y++) {
		int screenX = vision.screenStartX;
		screenY += vision.screentileheight;
		for(int x = vision.xBegin; x < vision.xEnd; x++) {
			screenX += vision.screentilewidth;
			auto tile = layer->Tile(x, y);
			if (tile.tileId == 0) continue;
			if (tile.tilesetIndex < 0) {
				MountTile(tile);
				sassert(tile.tilesetIndex >= 0);
				if (tile.tilesetIndex < 0) continue;
			}
			
			//наивная отрисовка
			const auto asset = m_tilesets[tile.tilesetIndex]->GetTexture();
			const auto texture = asset->MakeTexture(context);
			
			SDL_FRect dest;
			dest.x = screenX;
			dest.y = screenY;
			dest.w = vision.screentilewidth + 1;
			dest.h = vision.screentileheight + 1;
			
			context->RenderCopyF(texture, &tile.tileSource, &dest);
		}
	}
}


void ARenderTiles::MountTile(ATileData &tile)
{
	for (int index = 0; index < m_tilesets.size(); index++) {
		const auto& tilesets = m_tilesets[index];
		if (tilesets->Compare(tile.tileId)) {
			tile.tilesetIndex = index;
			tile.tileSource = tilesets->GetSource(tile.tileId);
			break;
		}
	}
}
