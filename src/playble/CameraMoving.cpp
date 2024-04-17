//◦ EggEngine ◦
#include "CameraMoving.h"
#include "engine/common/eMath.h"


using namespace Game;

void ACameraMoving::Done()
{
	m_camera = {};
	m_geometry = {};
}

void ACameraMoving::Init(const Map::ACamera::Ptr &camera, const Components::AComponentGeometry::Ptr &geometry)
{
	m_camera = camera;
	m_geometry = geometry;
	m_geometry->ConnectPositionGrid(std::bind(&ACameraMoving::ChangePositions, this, std::placeholders::_1, std::placeholders::_2));
	
}


void ACameraMoving::Update(const double dt)
{
	if (!m_moving || !m_camera || !m_geometry) return;
	

	float speed = 0.8f;
	m_time += dt;
	if (m_time > speed) {
		m_time = speed;
		m_moving = false;
	}
	auto time = (1.0f / speed) * m_time;
	auto diff = (m_posEnd - m_posBegin) * Engine::Math::EaseOutQuad(time);
	auto pt = m_posBegin + diff;
	m_camera->SetPosition(pt);
}


void ACameraMoving::Home()
{
	m_moving = false;
	if (m_camera && m_geometry) {
		m_camera->SetPosition(m_geometry->Position());
	}
}

void ACameraMoving::Stop()
{
	m_moving = false;
}


void ACameraMoving::ChangePositions(const Engine::IPoint &gridStart, const Engine::IPoint &gridEnd)
{
	if (!m_camera || !m_geometry) return;
	
	Engine::IRect player = m_camera->WorldGridToScreenRect(gridEnd);
	Engine::IRect main = m_camera->ToScreenRect();
	
	float area = 0.2f;
	int bwidth = static_cast<int>(main.Width() * area);
	int bheight = static_cast<int>(main.Height() * area);
	
	Engine::IRect screen;
	screen.x1 = main.x1 + bwidth;
	screen.x2 = main.x2 - bwidth;
	screen.y1 = main.y1 + bheight;
	screen.y2 = main.y2 - bheight;
	
	if (RECT2RECT(screen, player)) {
		return;
	}
	
	m_moving = true;
	m_posBegin = m_camera->GetPosition();
	m_posEnd = m_geometry->Position();
	m_time = 0.0f;
}
