//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "engine/common/eRect.h"
#include "components/ComponentUpdater.h"

#include "components/grid/ComponentGrid.h"
#include "components/geometry/ComponentGeometry.h"
#include "components/sprite/ComponentSprite.h"
#include "components/sound/ComponentSound.h"

namespace Game::Components
{

	//Объект
	class AComponentPlayerControl : public AComponentUpdater
	{
	public:
		using UPtr		= std::unique_ptr<AComponentPlayerControl>;
		using Ptr		= std::shared_ptr<AComponentPlayerControl>;
		using WeakPtr	= std::weak_ptr<AComponentPlayerControl>;

		using SignalMoving = std::function<void(const std::vector<Engine::IPoint>&)>;
		
	public:
		void Destroy() override;
		void Update(const double dt) override;

	public:
		void SetSpeed(const float speed);
		void SetPathDepth(const int value);

	public:
		void MovingToGrid(const Engine::IPoint &pos, SignalMoving signal);
		void MovingToDirect(const Engine::IPoint &direct); //Начало движения по направлению
		
	private:
		bool InitComponents();
		void MoveStart(); //Начало движения
		bool MoveNext(); //Двигаемся к следующей точке
		void MoveCompleted(); //Конец движения
		
		
	private:
		std::vector<Engine::IPoint> m_path; //Точки прохождения пути
		SignalMoving m_signalMoving;
		
		bool 			m_moving	= { false }; 		//Начало движения
		bool 			m_next		= { false }; 		//Следующая порция данных для движения
		Engine::IPoint	m_direct	= {}; 	//Направление автодвижения
		
		int				m_pathDepth	= { 16 }; //Глубина перебора пути
		float 			m_speed		= { 1.0f };  //Скорость движения персонажа
		Engine::FPoint 	m_posStart	= {}; //Начальная позиция движения
		Engine::FPoint 	m_posEnd	= {}; //Конечная позиция движения
		float 			m_time		= {}; //текущее время движения
		
		//Кеш компонентов
		AComponentGeometry::Ptr m_geometry = {};
		AComponentSprite::Ptr m_sprite = {};
		AComponentGrid::Ptr m_grid = {};
		AComponentSound::Ptr m_sound = {};
	};

}
