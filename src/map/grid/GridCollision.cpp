//◦ EggEngine ◦
#include "GridCollision.h"


using namespace Game::Map;


AGrigCollision::AGrigCollision(const int width, const int height)
	:
		m_width(width),
		m_height(height)
{
	m_grid.resize(width * height);
}


AGrigCollision::~AGrigCollision()
{

}


void AGrigCollision::SetGrid(const Engine::IPoint &pos, const EGridType type)
{
	const size_t index = pos.x + pos.y * m_width;
	if (index < m_grid.size()) {
		m_grid[index] = type;
	}
}


void AGrigCollision::Destroy()
{
	m_grid.clear();
}


void AGrigCollision::WaveGroundRun(const Engine::IPoint &pt)
{
	m_wave.resize(m_grid.size());
	for (auto i = 0; i < m_grid.size(); i++) {
		int val = 0;
		switch (m_grid[i]) {
			case EGridType::none		: val = -1; break; //нет ничего, можно видеть
			case EGridType::block		: val = -1; break; //заблокированно
			case EGridType::passable	: val = 0;  break; //можно передвигатся
			case EGridType::road		: val = 0;  break; //можно передвигатся дорога
			case EGridType::water		: val = -1; break; //вода
		}
		m_wave[i] = val;
	}
	WaveAlgorithm(pt, pt, 0);
}


bool AGrigCollision::WaveGround(const Engine::IPoint &ptStart, const Engine::IPoint &ptEnd, Path &path, const int depth)
{
	m_wave.resize(m_grid.size());
	for (auto i = 0; i < m_grid.size(); i++) {
		int val = 0;
		switch (m_grid[i]) {
			case EGridType::none		: val = -1; break; //нет ничего, можно видеть
			case EGridType::block		: val = -1; break; //заблокированно
			case EGridType::passable	: val = 0;  break; //можно передвигатся
			case EGridType::road		: val = 0;  break; //можно передвигатся дорога
			case EGridType::water		: val = -1; break; //вода
		}
		m_wave[i] = val;
	}
	WaveAlgorithm(ptStart, ptEnd, depth);
	if (GetWaveData(ptStart) < 1 || GetWaveData(ptEnd) < 1) {
		return false;
	}
	CalcPath(ptStart, ptEnd, path);
	return true;
}

void AGrigCollision::WaveAlgorithm(const Engine::IPoint &ptStart, const Engine::IPoint &ptEnd, const int depth)
{
	bool checkStart = false;
	if (ptStart != ptEnd) {
		checkStart = true;
		if (GetWaveData(ptStart) != 0 || GetWaveData(ptEnd) != 0) {
			return;
		}
	}
	
	std::queue<Engine::IPoint> q;
	q.push(ptEnd);
	SetWaveData(ptEnd, 1);

	std::vector<Engine::IPoint> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	
	while (!q.empty()) {
		const auto pt = q.front();
		q.pop();
		const int data = GetWaveData(pt) + 1;
		if (depth > 0 && data > depth) {
			break;
		}
		if (pt == ptStart && checkStart) {
			break;
		}
		
		for (auto& dir : directions) {
			const auto new_pt = pt + dir;
			if (GetWaveData(new_pt) == 0) {
				SetWaveData(new_pt, data);
				q.push(new_pt);
			}
		}
	}
}

void AGrigCollision::CalcPath(const Engine::IPoint &ptStart, const Engine::IPoint &ptEnd, Path &path)
{
	std::vector<Engine::IPoint> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	auto pt = ptStart;
	int data = GetWaveData(pt);
	bool exit = false;
	while (pt != ptEnd && !exit) {
		exit = true;
		for (auto& dir : directions) {
			const auto new_pt = pt + dir;
			int new_data = GetWaveData(new_pt);
			if (new_data > 0 && new_data < data) {
				data = new_data;
				pt = new_pt;
				path.push_back(pt);
				exit = false;
				break;
			}
		}
		
	}
}


int AGrigCollision::GetWaveData(const Engine::IPoint &pt) const
{
	if (pt.x < 0 || pt.x >= m_width || pt.y < 0 || pt.y >= m_height) {
		return -1;
	}
	const size_t index = pt.x + pt.y * m_width;
	if (index < m_wave.size()) {
		return m_wave[index];
	}
	return -1;
}

void AGrigCollision::SetWaveData(const Engine::IPoint &pt, const int data)
{
	if (pt.x < 0 || pt.x >= m_width || pt.y < 0 || pt.y >= m_height) {
		return;
	}
	const size_t index = pt.x + pt.y * m_width;
	if (index < m_wave.size()) {
		m_wave[index] = data;
	}
}


//Проверка, можно ли стоять на этой точке
bool AGrigCollision::HasGround(const Engine::IPoint &pos) const
{
	if (pos.x < 0 || pos.x >= m_width || pos.y < 0 || pos.y >= m_height) {
		return false;
	}
	const size_t index = pos.x + pos.y * m_width;
	if (index < m_grid.size())
	switch (m_grid[index]) {
		case EGridType::none		: return false; //нет ничего, можно видеть
		case EGridType::block		: return false; //заблокированно
		case EGridType::passable	: return true;  //можно передвигатся
		case EGridType::road		: return true;  //можно передвигатся дорога
		case EGridType::water		: return false; //вода
	}
	return false;
}


EGridType AGrigCollision::GetGrid(const Engine::IPoint &pos) const
{
	if (pos.x < 0 || pos.x >= m_width || pos.y < 0 || pos.y >= m_height) {
		return EGridType::none;
	}
	const size_t index = pos.x + pos.y * m_width;
	if (index < m_grid.size()) {
		return m_grid[index];
	}
	return EGridType::none;
}
