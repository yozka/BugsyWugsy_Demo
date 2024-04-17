//◦ EggEngine ◦
#include "ComponentFinal.h"
#include "components/layer/ComponentLayer.h"
#include "components/sprite/ComponentSprite.h"
#include "components/egg/ComponentEgg.h"
#include "components/music/ComponentMusic.h"


using namespace Game::Components;


AComponentFinal::AComponentFinal()
{

}


AComponentFinal::~AComponentFinal()
{

}

void AComponentFinal::SetWinEgg(const int value)
{
	m_winEgg = value;
}

void AComponentFinal::Start()
{
	m_grid = GetComponent<AComponentGrid>();
	
	if (auto layer = GetComponent<AComponentLayer>()) {
		for (auto obj : layer->GetComponents<AComponentEgg>()) {
			m_eggs.push_back(obj);
		}
		if (auto player = layer->FindObject("Player")) {
			m_player = player->GetComponent<AComponentGeometry>();
		}
	}
	
	m_active = !m_eggs.empty();
}

void AComponentFinal::Destroy()
{
	m_eggs.clear();
	m_eggsCollect.clear();
	m_grid = {};
}

void AComponentFinal::Update(const double dt)
{
	if (!m_active) return;
	m_timeCheck -= dt;
	if (m_timeCheck > 0) return;
	m_timeCheck = 2.0f;
	
	for (auto it = m_eggs.begin(); it != m_eggs.end(); ++it) {
		auto egg = *it;
		if (egg && egg->IsCollect()) {
			m_eggsCollect.push_back(egg);
			it = m_eggs.erase(it);
		}
	}
	
	if (m_eggsCollect.size() >= m_winEgg || m_eggs.empty()) {
		m_active = false;
		if (onGameWin) {
			onGameWin();
		}
	}
	
	//проверяем на проигрыш
	if (!m_grid || !m_player ) return;
	
	const auto pos = m_player->PositionGrid();
	m_grid->WaveGroundRun(pos);
	for (auto& egg : m_eggs) {
		if (auto geom = egg->GetComponent<AComponentGeometry>()) {
			const auto posEgg = geom->PositionGrid();
			const int data = m_grid->GetWaveData(posEgg);
			if (data > 0) {
				FailFalse();
				return;
			}
		}
	}

	FailAlarm();
	if (m_fails < 5) {
		return;
	}
	if (onGameLose) {
		onGameLose();
	}
	m_active = false;
}


void AComponentFinal::FailFalse()
{
	//Отмена тревоги
	if (m_fails > 0) {
		// Переключаем музыку
		if (auto music = GetComponent<AComponentMusic>()) {
			music->PlayMusic1();
		}
	}
	m_fails = 0;
}


void AComponentFinal::FailAlarm()
{
	//тревога!!
	if (m_fails == 0) {
		// Переключаем музыку
		if (auto music = GetComponent<AComponentMusic>()) {
			music->PlayMusic2();
		}
	}
	
	m_fails++;
	
}


void AComponentFinal::GameWin()
{
	
}

void AComponentFinal::GameLose()
{
	
}

