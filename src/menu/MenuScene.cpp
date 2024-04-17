//◦ EggEngine ◦
#include "MenuScene.h"

#include "engine/CoreSDL.h"
#include "engine/debug/eAssert.h"
#include "engine/assets/texture/eTextureLoader.h"
#include "engine/assets/sound/eSoundLoader.h"
#include "engine/assets/font/eFontLoader.h"

using namespace Game;


AMenuScene::AMenuScene()
{

}


AMenuScene::~AMenuScene()
{
	Done();
}


//Инциализация
bool AMenuScene::Init(const Engine::Assets::EAssetResources::Ptr &assets)
{
	m_assets = assets;
	Engine::Assets::ETextureLoader loaderTexture(m_assets);
	loaderTexture.LoadSprite("menu", "menu/logo.png");
	loaderTexture.LoadSprite("menu", "menu/bug1.png");
	
	Engine::Assets::ESoundLoader loaderSound(m_assets);
	loaderSound.LoadSample("menu", "sound/TapComics.wav");
	
	Engine::Assets::EFontLoader loaderFont(m_assets);
	auto font = loaderFont.LoadFont("menu", "fonts/molot.otf", 64);
	m_caption.SetFont(font);
	m_caption.SetColor({0xFF, 0xFF, 0xFF, 0xE0});
	m_caption.SetText("Press any key to continue");
	m_caption.SetScale(0.5f);
	m_caption.SetAlignH(Engine::GUI::EAlign::center);
	m_caption.SetAlignV(Engine::GUI::EAlign::center);
	return true;
}


//Завершение игры
void AMenuScene::Done()
{
	if (m_assets) {
		m_assets->RemoveGroup("menu");
		m_assets = {};
	}
}


void AMenuScene::Input(const Engine::Input::TControls &controls)
{
	if (controls.left.pressed) {
		m_movingX = -1;
	}
	if (controls.left.released) {
		m_movingX = {};
	}
	if (controls.right.pressed) {
		m_movingX = 1;
	}
	if (controls.right.released) {
		m_movingX = {};
	}
	if (controls.up.pressed) {
		m_movingY = -1;
	}
	if (controls.up.released) {
		m_movingY = {};
	}
	if (controls.down.pressed) {
		m_movingY = 1;
	}
	if (controls.down.released) {
		m_movingY = {};
	}
	
	
	
	//нажато
	if (controls.touch.pressed || controls.action.released) {

		m_bugX = controls.touch.pos.x;
		m_bugY = controls.touch.pos.y;

		if (controls.action.released) {
			m_bugX = 100;
			m_bugY = 100;
		}
		
		m_movingX = {};
		m_movingY = {};
		
		
		auto sound = m_assets->Find<Engine::Assets::EAssetSample>("sound/TapComics.wav");
		if (sound) {
			auto sample = sound->GetSample();
			if (sample) {
				Mix_PlayChannel(-1, sample, 0);
			}
		}
		
		m_start--;
		m_caption.SetText("Press any key to continue: " + std::to_string(m_start));
		if (m_start <= 0) {
			m_start = 2;
			if (onStart) {
				onStart();
			}
		}
	}
}


//Игровой цикл
void AMenuScene::Update(const double dt)
{
	float speed = 200.0f * dt;
	m_bugX += m_movingX * speed;
	m_bugY += m_movingY * speed;
}


//Отрисовка
void AMenuScene::Render(const Engine::Render::ERenderContext::UPtr& context)
{
	if (!m_spriteBatch) {
		m_spriteBatch = std::make_unique<Engine::Render::ESpriteBatch>();
	}
	m_spriteBatch->Begin(context);
	
	const int dw = context->RenderWidth();
	const int dh = context->RenderHeight();
	
	SDL_FRect rectScreen;
	rectScreen.x = 0;
	rectScreen.y = 0;
	rectScreen.w = dw;
	rectScreen.h = dh;
	
	SDL_Color colorScreen;
	m_spriteBatch->RenderFillRect(rectScreen, colorScreen);
	
	const auto spriteMenu = m_assets->Find<Engine::Assets::EAssetSprite>("menu/logo.png");
	sassert(spriteMenu);
	if (spriteMenu) {
		const auto textureMenu = spriteMenu->MakeTexture(m_spriteBatch);
		if (textureMenu) {
			const auto source = spriteMenu->SourceRect().SDL();
			
			SDL_FRect dest;
			dest.x = (dw - source.w) / 2;
			dest.y = (dh - source.h) / 2;
			dest.w = source.w;
			dest.h = source.h;
			m_spriteBatch->RenderCopyF(textureMenu, &source, &dest);
		}
	}

	const auto spriteBug = m_assets->Find<Engine::Assets::EAssetSprite>("menu/bug1.png");
	sassert(spriteBug);
	if (spriteBug) {
		const auto textureBug = spriteBug->MakeTexture(m_spriteBatch);
		if (textureBug) {
			const auto source = spriteBug->SourceRect().SDL();
			
			SDL_FRect dest;
			dest.x = source.w / -2 + m_bugX;
			dest.y = source.h / -2 + m_bugY;
			dest.w = source.w;
			dest.h = source.h;
			m_spriteBatch->RenderCopyF(textureBug, &source, &dest);
		}
	}
	
	m_caption.SetPosition({static_cast<float>(dw) / 2.0f, static_cast<float>(dh) - 80.0f});
	m_caption.Render(m_spriteBatch);
	
	m_spriteBatch->End();
}
