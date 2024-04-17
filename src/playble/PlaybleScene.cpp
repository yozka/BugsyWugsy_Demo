//◦ EggEngine ◦
#include "PlaybleScene.h"
#include "map/tmx/tmxLoader.h"

#include "engine/CoreSDL.h"
#include "engine/debug/eAssert.h"
#include "engine/assets/texture/eTextureLoader.h"

#include "objects/FactoryObject.h"
#include "components/geometry/FactoryGeometry.h"
#include "components/sprite/FactorySprite.h"
#include "components/playerControl/FactoryPlayerControl.h"
#include "components/trail/FactoryTrail.h"
#include "components/music/FactoryMusic.h"
#include "components/sound/FactorySound.h"
#include "components/egg/FactoryEgg.h"
#include "components/final/FactoryFinal.h"

using namespace Game;


APlaybleScene::APlaybleScene()
{

}


APlaybleScene::~APlaybleScene()
{
	Done();
}


//Инциализация
bool APlaybleScene::Init(const Engine::Assets::EAssetResources::Ptr &assets)
{
	m_assets = assets;
	m_camera = std::make_shared<Map::ACamera>();
	
	AFactoryObject factory;
	factory.Create<Components::AFactoryGeometry>();
	factory.Create<Components::AFactoryMusic>(m_assets);
	factory.Create<Components::AFactorySound>(m_assets);
	factory.Create<Components::AFactorySprite>(m_assets);
	factory.Create<Components::AFactoryPlayerControl>(m_assets, m_camera, &m_control);
	factory.Create<Components::AFactoryTrailEmitter>();
	factory.Create<Components::AFactoryEgg>();
	factory.Create<Components::AFactoryFinal>();
	
	Map::Tmx::ATmxLoader loaderTmx(m_assets, factory.Creator());
	m_map = loaderTmx.Load("Level", "levels/level_1.tmx");
	m_map->InitCamera(m_camera);
	
	//Кнопочки
	Engine::Assets::ETextureLoader loaderTexture(m_assets);
	loaderTexture.LoadAtlas("textures/common.xml");
	
	m_buttonCamera.SetSpriteNormal		(m_assets->Find<Engine::Assets::EAssetSprite>("buttons/buttonSquare_blue.png"));
	m_buttonCamera.SetSpritePushed		(m_assets->Find<Engine::Assets::EAssetSprite>("buttons/buttonSquare_blue_pressed.png"));
	m_buttonCamera.SetSpriteIconNormal	(m_assets->Find<Engine::Assets::EAssetSprite>("icons/iconCircle_brown.png"));
	m_buttonCamera.SetPosition({50, 50});
	m_buttonCamera.click_signal = [this]()
	{
		m_cameraMoving.Home();
	};
	

	
	
	if (auto player = m_map->FindObject("Player")) {
		if (auto geometry = player->GetComponent<Components::AComponentGeometry>()) {
			m_camera->SetPosition(geometry->Position());
			m_cameraMoving.Init(m_camera, geometry);
		}
	}
	
	if (auto game = m_map->FindObject("MainGame")) {
		if (auto fin = game->GetComponent<Components::AComponentFinal>()) {
			fin->onGameWin = std::bind(&APlaybleScene::GameWin, this);
			fin->onGameLose = std::bind(&APlaybleScene::GameLose, this);
		}
	}
	
	return true;
}


//Завершение игры
void APlaybleScene::Done()
{
	m_camera = {};
	m_control = {};
	
	if (m_map) {
		m_map->Destroy();
		m_map = {};
	}
	if (m_assets) {
		m_assets->RemoveGroup("level");
		m_assets->RemoveGroup("common");
		m_assets = {};
	}
	
	m_cameraMoving.Done();
}

void APlaybleScene::GameWin()
{
	m_win = true;
	m_lose = false;

}

void APlaybleScene::GameLose()
{
	m_win = false;
	m_lose = true;
}


void APlaybleScene::Input(const Engine::Input::TControls &controls)
{
	if (!m_control || !m_control->IsInputCaptured()) {
		if (m_buttonCamera.Input(controls)) return;
		//if (m_buttonZoomOut.Input(controls)) return;
		//if (m_buttonZoomDef.Input(controls)) return;
	}
	if (m_control && m_control->Input(controls)) {
		m_cameraMoving.Stop();
		return;
	}

	
	/*
	
	if (controls.menu.pressed) {
		m_camera->ZoomReset();
	}
	 */

	
}


//Игровой цикл
void APlaybleScene::Update(const double dt)
{
	if (!m_active) return;
	
	if (m_win) {
		m_active = false;
		if (onGameWin) {
			onGameWin();
		}
		
		return;
	}
	
	if (m_lose) {
		m_active = false;
		if (onGameLose) {
			onGameLose();
		}
		return;
	}
	
	
	if (!m_start && m_map) {
		m_start = true;
		m_map->Start();
	}

	if (m_control) {
		m_control->Update(dt);
	}
	
	if (m_map) {
		m_map->Update(dt);
	}
	
	if (!m_control || !m_control->IsInputCaptured()) {
		m_cameraMoving.Update(dt);
	}
}


//Отрисовка
void APlaybleScene::Render(const Engine::Render::ERenderContext::UPtr& context)
{
	if (m_camera) {
		m_camera->SetScreenSize(context->RenderWidth(), context->RenderHeight());
	}
	
	if (!m_spriteBatch) {
		m_spriteBatch = std::make_unique<Engine::Render::ESpriteBatch>();
	}
	
	SDL_FRect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = context->RenderWidth();
	rect.h = context->RenderHeight();
	context->RenderFillRect(rect, {48, 104, 80, 0xFF});

	m_spriteBatch->Begin(context);
	
	//Карта
	if (m_map) {
		m_map->Render(m_spriteBatch, m_camera);
	}
	
	//GUI
	m_buttonCamera.Render(m_spriteBatch);
	//m_buttonZoomOut.Render(m_spriteBatch);
	//m_buttonZoomDef.Render(m_spriteBatch);

	
	if (m_control) {
		m_control->Render(m_spriteBatch);
	}
	
	m_spriteBatch->End();
}

