//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <map>


#include "components/ComponentUpdater.h"
#include "components/geometry/ComponentGeometry.h"
#include "components/trail/ComponentTrailEmitter.h"

namespace Game::Components
{

	//Компанент реализцет яйцо
	class AComponentEgg : public AComponentUpdater
	{
	public:
		using UPtr		= std::unique_ptr<AComponentEgg>;
		using Ptr		= std::shared_ptr<AComponentEgg>;
		using WeakPtr	= std::weak_ptr<AComponentEgg>;

	public:
		AComponentEgg();
		~AComponentEgg() override;
		
	public:
		void Start() override;
		void Destroy() override;
		void Update(const double dt) override;
		
	public:
		void SetMaster(const std::string &name);
		void SetChecken(const std::string &name);
		
		bool IsCollect() const { return m_collect; }
		
	private:
		void CollectEgg(); //Собрали яйцо
		
	private:
		std::string m_masterName;
		std::string m_checkenName;
		
		float m_timeUpdate = {};
		bool m_collect = { false };
		
		bool m_movingTrail = { false }; //Движение в хвосте
		int m_trailPosition = { -1 }; //Позиция в хвосте
		
		bool m_moving 				= { false }; //Простое движение
		Engine::FPoint 	m_posStart	= {}; //Начальная позиция движения
		Engine::FPoint 	m_posEnd	= {}; //Конечная позиция движения
		float 			m_time		= {}; //текущее время движения
		float 			m_speed		= { 0.5f };
		//закеширован
		AGameObject::Ptr m_master = {};
		AComponentGeometry::Ptr m_masterGeometry = {};
		AComponentTrailEmitter::Ptr m_masterTrail = {};
		AComponentGeometry::Ptr m_geometry = {};
	};

}
