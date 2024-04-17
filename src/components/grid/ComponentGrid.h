//◦ EggEngine ◦
#pragma once
#include <memory>
#include "components/Component.h"
#include "map/grid/GridCollision.h"

namespace Game::Components
{

	//Компанент, предоставляет доступ к grid коллизии
	class AComponentGrid : public AComponent
	{
	public:
		using UPtr		= std::unique_ptr<AComponentGrid>;
		using Ptr		= std::shared_ptr<AComponentGrid>;
		using WeakPtr	= std::weak_ptr<AComponentGrid>;

		using Path 		= Game::Map::AGrigCollision::Path;
	public:
		AComponentGrid(Game::Map::AGrigCollision::WeakPtr grid);
		void Destroy() override;
		
		bool WaveGround(const Engine::IPoint &ptStart, const Engine::IPoint &ptEnd, Path &path, const int depth = 0);
		bool HasGround(const Engine::IPoint &pos) const; //Проверка, можно ли стоять на этой точке
		bool HasWater(const Engine::IPoint &pos) const; //Проверка, можно ли стоять на этой точке
		
		void SetNone	(const Engine::IPoint &pos);
		void SetBlock	(const Engine::IPoint &pos);
		void SetPassable(const Engine::IPoint &pos);
		void SetRoad	(const Engine::IPoint &pos);
		void SetWater	(const Engine::IPoint &pos);
		
		void WaveGroundRun(const Engine::IPoint &pt);
		int GetWaveData(const Engine::IPoint &pt) const;
		
	private:
		Game::Map::AGrigCollision::WeakPtr m_grid = {};
		
	};

}
