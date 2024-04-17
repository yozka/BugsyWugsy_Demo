//◦ EggEngine ◦
#pragma once
#include <string>
#include <memory>
#include <vector>

#include "engine/CoreSDL.h"
#include "engine/assets/eAsset.h"
#include "engine/common/eRect.h"
#include "engine/render/eGraphics.h"

namespace Engine::Assets
{
	/*
	 * Шрифты
	 */

	class EAssetFont : public EAsset
	{
	public:
		using Ptr = std::shared_ptr<EAssetFont>;
		using UPtr = std::unique_ptr<EAssetFont>;
		
	public:
		EAssetFont();
		~EAssetFont() override;
		
	public:
		static EAssetFont::UPtr Create(const std::string& name, const std::string& group, const int fontSize, const std::vector<char>& data);

	public:
		std::string Name() const override;
		std::string Group() const override; //Группа ассета
		
	public:
		template <class T>
		SDL_Texture* MakeText(const std::unique_ptr<T> &context, const std::string& text, const SDL_Color &color)
		{
			if (auto obj = context.get()) {
				return MakeText(*obj, text, color);
			}
			return {};
		}
		SDL_Texture* MakeText(Engine::Render::EGraphics &context, const std::string& text, const SDL_Color &color);
		
	private:
		std::string	m_name;
		std::string	m_group;

		std::vector<char> m_data;
		TTF_Font* m_font = {};

	};

}
