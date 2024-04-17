//◦ EggEngine ◦
#include "Camera.h"


using namespace Game::Map;


ACamera::ACamera()
{
	
}

ACamera::~ACamera()
{

}

void ACamera::Init(const int width, const int height, const int tilewidth, const int tileheight)
{
	m_init = true;
	m_width = width;
	m_height = height;
	m_tilewidth = tilewidth;
	m_tileheight = tileheight;
	
	m_curentPosition = {};
	m_pos = {};
	m_currentScale = 1.0f;
	m_scale = {};
	
	m_screentilewidth = {};
	m_screentileheight = {};
	
	m_screenWidth = {};
	m_screenHeight = {};
	
	m_visibleTileCols = {};
	m_visibleTileRows = {};
	
	m_centerX = {};
	m_centerY = {};
	
	m_offsetX = {};
	m_offsetY = {};
	
	m_xBegin = {};
	m_xEnd = {};
	m_yBegin = {};
	m_yEnd = {};
	
	m_homeX = {};
	m_homeY = {};
	
	m_screenObjectStartX = {};
	m_screenObjectStartY = {};
	
	m_viewRect = {};
	
	m_screenStartX = {};
	m_screenStartY = {};
}

void ACamera::SetScreenSize(const int renderWidth, const int renderHeight)
{
	if (renderWidth != m_screenWidth || renderHeight != m_screenHeight) {
		m_screenWidth = renderWidth;
		m_screenHeight = renderHeight;
		if (m_init) {
			Calc();
		}
	}
}


void ACamera::SetPosition(const Engine::FPoint &pos)
{
	m_curentPosition = pos;
	if (m_init) {
		Calc();
	}
}


void ACamera::SetScale(const float scale)
{
	m_currentScale = scale;
	if (m_init) {
		Calc();
	}
}


void ACamera::ZoomIn(const float scale)
{
	m_currentScale += scale;
	if (m_init) {
		Calc();
	}
}


void ACamera::ZoomOut(const float scale)
{	
	m_currentScale -= scale;
	if (m_init) {
		Calc();
	}
	
}


void ACamera::ZoomReset()
{
	m_currentScale = 1.0f;
	if (m_init) {
		Calc();
	}
}

Engine::FPoint ACamera::ScreenToWorld(const Engine::IPoint &screen) const
{
	return { static_cast<float>(screen.x) / m_scale, static_cast<float>(screen.y) / m_scale };
}

//перевод экранных координат в координаты карты
Engine::IPoint ACamera::ScreenToWorldGrid(const Engine::IPoint &screen) const
{
	const auto worldx = static_cast<float>(screen.x - m_screenObjectStartX - m_screentilewidthDiv) / m_scale;
	const auto worldy = static_cast<float>(screen.y - m_screenObjectStartY - m_screentileheightDiv) / m_scale;
	
	return  { static_cast<int>(worldx / m_tilewidth), static_cast<int>(worldy / m_tileheight) };
}

//Перевод координат карты в прямоугольник на экране
Engine::IRect ACamera::WorldGridToScreenRect(const Engine::IPoint &worldGrid) const
{
	int x = m_screenObjectStartX + m_screentilewidthDiv + worldGrid.x * m_screentilewidth;
	int y = m_screenObjectStartY + m_screentileheightDiv + worldGrid.y * m_screentileheight;
	return { x, y, x + m_screentilewidth, y + m_screentileheight};
}

Engine::IRect ACamera::ToScreenRect() const
{
	return {0,0, m_screenWidth, m_screenHeight};
}


Engine::IPoint ACamera::WorldToScreen(const Engine::FPoint &world) const
{
	return {};
}


void ACamera::Calc()
{
	if (m_screenWidth == 0 || m_screenHeight == 0) return;
	
	m_pos.x = static_cast<int>(m_curentPosition.x);
	m_pos.y = static_cast<int>(m_curentPosition.y);
	
	m_screentilewidth 	= static_cast<int>(static_cast<float>(m_tilewidth) * m_currentScale);
	m_screentileheight 	= static_cast<int>(static_cast<float>(m_tileheight) * m_currentScale);
	m_screentilewidthDiv = m_screentilewidth / 2;
	m_screentileheightDiv = m_screentileheight / 2;
	m_scale = static_cast<float>(m_screentilewidth) / static_cast<float>(m_tilewidth);
	
	//Видемые тайлы
	m_visibleTileCols = (m_screenWidth / m_screentilewidth) / 2;
	m_visibleTileRows = (m_screenHeight / m_screentileheight) / 2;
	
	//Центральный тайл
	m_centerX = m_pos.x / m_tilewidth;
	m_centerY = m_pos.y / m_tileheight;


	//Смещение для всех тайлов
	m_offsetX = (m_tilewidth - (m_pos.x - m_centerX * m_tilewidth)) * m_scale;
	m_offsetY = (m_tileheight - (m_pos.y - m_centerY * m_tileheight)) * m_scale;
	
	//Диапазон отрисовки спрайтов
	m_xBegin = std::max(0, m_centerX - m_visibleTileCols);
	m_xEnd = std::min(m_width, m_centerX + m_visibleTileCols + 3);
	m_yBegin = std::max(0, m_centerY - m_visibleTileRows);
	m_yEnd = std::min(m_height, m_centerY + m_visibleTileRows + 3);

	//Отрисовка
	m_homeX = (m_visibleTileCols - m_centerX) * m_screentilewidth;
	m_homeY = (m_visibleTileRows - m_centerY) * m_screentileheight;
	
	m_screenObjectStartX = m_offsetX - m_screentilewidth - m_screentilewidth/2 + m_homeX;
	m_screenObjectStartY = m_offsetY - m_screentileheight - m_screentileheight/2 + m_homeY;
	
	m_viewRect.x1 = m_screenObjectStartX / -m_scale;
	m_viewRect.x2 = m_viewRect.x1 + m_screenWidth / m_scale;
	m_viewRect.y1 = m_screenObjectStartY / -m_scale;
	m_viewRect.y2 = m_viewRect.y1 + m_screenHeight / m_scale;
	
	
	m_screenStartX = m_offsetX - m_screentilewidth - m_screentilewidth + (m_xBegin == 0 ? m_homeX : 0);
	m_screenStartY = m_offsetY - m_screentileheight - m_screentileheight + (m_yBegin == 0 ? m_homeY : 0);

}


TVisionTiles ACamera::GetVisionTiles() const
{
	TVisionTiles vision;
	vision.screenStartX = m_screenStartX;
	vision.screenStartY = m_screenStartY;
	
	vision.xBegin = m_xBegin;
	vision.xEnd =  m_xEnd;
	vision.yBegin = m_yBegin;
	vision.yEnd = m_yEnd;
	
	vision.screentilewidth = m_screentilewidth;
	vision.screentileheight = m_screentileheight;
	
	return vision;
}


TVisionObjects ACamera::GetVisionObjects() const
{
	TVisionObjects vision;
	vision.screenObjectStartX = m_screenObjectStartX;
	vision.screenObjectStartY = m_screenObjectStartY;
	vision.viewRect = m_viewRect;
	vision.scale = m_scale;
	return vision;
}
