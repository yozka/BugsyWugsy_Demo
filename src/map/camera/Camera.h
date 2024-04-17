//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "engine/common/eRect.h"

namespace Game::Map
{
	struct TVisionTiles
	{
		int screenStartX = {};
		int screenStartY = {};
		
		int xBegin = {};
		int xEnd = {};
		int yBegin = {};
		int yEnd = {};
		
		int screentilewidth = {};
		int screentileheight = {};
	};

	struct TVisionObjects
	{
		int screenObjectStartX = {};
		int screenObjectStartY = {};
		Engine::FRect viewRect = {};
		float scale = {};
	};
	//


	//Камерая для отрисовки тайлов и игровых объектов на карте
	class ACamera
	{
	public:
		using UPtr		= std::unique_ptr<ACamera>;
		using Ptr		= std::shared_ptr<ACamera>;
		using WeakPtr	= std::weak_ptr<ACamera>;
		
	public:
		ACamera();
		virtual ~ACamera();
		
	public:
		void Init(const int width, const int height, const int tilewidth, const int tileheight);
		void SetScreenSize(const int renderWidth, const int renderHeight);
		
		void SetPosition(const Engine::FPoint &pos);
		Engine::FPoint GetPosition() const { return m_curentPosition; }
		
		void SetScale(const float scale);
		void ZoomIn(const float scale = 0.01f);
		void ZoomOut(const float scale = 0.01f);
		void ZoomReset();
		
		

		Engine::FPoint 	ScreenToWorld(const Engine::IPoint &screen) const; 		//перевод экраннны координат в игровые
		Engine::IPoint 	ScreenToWorldGrid(const Engine::IPoint &screen) const; 	//перевод экранных координат в координаты карты
		
		Engine::IPoint 	WorldToScreen(const Engine::FPoint &world) const; //Перевод игровых координат в экранные
		Engine::IRect 	WorldGridToScreenRect(const Engine::IPoint &worldGrid) const; //Перевод координат карты в прямоугольник на экране
		
		Engine::IRect 	ToScreenRect() const; //Перевод координат карты в прямоугольник на экране
	public:
		TVisionTiles GetVisionTiles() const;
		TVisionObjects GetVisionObjects() const;
		
	private:
		void Calc();
		
	private:
		bool m_init = {};
		
		//Размер карты в тайлах
		int m_width = {};
		int m_height = {};
		
		//Размерность тайлов
		int m_tilewidth = {};
		int m_tileheight = {};
		
		//Текущее положение камеры
		Engine::FPoint m_curentPosition = {};
		
		//Текущий масштаб
		float m_currentScale = { 1.0f };
		float m_scale = {};
		
		//Экранная размерность тайлов
		int m_screentilewidth = {};
		int m_screentileheight = {};
		int m_screentilewidthDiv = {};
		int m_screentileheightDiv = {};
		
		//Размер экрана
		int m_screenWidth = {};
		int m_screenHeight = {};
		
		//Количество видимых тайлов
		int m_visibleTileCols = {};
		int m_visibleTileRows = {};
		
		//Центральный тайл
		int m_centerX = {};
		int m_centerY = {};
		
		//позиция камеры, целочисленная
		Engine::IPoint m_pos = {};
		
		//Смещение для всех тайлов
		int m_offsetX = {};
		int m_offsetY = {};
		
		//Диапазон отрисовки спрайтов
		int m_xBegin = {};
		int m_xEnd = {};
		int m_yBegin = {};
		int m_yEnd = {};
		
		int m_homeX = {};
		int m_homeY = {};
		
		int m_screenObjectStartX = {};
		int m_screenObjectStartY = {};
		
		Engine::FRect m_viewRect = {};
		
		int m_screenStartX = {};
		int m_screenStartY = {};
	};

}
