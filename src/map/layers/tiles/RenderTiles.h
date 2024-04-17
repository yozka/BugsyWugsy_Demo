//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>

#include "LayerTiles.h"
#include "TileData.h"
#include "map/tileset/Tileset.h"
#include "map/camera/Camera.h"

#include "engine/CoreSDL.h"
#include "engine/common/eV2.h"
#include "engine/render/eSpriteBatch.h"

namespace Game::Map
{

	//Отрисовка тайлов
	class ARenderTiles
	{
	public:
		ARenderTiles(const int width, const int height, const int tilewidth, const int tileheight, const std::vector<ATileset::UPtr> &tilesets);
		virtual ~ARenderTiles();
		
	public:
		void Render(const ALayerTiles::Ptr &layer,
					const Engine::Render::ESpriteBatch::UPtr &context,
					const ACamera::Ptr &camera);
		
	private:
		void MountTile(ATileData &tile);
		
	private:
		//Размер карты в тайлах
		const int m_width = {};
		const int m_height = {};
		
		//Размерность тайлов
		const int m_tilewidth = {};
		const int m_tileheight = {};
		
		//Тайлсеты
		const std::vector<ATileset::UPtr> &m_tilesets;
	};

}
