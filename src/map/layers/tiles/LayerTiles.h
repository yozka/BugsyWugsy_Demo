//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>

#include "map/layers/Layer.h"
#include "TileData.h"
#include "engine/common/eRect.h"

namespace Game::Map
{

	//Спрайты тайлы для игровой карты
	class ALayerTiles : public ALayer
	{
	public:
		using UPtr		= std::unique_ptr<ALayerTiles>;
		using Ptr		= std::shared_ptr<ALayerTiles>;
		using WeakPtr	= std::weak_ptr<ALayerTiles>;

	public:
		ALayerTiles(const std::string& name, const int width, const int height);
		~ALayerTiles() override;
		
	public:
		void Destroy();
		void Update(const double dt);
		
		std::string Name() const { return m_name; }
		
	public:
		void SetTileId(const Engine::IPoint &pos, const int tileId);
		void SetTileId(const int x, const int y, const int tileId);
		void AppendAnimation(const int x, const int y, const int tileId, const float time);
		
		ATileData& Tile(const int x, const int y);
		
	private:
		std::string m_name;
		int m_width		= {};
		int m_height	= {};

		std::vector<ATileInfo> m_data;

		float m_time = {}; //текущее время
		
	};

}
