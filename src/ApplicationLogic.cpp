//◦ EggEngine ◦
#include "ApplicationLogic.h"
#include "engine/debug/eAssert.h"

#include "menu/MenuScene.h"


using namespace Game;



AApplicationLogic::AApplicationLogic()
{

}


AApplicationLogic::~AApplicationLogic()
{

}


bool AApplicationLogic::Init()
{
	auto menu = std::make_shared<Game::AMenuScene>();
	menu->SetController(this);
	if (!menu->Init()) {
		sassert2(false, "Menunot init!");
		return false;
	}
	PushScene(menu);
	return true;
}


//Завершение игры
void AApplicationLogic::Done()
{
	for (const auto scene : m_scenes) {
		scene->Done();
	}
	m_scenes.clear();
	m_scene = {};
}


void AApplicationLogic::EventInput(SDL_Event &event)
{
	if (m_scene) {
		m_scene->EventInput(event);
	}
}

//Игровой цикл
void AApplicationLogic::Update(const double dt)
{
	if (m_scene) {
		m_scene->Update(dt);
	}
}


//Отрисовка
void AApplicationLogic::Render(const Engine::Render::ERenderContext::UPtr& context)
{
	if (m_scene) {
		m_scene->Render(context);
	}
}


void AApplicationLogic::PushScene(const AGameScene::Ptr &scene)
{
	m_scene = scene;
	m_scene->SetController(this);
	
	m_scenes.push_back(scene);
}


void AApplicationLogic::PopScene()
{
	m_scenes.pop_back();
	if (m_scenes.empty()) {
		sassert2(false, "scenes empty");
		m_scene = {};
		return;
	}
	m_scene = m_scenes.front();
}
