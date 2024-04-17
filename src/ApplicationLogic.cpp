//◦ EggEngine ◦
#include "ApplicationLogic.h"
#include "engine/debug/eAssert.h"
#include "engine/input/controllers/eControllers.h"
#include "engine/input/keyboard/eKeyboard.h"
#include "engine/input/screen/eScreenGamepad.h"

#include "menu/MenuScene.h"
#include "comics/ComicsScene.h"
#include "playble/PlaybleScene.h"


using namespace Game;



AApplicationLogic::AApplicationLogic()
{

}


AApplicationLogic::~AApplicationLogic()
{
	Done();
}


bool AApplicationLogic::Init()
{
	m_assets = std::make_shared<Engine::Assets::EAssetResources>();
	
	auto menu = std::make_shared<Game::AMenuScene>();
	if (!menu->Init(m_assets)) {
		sassert2(false, "Menu not init!");
		return false;
	}
	menu->onStart = std::bind(&AApplicationLogic::OnStartComics, this);


	PushScene(menu);
	InitInput();
	return true;
}


void AApplicationLogic::InitInput()
{
	auto input = std::make_shared<Engine::Input::EControllers>();
	input->Append(std::make_unique<Engine::Input::EKeyboard>());
	input->Append(std::make_unique<Engine::Input::EScreenGamepad>());
	m_input = std::move(input);
}


//Завершение игры
void AApplicationLogic::Done()
{
	for (const auto scene : m_scenes) {
		scene->Done();
	}
	m_scenes.clear();
	m_scene = {};
	m_assets = {};
	m_input = {};
}


void AApplicationLogic::EventInput(SDL_Event &event)
{
	if (m_input) {
		m_input->EventInput(event);
	}
}


//Игровой цикл
void AApplicationLogic::Update(const double dt)
{
	if (m_input) {
		m_input->Update(dt);
		Engine::Input::TControls controls;
		if (m_scene && m_input->HasControls(controls)) {
			m_scene->Input(controls);
		}
	}
	
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
	if (m_input) {
		m_input->Render(context);
	}
}


void AApplicationLogic::PushScene(const AGameScene::Ptr &scene)
{
	m_scene = scene;
	m_scenes.push_back(scene);
}


void AApplicationLogic::PopScene()
{
	if (m_scene) {
		m_scene->Done();
	}
	m_scenes.pop_back();
	if (m_scenes.empty()) {
		sassert2(false, "scenes empty");
		m_scene = {};
		return;
	}
	m_scene = m_scenes.front();
}


void AApplicationLogic::OnStartComics()
{
	auto comics = std::make_shared<Comics::AComicsScene>();
	comics->Init(m_assets, "comics/start.xml");
	comics->onCompleted = std::bind(&AApplicationLogic::OnStartGame, this);
	PushScene(comics);
}

void AApplicationLogic::OnStartGame()
{
	PopScene();
	auto game = std::make_shared<Game::APlaybleScene>();
	game->Init(m_assets);
	game->onGameWin = std::bind(&AApplicationLogic::OnGameWin, this);
	game->onGameLose = std::bind(&AApplicationLogic::OnGameLose, this);
	PushScene(game);
}


void AApplicationLogic::OnGameWin()
{
	PopScene();
	auto comics = std::make_shared<Comics::AComicsScene>();
	if (comics->Init(m_assets, "comics/win.xml")) {
		comics->onCompleted = std::bind(&AApplicationLogic::OnMenu, this);
		PushScene(comics);
	}
}


void AApplicationLogic::OnGameLose()
{
	PopScene();
	auto comics = std::make_shared<Comics::AComicsScene>();
	if (comics->Init(m_assets, "comics/lose.xml")) {
		comics->onCompleted = std::bind(&AApplicationLogic::OnMenu, this);
		PushScene(comics);
	}
}


void AApplicationLogic::OnMenu()
{
	PopScene();
}
