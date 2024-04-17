//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>

#include "engine/CoreSDL.h"
#include "eAssetSprite.h"

namespace Engine::Assets
{
	/*
	 * Текстура, хранящеся в бинарниках
	 */
	class EAssetTexture : public EAssetSprite
	{
	public:
		using Ptr = std::shared_ptr<EAssetTexture>;
		using UPtr = std::unique_ptr<EAssetTexture>;
		
	public:
		EAssetTexture();
		~EAssetTexture() override;
		
	public:
		static EAssetSprite::UPtr Create(const std::string& name, const std::string& group, const std::vector<char>& data);

	public:
		std::string Name() const override;
		std::string Group() const override; //Группа ассета
		
	public:
		SDL_Texture* MakeTexture(Engine::Render::EGraphics &context) override;
		IRect SourceRect() const override; //Область спрайта в текстуре
		IPoint SizeTexture() const override; //Размерность самой текстуры
		
	private:
		std::string	m_name;
		std::string	m_group;
		SDL_Surface* m_surface = {};
		SDL_Texture* m_texture = {};
	};

}
