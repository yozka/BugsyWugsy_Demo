//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include "engine/common/eRect.h"


namespace Game::Map
{
	//Описание тип земли
	enum class EGridType
	{
		none,		//нет ничего, можно видеть
		block,		//заблокированно
		passable,	//можно передвигатся
		road,		//можно передвигатся дорога
		water		//вода
	};

	//Земля для отслеживания коллизий
	class AGrigCollision
	{
	public:
		using UPtr		= std::unique_ptr<AGrigCollision>;
		using Ptr		= std::shared_ptr<AGrigCollision>;
		using WeakPtr	= std::weak_ptr<AGrigCollision>;

		using Path 		= std::vector<Engine::IPoint>;
	public:
		AGrigCollision(const int width, const int height);
		virtual ~AGrigCollision();
		
	public:
		void SetGrid(const Engine::IPoint &pos, const EGridType type);
		void Destroy();
		
	public:
		EGridType GetGrid(const Engine::IPoint &pos) const;
		bool HasGround(const Engine::IPoint &pos) const; //Проверка, можно ли стоять на этой точке
		
	public:
		bool WaveGround(const Engine::IPoint &ptStart, const Engine::IPoint &ptEnd, Path &path, const int depth = 0);
		void WaveGroundRun(const Engine::IPoint &pt);
		int GetWaveData(const Engine::IPoint &pt) const;
		
	private:
		void WaveAlgorithm(const Engine::IPoint &ptStart, const Engine::IPoint &ptEnd, const int depth);
		void CalcPath(const Engine::IPoint &ptStart, const Engine::IPoint &ptEnd, Path &path);
		void SetWaveData(const Engine::IPoint &pt, const int data);
		//int GetWaveData(const Engine::IPoint &pt) const;

	private:
		const int m_width = {};
		const int m_height = {};
		std::vector<EGridType> m_grid;
		std::vector<int> m_wave;
	};

}
