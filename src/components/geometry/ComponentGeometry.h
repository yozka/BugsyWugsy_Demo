//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "engine/common/eRect.h"
#include "components/Component.h"

namespace Game::Components
{

	//Компонент который хранит геометрию объекта
	//его положение и размер
	class AComponentGeometry : public AComponent
	{
	public:
		using UPtr		= std::unique_ptr<AComponentGeometry>;
		using Ptr		= std::shared_ptr<AComponentGeometry>;
		using WeakPtr	= std::weak_ptr<AComponentGeometry>;

		using SignalChanged = std::function<void(const Engine::IPoint&, const Engine::IPoint&)>;
	public:
		void Destroy() override;
		
		void SetSize(const Engine::FPoint &size);
		void SetPosition(const Engine::FPoint &pos);
		void SetTileSize(const int tilewidth, const int tileheight);
		
		
		Engine::FRect 	Geometry() const;
		Engine::FPoint 	Position() const;
		Engine::FPoint 	Size() const;
		
		Engine::IPoint	PositionGrid() const;
		Engine::FPoint 	CalcPositionFromGrid(const Engine::IPoint &grid) const; //Позиция в указанной клетке

	public:
		void ConnectPositionGrid(SignalChanged signal);
		
	private:
		void ChangedPositionGrid();
		
	private:
		Engine::FPoint m_position;
		Engine::IPoint m_positionGrid;

		Engine::FPoint m_size;

		int m_tilewidth = {};
		int m_tileheight = {};
		
		std::vector<SignalChanged> m_positionGrid_signals;
	};

}
