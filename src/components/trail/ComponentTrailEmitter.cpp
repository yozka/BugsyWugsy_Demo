//◦ EggEngine ◦
#include "ComponentTrailEmitter.h"
#include "components/geometry/ComponentGeometry.h"
#include "components/tilesets/ComponentTilesets.h"

#include "engine/debug/eAssert.h"
using namespace Game::Components;

AComponentTrailEmitter::AComponentTrailEmitter()
{
	
}


void AComponentTrailEmitter::Destroy()
{
	m_layer = {};
	m_grid = {};
}


void AComponentTrailEmitter::SetTileName(const std::string &name)
{
	m_tileName = name;
	sassert(!m_tileName.empty());
}


void AComponentTrailEmitter::SetlayerName(const std::string &name)
{
	m_layerName = name;
	sassert(!m_layerName.empty());
}


void AComponentTrailEmitter::SetTrailLive(const float time)
{
	m_timeTrailLive = time;
}

void AComponentTrailEmitter::ComponentAttached()
{
	if (m_attached) return;
	auto geometry = GetComponent<AComponentGeometry>();
	if (!geometry) return;
	m_attached = true;
	geometry->ConnectPositionGrid(std::bind(&AComponentTrailEmitter::ChangePositions, this, std::placeholders::_1, std::placeholders::_2));
}


bool AComponentTrailEmitter::Init()
{
	if (m_init) return true;
	
	if (m_tilesId.empty()) {
		if (auto tilesets = GetComponent<AComponentTilesets>()) {
			m_tilesId = tilesets->FindTiles(m_tileName);
		}
		if (m_tilesId.empty()) return false;
	}
	
	if (!m_layer) {
		if (auto layers = GetComponent<AComponentLayer>()) {
			m_layer = layers->FindLayerTiles(m_layerName);
		}
		if (!m_layer) return false;
	}
	
	if (!m_grid) {
		m_grid = GetComponent<AComponentGrid>();
		if (!m_grid) return false;
	}
	
	m_init = true;
	return true;
}


void AComponentTrailEmitter::ChangePositions(const Engine::IPoint &gridStart, const Engine::IPoint &gridEnd)
{
	if (!Init()) return;
	
	for (auto& trail : m_trails) {
		if (trail == gridStart) return;
	}
	m_timeSlow = 0.5f;
	m_timeSlowNormal = m_timeTrailLive;
	AppendTrail(gridStart);
}


void AComponentTrailEmitter::AppendTrail(Engine::IPoint pos)
{
	m_trails.push_front(pos);
	m_grid->SetNone(pos);

	if (m_trailLength == 0) {
		SetTrailAnimation(pos);
	} else {
		auto it = m_trails.begin();
		std::advance(it, m_trailLength);
		if (it != m_trails.end()) {
			SetTrailAnimation(*it);
		}
	}
	
}

void AComponentTrailEmitter::SetTrailAnimation(Engine::IPoint pos)
{
	if (m_trails.size() == 1) {
		m_layer->SetTileId(pos, m_tilesId.front());
	} else {
		m_layer->SetTileId(pos, 0);
		for (auto id : m_tilesId) {
			m_layer->AppendAnimation(pos.x, pos.y, id, 0.3f);
		}
	}
}

void AComponentTrailEmitter::RemoveTrail()
{
	if (!Init()) return;
	
	auto pos = m_trails.back();
	m_trails.pop_back();
	m_layer->SetTileId(pos, 0);
	m_grid->SetPassable(pos);
}


//Увеличим длину хвоста
int AComponentTrailEmitter::IncLength()
{
	int old = m_trailLength;
	m_trailLength++;
	
	auto it = m_trails.begin();
	std::advance(it, old);
	if (it != m_trails.end()) {
		m_layer->SetTileId(*it, 0);
	}
	return old;
}

Engine::IPoint AComponentTrailEmitter::GetTrailPosition(const int number) const
{
	auto it = m_trails.begin();
	std::advance(it, number);
	if (it != m_trails.end()) {
		return *it;
	}
	return {};
}


void AComponentTrailEmitter::Update(const double dt)
{
	//Хвот обрезать не нужно
	if (m_trails.empty()) {
		return;
	}
	if (m_trailLength >= m_trails.size()) {
		return;
	}
	
	float slowTime = dt * m_timeSlow;
	if (m_timeSlowNormal >= 0) {
		m_timeSlowNormal -= dt;
		if (m_timeSlowNormal < 0) {
			m_timeSlow = 1.0f;
		}
	}
	//
	
	m_timeRemove += slowTime;
	if (m_timeRemove > m_timeTrailLive) {
		//Время обрезать хвост
		m_timeRemove = 0;
		RemoveTrail();
	}
}

/*
#include <iostream>
#include <vector>

// Функция для проверки, находится ли точка в пределах массива
bool isSafe(int x, int y, int maxX, int maxY) 
{
	return (x >= 0 && x < maxX && y >= 0 && y < maxY);
}

// Функция затравки для закрашивания замкнутой области
void floodFill(std::vector<std::vector<char>>& screen, int x, int y, char prevC, char newC)
{
	if (!isSafe(x, y, screen.size(), screen[0].size())) return;
	if (screen[x][y] != prevC) return;
	
	// Заменяем цвет в текущей ячейке
	screen[x][y] = newC;
	
	// Рекурсивно применяем функцию к соседним ячейкам
	floodFill(screen, x + 1, y, prevC, newC);
	floodFill(screen, x - 1, y, prevC, newC);
	floodFill(screen, x, y + 1, prevC, newC);
	floodFill(screen, x, y - 1, prevC, newC);
}

// Функция для заполнения замкнутой области
void fillClosedArea(std::vector<std::vector<char>>& screen, int x, int y, char newC) 
{
	if (screen.empty()) return;
	char prevC = screen[x][y];
	if (prevC == newC) return;
	
	floodFill(screen, x, y, prevC, newC);
}

int main() 
{
	std::vector<std::vector<char>> screen = {
		{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
		{'X', ' ', ' ', 'X', 'X', ' ', ' ', 'X'},
		{'X', ' ', ' ', 'X', 'X', ' ', 'X', 'X'},
		{'X', 'X', 'X', ' ', ' ', ' ', 'X', 'X'},
		{'X', 'X', ' ', ' ', ' ', 'X', 'X', 'X'},
		{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}
	};
	
	// Заполняем замкнутую область символом 'O'
	fillClosedArea(screen, 1, 1, 'O');
	
	// Выводим результат
	for (const auto& row : screen) {
		for (char pixel : row) {
			std::cout << pixel << " ";
		}
		std::cout << std::endl;
	}
	
	return 0;
}
*/
