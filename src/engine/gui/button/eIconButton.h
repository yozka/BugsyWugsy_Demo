//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "engine/CoreSDL.h"
#include "engine/gui/button/eButton.h"

namespace Engine::GUI
{


	// Кнопка
	class EIconButton : public EButton
	{
	public:
		using Super 	= EButton;
		using Ptr		= std::shared_ptr<EIconButton>;
		using WeakPtr	= std::weak_ptr<EIconButton>;
		using UPtr		= std::unique_ptr<EIconButton>;

	public:
		EIconButton();
		virtual ~EIconButton();

	public:
		void SetIconOffset(const FPoint &offset);
		void SetIconScale(const FPoint &scale);
		void SetIconScale(const float scale);

		void SetSpriteIconNormal(const Engine::Assets::EAssetSprite::Ptr &sprite);
		void SetSpriteIconPushed(const Engine::Assets::EAssetSprite::Ptr &sprite);
		void SetSpriteIconDisabled(const Engine::Assets::EAssetSprite::Ptr &sprite);

		
	public:
		void Render(const Engine::Render::ESpriteBatch::UPtr& context) override;

	protected:
		void CalcCurrentSprite() override;
		void OnPushdown() override; //  нажали на кнопку
		void OnPushup() override; //  Отпустили кнопку
		
	private:
		Engine::Assets::EAssetSprite::Ptr m_iconNormal;
		Engine::Assets::EAssetSprite::Ptr m_iconPushed;
		Engine::Assets::EAssetSprite::Ptr m_iconDisabled;
		
		Engine::Assets::EAssetSprite::Ptr m_icon; //Текущий спрайт для отрисовки
		SDL_Rect m_iconSource 	= {}; //Текстурные координаты спрайта
		SDL_FRect m_iconScreen 	= {}; //Экран. куда рисовать
		
		FPoint m_iconOffset			= {};
		FPoint m_iconScale			= { 1.0f, 1.0f };
		FPoint m_iconPushedScale	= { 1.0f, 1.0f };
		
	};


}
