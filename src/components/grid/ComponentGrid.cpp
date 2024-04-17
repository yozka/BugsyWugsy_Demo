//◦ EggEngine ◦
#include "ComponentGrid.h"

using namespace Game::Components;

AComponentGrid::AComponentGrid(Game::Map::AGrigCollision::WeakPtr grid)
	:
		m_grid(std::move(grid))
{
	
}


void AComponentGrid::Destroy()
{
	m_grid = {};
}


void AComponentGrid::WaveGroundRun(const Engine::IPoint &pt)
{
	if (auto grid = m_grid.lock()) {
		grid->WaveGroundRun(pt);
	}
}

int AComponentGrid::GetWaveData(const Engine::IPoint &pt) const
{
	if (auto grid = m_grid.lock()) {
		return grid->GetWaveData(pt);
	}
	return -1;
}

bool AComponentGrid::WaveGround(const Engine::IPoint &ptStart, const Engine::IPoint &ptEnd, Path &path, const int depth)
{
	if (auto grid = m_grid.lock()) {
		return grid->WaveGround(ptStart, ptEnd, path, depth);
	}
	return false;
}

//Проверка, можно ли стоять на этой точке
bool AComponentGrid::HasGround(const Engine::IPoint &pos) const
{
	if (auto grid = m_grid.lock()) {
		return grid->HasGround(pos);
	}
	return false;
}


bool AComponentGrid::HasWater(const Engine::IPoint &pos) const
{
	if (auto grid = m_grid.lock()) {
		return grid->GetGrid(pos) == Map::EGridType::water;
	}
	return false;
}

void AComponentGrid::SetNone(const Engine::IPoint &pos)
{
	if (auto grid = m_grid.lock()) {
		grid->SetGrid(pos, Map::EGridType::none);
	}
}

void AComponentGrid::SetBlock(const Engine::IPoint &pos)
{
	if (auto grid = m_grid.lock()) {
		grid->SetGrid(pos, Map::EGridType::block);
	}
}

void AComponentGrid::SetPassable(const Engine::IPoint &pos)
{
	if (auto grid = m_grid.lock()) {
		grid->SetGrid(pos, Map::EGridType::passable);
	}
}

void AComponentGrid::SetRoad(const Engine::IPoint &pos)
{
	if (auto grid = m_grid.lock()) {
		grid->SetGrid(pos, Map::EGridType::road);
	}
}

void AComponentGrid::SetWater(const Engine::IPoint &pos)
{
	if (auto grid = m_grid.lock()) {
		grid->SetGrid(pos, Map::EGridType::water);
	}
}
