//◦ EggEngine ◦
#include "MenuScene.h"
#include <SDL_image.h>
#include <assert.h>

using namespace Game;


AMenuScene::AMenuScene()
{

}


AMenuScene::~AMenuScene()
{

}


//Инциализация
bool AMenuScene::Init()
{
	m_surface = IMG_Load("menu/logo.png");
	assert(m_surface);
	return true;
}


//Завершение игры
void AMenuScene::Done()
{
	if (m_surface) {
		SDL_FreeSurface(m_surface);
		m_surface = {};
	}

	if (m_texture) {
		SDL_DestroyTexture(m_texture);
		m_texture = {};
	}
}


void AMenuScene::EventInput(SDL_Event &event)
{
	
}


//Игровой цикл
void AMenuScene::Update(const double dt)
{
	
}


//Отрисовка
void AMenuScene::Render(const Engine::Render::ERenderContext::UPtr& context)
{
	if (!m_texture && m_surface) {
		m_texture = context->CreateTexture(m_surface);
		SDL_FreeSurface(m_surface);
		m_surface = {};
	}
	
	if (m_texture) {
		int w = 0;
		int h = 0;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);
		
		const int dw = context->RenderWidth();
		const int dh = context->RenderHeight();
		
		SDL_Rect dest;
		dest.x = (dw - w) / 2;
		dest.y = (dh - h) / 2;
		dest.w = w;
		dest.h = h;
		context->RenderCopy(m_texture, nullptr, &dest);
	}

}
