//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>
#include <list>
#include <functional>


#include "components/ComponentUpdater.h"
#include "components/egg/ComponentEgg.h"
#include "components/grid/ComponentGrid.h"
#include "components/geometry/ComponentGeometry.h"

namespace Game::Components
{

	//Компанент считает финал
	class AComponentFinal : public AComponentUpdater
	{
	public:
		using UPtr		= std::unique_ptr<AComponentFinal>;
		using Ptr		= std::shared_ptr<AComponentFinal>;
		using WeakPtr	= std::weak_ptr<AComponentFinal>;

	public:
		AComponentFinal();
		~AComponentFinal() override;
		
	public:
		std::function<void()> onGameWin = {};
		std::function<void()> onGameLose = {};
		
	public:
		void Start() override;
		void Destroy() override;
		void Update(const double dt) override;
		
		void GameWin();
		void GameLose();
		
	public:
		void SetWinEgg(const int value);
		
		
	private:
		void FailFalse();
		void FailAlarm();
		
	private:
		int m_winEgg = { 10 };
		int m_fails = {};
		bool m_active = {};
		float m_timeCheck = {};
		std::list<AComponentEgg::Ptr> m_eggs;
		std::list<AComponentEgg::Ptr> m_eggsCollect;
		
		AComponentGrid::Ptr m_grid = {};
		AComponentGeometry::Ptr m_player = {};
	};

}
