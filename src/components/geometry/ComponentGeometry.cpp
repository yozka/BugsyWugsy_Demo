//◦ EggEngine ◦
#include "ComponentGeometry.h"


using namespace Game::Components;

void AComponentGeometry::Destroy()
{
	m_position = {};
	m_size = {};
	m_positionGrid_signals.clear();
}

Engine::FRect AComponentGeometry::Geometry() const
{
	return { m_position.x, m_position.y, m_position.x + m_size.x, m_position.y + m_size.y };
}

Engine::FPoint AComponentGeometry::Position() const
{
	return m_position;
}

Engine::FPoint AComponentGeometry::Size() const
{
	return m_size;
}

void AComponentGeometry::SetSize(const Engine::FPoint &size)
{
	m_size = size;
}

void AComponentGeometry::SetPosition(const Engine::FPoint &pos)
{
	m_position = pos;
	ChangedPositionGrid();
}

void AComponentGeometry::SetTileSize(const int tilewidth, const int tileheight)
{
	m_tilewidth = tilewidth;
	m_tileheight = tileheight;
	ChangedPositionGrid();
}

Engine::IPoint AComponentGeometry::PositionGrid() const
{
	return m_positionGrid;
}


//Позиция в указанной клетке
Engine::FPoint 	AComponentGeometry::CalcPositionFromGrid(const Engine::IPoint &grid) const
{
	const float tw = static_cast<float>(m_tilewidth);
	const float th = static_cast<float>(m_tileheight);
	return { grid.x * tw + (tw / 2), grid.y * th + (th / 2)};
}


void AComponentGeometry::ConnectPositionGrid(SignalChanged signal)
{
	m_positionGrid_signals.push_back(std::move(signal));
}


void AComponentGeometry::ChangedPositionGrid()
{
	if (m_tilewidth <= 0 || m_tileheight <= 0) return;
	
	//рассылаем всем, что мы поменяли позицию
	Engine::IPoint pt = { static_cast<int>(m_position.x / m_tilewidth), static_cast<int>(m_position.y / m_tileheight) };
	if (pt != m_positionGrid){
		std::swap(pt, m_positionGrid);
		for(auto& signal : m_positionGrid_signals) {
			signal(pt, m_positionGrid);
		}
	}
}
