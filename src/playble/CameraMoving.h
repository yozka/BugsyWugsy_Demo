//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "map/camera/Camera.h"
#include "components/geometry/ComponentGeometry.h"

#include "engine/CoreSDL.h"


namespace Game
{

	//Движение камеры
	class ACameraMoving
	{
	public:
		void Done();	//Завершение игры
		void Init(const Map::ACamera::Ptr &camera, const Components::AComponentGeometry::Ptr &geometry);
		void Update(const double dt);
		void Stop();
		void Home();
		
	private:
		void ChangePositions(const Engine::IPoint &gridStart, const Engine::IPoint &gridEnd);
		
	private:
		Map::ACamera::Ptr m_camera = {};
		Components::AComponentGeometry::Ptr m_geometry = {};
		bool m_moving = {};
		Engine::FPoint m_posBegin = {};
		Engine::FPoint m_posEnd = {};
		float m_time = {};
	};

}
