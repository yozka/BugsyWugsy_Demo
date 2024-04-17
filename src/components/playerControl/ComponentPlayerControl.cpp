//◦ EggEngine ◦
#include "ComponentPlayerControl.h"
#include "engine/debug/eAssert.h"

using namespace Game::Components;


void AComponentPlayerControl::Destroy()
{
	m_path.clear();
	m_signalMoving = {};
	m_geometry = {};
	m_sprite = {};
	m_grid = {};
	m_sound = {};
}


bool AComponentPlayerControl::InitComponents()
{
	if (!m_sprite) {
		m_sprite =  GetComponent<AComponentSprite>();
		sassert(m_sprite);
		if (!m_sprite) return false;
	}
	
	if (!m_geometry) {
		m_geometry = GetComponent<AComponentGeometry>();
		sassert(m_geometry);
		if (!m_geometry) return false;
	}
	
	if (!m_grid) {
		m_grid = GetComponent<AComponentGrid>();
		sassert(m_grid);
		if (!m_grid) return false;
	}
	
	if (!m_sound) {
		m_sound = GetComponent<AComponentSound>();
		sassert(m_sound);
		if (!m_sound) return false;
	}
	return true;
}


void AComponentPlayerControl::SetSpeed(const float speed)
{
	m_speed = speed;
}

void AComponentPlayerControl::SetPathDepth(const int value)
{
	m_pathDepth = value;
}


//Начало движения по направлению
void AComponentPlayerControl::MovingToDirect(const Engine::IPoint &direct)
{
	if (!m_path.empty()) {
		MoveCompleted();
	}
	if (m_direct != direct) {
		m_direct = direct;
		if (m_direct != 0) {
			if (!m_moving) {
				m_moving = true;
				m_next = true;
			}
		}
	}
}

void AComponentPlayerControl::MovingToGrid(const Engine::IPoint &pos, SignalMoving signal)
{
	m_signalMoving = std::move(signal);
	if (!InitComponents()) {
		MoveCompleted();
		return;
	}
	//
	
	//Ищем путь для прохождения
	const auto startPosition = m_geometry->PositionGrid();
	if (startPosition == pos) {
		MoveCompleted();
		return;
	}
	//
	
	m_path.clear();
	m_grid->WaveGround(startPosition, pos, m_path, m_pathDepth);
	if (m_path.empty()) {
		
		if (m_grid->HasWater(pos)) {
			m_sound->Play("TapWater");
		} else {
			m_sound->Play("TapBlock");
		}
		
		
		MoveCompleted();
		return;
	}
	MoveStart();
}

void AComponentPlayerControl::MoveStart()
{
	m_moving = true;
	m_next = true;
	m_direct = {};
	if (m_signalMoving) {
		m_signalMoving(m_path);
	}
}

//Двигаемся к следующей точке
bool AComponentPlayerControl::MoveNext()
{
	m_next = false;
	if (m_path.empty() && m_direct == 0) {
		return false;
	}
	if (!InitComponents()) {
		return false;
	}
	
	Engine::IPoint pt = {-1, -1};
	if (!m_path.empty()) {
		pt = m_path.front();
		m_path.erase(m_path.begin());
	}
	if (m_direct != 0) {
		pt = m_geometry->PositionGrid();
		pt += m_direct;
	}
	
	if (!m_grid->HasGround(pt)) {
		return false;
	}
	
	m_posStart = m_geometry->Position();
	m_posEnd = m_geometry->CalcPositionFromGrid(pt);
	m_time = 0.0f;
	
	if (m_signalMoving) {
		m_signalMoving(m_path);
	}
	
	m_sound->Play("ChickenStep");
	return true;
}

void AComponentPlayerControl::MoveCompleted()
{
	m_moving = false;
	m_next = false;
	m_direct = {};
	m_path.clear();
	if (m_signalMoving) {
		m_signalMoving(m_path);
		m_signalMoving = {};
	}

	m_geometry = {};
	m_sprite = {};
	m_grid = {};
	m_sound = {};
}


void AComponentPlayerControl::Update(const double dt)
{
	if (!m_moving) return;
	if (m_next) {
		if (!MoveNext()) {
			MoveCompleted();
			return;
		}
	}
	
	m_time += dt;
	if (m_time > m_speed) {
		m_next = true;
		m_time = m_speed;
	}
	const float speed = (1.0f / m_speed) * m_time;
	auto pt = m_posStart + ((m_posEnd - m_posStart) * speed);
	if (m_geometry) {
		m_geometry->SetPosition(pt);
	}
}

