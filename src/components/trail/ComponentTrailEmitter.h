//◦ EggEngine ◦
#pragma once
#include <memory>
#include <list>
#include "components/ComponentUpdater.h"
#include "components/layer/ComponentLayer.h"
#include "components/grid/ComponentGrid.h"

#include "engine/common/eRect.h"

namespace Game::Components
{

	//Компанент, который следит за движением и создает след игроков
	class AComponentTrailEmitter : public AComponentUpdater
	{
	public:
		using UPtr		= std::unique_ptr<AComponentTrailEmitter>;
		using Ptr		= std::shared_ptr<AComponentTrailEmitter>;
		using WeakPtr	= std::weak_ptr<AComponentTrailEmitter>;

	public:
		AComponentTrailEmitter();
		void Destroy() override;
		void ComponentAttached() override;
		void Update(const double dt) override;

	public:
		void SetTrailLive(const float time);
		void SetTileName(const std::string &name);
		void SetlayerName(const std::string &name);
		
	public:
		int IncLength(); //Увеличим длину хвоста
		Engine::IPoint GetTrailPosition(const int number) const;
		
	private:
		bool Init();
		void ChangePositions(const Engine::IPoint &gridStart, const Engine::IPoint &gridEnd);
		void AppendTrail(Engine::IPoint pos);
		void SetTrailAnimation(Engine::IPoint pos);
		void RemoveTrail();
		
	private:
		bool m_attached = {};
		bool m_init = {};
		
		std::string m_tileName;
		std::vector<int> m_tilesId;
		
		std::string m_layerName;
		
		//Хвост
		std::list<Engine::IPoint> m_trails;
		float m_timeRemove = {}; //Время, когда уничтожается хворт
		float m_timeTrailLive = { 10.0f }; //время жизни хвоста
		float m_timeSlow = { 1.0f }; //Замедление исчезания хвоста
		float m_timeSlowNormal = {}; //Время действия замедления
		
		int m_trailLength = { 0 }; //Длина хвоста
		 
	private:
		//кеш компанентов
		Map::ALayerTiles::Ptr 	m_layer		= {}; //Слой тайлов где находится следы
		AComponentGrid::Ptr 	m_grid		= {}; //Компанент коллизий
	};

}
