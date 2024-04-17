//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>

#include "engine/CoreSDL.h"
#include "eAssetSprite.h"

namespace Engine::Assets
{

	class EAssetSubTexture : public EAssetSprite
	{
	public:
		using Ptr = std::shared_ptr<EAssetSubTexture>;
		using UPtr = std::unique_ptr<EAssetSubTexture>;
		
	public:
		EAssetSubTexture();
		~EAssetSubTexture();
		
	public:
		static EAssetSprite::UPtr Create(const std::string& name, const EAssetSprite::Ptr& atlas, const IRect& rect);
		
	public:
		std::string Name() const override;
		std::string Group() const override; //Группа ассета
		
	public:
		SDL_Texture* MakeTexture(Engine::Render::EGraphics &context) override;
		IRect SourceRect() const override; //Область спрайта в текстуре
		IPoint SizeTexture() const override; //Размерность самой текстуры
		
	private:
		std::string	m_name;
		IRect m_rect = {};
		EAssetSprite::Ptr m_atlas = {};
		
	};

}

