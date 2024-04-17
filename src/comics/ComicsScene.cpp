//◦ EggEngine ◦
#include "ComicsScene.h"
#include "engine/files/os/eOS.h"
#include "engine/xml/eTinyxml.h"

#include "engine/assets/font/eFontLoader.h"
#include "engine/assets/texture/eTextureLoader.h"
#include "engine/assets/sound/eSoundLoader.h"

using namespace Comics;


AComicsScene::AComicsScene()
{
	
}


AComicsScene::~AComicsScene()
{
	Done();
}


//Инциализация
bool AComicsScene::Init(const Engine::Assets::EAssetResources::Ptr &assets, const std::string &fileName)
{
	m_assets = assets;
	
	{
		Engine::Assets::EFontLoader loader(m_assets);
		if (!loader.LoadFonts(fileName)) return false;
	}
	
	{
		Engine::Assets::ETextureLoader loader(m_assets);
		if (!loader.LoadSprites(fileName)) return false;
	}
	
	//Загружаем музыку
	{
		Engine::Assets::ESoundLoader loader(m_assets);
		if (!loader.Load(fileName)) return false;
	}
	
	//Загружаем слайды
	auto file = Engine::Files::OS::Open(fileName);
	if (!file) return false;

	auto doc = Engine::Xml::Load(file);
	file->Close();

	auto root = doc->RootElement();
	if (!root) return false;
	auto node = root->FirstChildElement("slide");
	while (node) {
		auto slide = std::make_shared<AComicsSlide>();
		slide->Load(node, m_assets);
		m_slides.push_back(slide);
		node = node->NextSiblingElement("slide");
	}
	return !m_slides.empty();
}



//Завершение игры
void AComicsScene::Done()
{
	if (m_assets) {
		m_assets->RemoveGroup("comics");
		m_assets = {};
	}
}


void AComicsScene::Input(const Engine::Input::TControls &controls)
{
	//нажато
	if (controls.touch.pressed) {
		m_tap = true;
		return;
	}
	
	if (controls.touch.released && m_tap) {
		NextSlide();
	}
	
	if (controls.action.pressed) {
		m_key = true;
		return;
	}
	
	if (controls.action.released && m_key) {
		NextSlide();
	}
	
}

void AComicsScene::NextSlide()
{
	m_key = false;
	m_tap = false;
	m_currentSlide++;
	if (m_currentSlide >= m_slides.size()) {
		//Все слайды протаптаны, выходим
		Mix_HaltMusic();
		if (onCompleted) {
			onCompleted();
		}
	} else {
		m_slides[m_currentSlide]->Activate();
	}
}

//Игровой цикл
void AComicsScene::Update(const double dt)
{
	if (!m_firstActivate && m_currentSlide == 0 && !m_slides.empty()) {
		m_firstActivate = true;
		m_slides[0]->Activate();
	}
}


//Отрисовка
void AComicsScene::Render(const Engine::Render::ERenderContext::UPtr& context)
{
	if (!m_spriteBatch) {
		m_spriteBatch = std::make_unique<Engine::Render::ESpriteBatch>();
	}
	m_spriteBatch->Begin(context);
	if (m_currentSlide < m_slides.size()) {
		m_slides[m_currentSlide]->Render(m_spriteBatch);
	}
	m_spriteBatch->End();
}
