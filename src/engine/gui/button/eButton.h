//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <functional>

#include "engine/CoreSDL.h"
#include "engine/gui/eWidget.h"
#include "engine/assets/texture/eAssetSprite.h"
#include "engine/render/eSpriteBatch.h"
#include "engine/input/eControls.h"

namespace Engine::GUI
{


	// Кнопка
	class EButton : public EWidget
	{
	public:
		using Ptr		= std::shared_ptr<EButton>;
		using WeakPtr	= std::weak_ptr<EButton>;
		using UPtr		= std::unique_ptr<EButton>;

	public:
		EButton();
		virtual ~EButton();
		
	public:
		std::function<void()> click_signal = {};

	public:
		void SetPosition(const FPoint &pos);
		void SetScale(const FPoint &scale);
		void SetScale(const float scale);
		
		void SetSpriteNormal(const Engine::Assets::EAssetSprite::Ptr &sprite);
		void SetSpritePushed(const Engine::Assets::EAssetSprite::Ptr &sprite);
		void SetSpriteDisabled(const Engine::Assets::EAssetSprite::Ptr &sprite);
		
	public:
		bool IsEnabled() const { return m_enabled; }
		FPoint Scale() const { return m_scale; }
		FPoint Position() const { return m_position; }
		
	public:
		bool IsInputCaptured() const override final { return m_captured; }
		bool Input(const Engine::Input::TControls &controls) override final;
		void Update(const double dt) override final;
		void Render(const Engine::Render::ESpriteBatch::UPtr& context) override;

	protected:
		virtual void CalcCurrentSprite();
		virtual void OnCapture(); //  Захват управления кнопки
		virtual void OnPushdown(); //  нажали на кнопку
		virtual void OnPushup(); //  Отпустили кнопку
		virtual void OnClick(); //Обработали клик по кнопке
		virtual void OnRelease(); //Отпустили управление кнопки
		
	private:
		Engine::Assets::EAssetSprite::Ptr m_spriteNormal;
		Engine::Assets::EAssetSprite::Ptr m_spritePushed;
		Engine::Assets::EAssetSprite::Ptr m_spriteDisabled;
		
		Engine::Assets::EAssetSprite::Ptr m_sprite; //Текущий спрайт для отрисовки
		SDL_Rect m_source 	= {}; //Текстурные координаты спрайта
		SDL_FRect m_screen 	= {}; //Экран. куда рисовать
		
		FPoint m_position 	= {};
		FPoint m_scale 		= { 1.0f, 1.0f };
		
		bool m_captured		= {}; //  Кнопка захватила управление
		bool m_pushed 		= {}; //  Кнопка нажата
		bool m_enabled	 	= { true };
	};


}
