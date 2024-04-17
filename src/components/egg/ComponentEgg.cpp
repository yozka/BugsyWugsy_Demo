//◦ EggEngine ◦
#include "ComponentEgg.h"
#include "components/layer/ComponentLayer.h"
#include "components/sprite/ComponentSprite.h"
#include "components/sound/ComponentSound.h"


using namespace Game::Components;


AComponentEgg::AComponentEgg()
{

}


AComponentEgg::~AComponentEgg()
{

}

void AComponentEgg::SetMaster(const std::string &name)
{
	m_masterName = name;
}

void AComponentEgg::SetChecken(const std::string &name)
{
	m_checkenName = name;
}

void AComponentEgg::Start()
{
	if (auto layer = GetComponent<AComponentLayer>()) {
		m_master = layer->FindObject(m_masterName);
		if (m_master) {
			m_masterGeometry = m_master->GetComponent<AComponentGeometry>();
			m_masterTrail = m_master->GetComponent<AComponentTrailEmitter>();
		}
	}
	
	m_geometry = GetComponent<AComponentGeometry>();
}

void AComponentEgg::Destroy()
{
	m_master = {};
	m_masterGeometry = {};
	m_masterTrail = {};
}

void AComponentEgg::Update(const double dt)
{
	if (!m_collect) {
		m_timeUpdate += dt;
		if (m_timeUpdate < 0.3f) return;
		m_timeUpdate = 0;
		if (!m_masterGeometry) return;
		if (!m_geometry) return;
	
		const auto posEgg = m_geometry->PositionGrid();
		const auto posMaster = m_masterGeometry->PositionGrid();
		if (posEgg == posMaster) {
			CollectEgg();
		}
		return;
	}

	if (m_moving) {
		m_time += dt;
		if (m_time > m_speed) {
			m_moving = false;
			m_time = m_speed;
		}
		const float speed = (1.0f / m_speed) * m_time;
		auto pt = m_posStart + ((m_posEnd - m_posStart) * speed);
		if (m_geometry) {
			m_geometry->SetPosition(pt);
		}
	}
	
	
	if (m_movingTrail) {
		//Движемся в хвосте;
		m_timeUpdate += dt;
		if (m_timeUpdate > 0.2f) {
			m_timeUpdate = 0;

			if (!m_masterTrail) return;
			if (!m_geometry) return;
			
			m_moving = true;
			m_time = 0;
			auto posTrail 	= m_masterTrail->GetTrailPosition(m_trailPosition);
			m_posStart 		= m_geometry->Position();
			m_posEnd 		= m_geometry->CalcPositionFromGrid(posTrail);
		}
	}
	
	
}

//Собрали яйцо
void AComponentEgg::CollectEgg()
{
	m_collect = true;
	if (auto sprite = GetComponent<AComponentSprite>()) {
		sprite->SetSprite(m_checkenName);
	}
	if (auto sound = GetComponent<AComponentSound>()) {
		sound->Play("ChickenEgg");
	}
	
	if (m_masterTrail) {
		m_trailPosition = m_masterTrail->IncLength();
		m_movingTrail = true;
	}
}


