//◦ EggEngine ◦
#include "eAssetFont.h"
#include "engine/CoreSDL.h"

namespace Engine::Assets
{

	EAssetFont::EAssetFont()
	{
	}


	EAssetFont::~EAssetFont()
	{
		if (m_font) {
			TTF_CloseFont(m_font);
			m_font = {};
		}
	}


	EAssetFont::UPtr EAssetFont::Create(const std::string& name, const std::string& group, const int fontSize, const std::vector<char>& data)
	{
		auto asset = std::make_unique<EAssetFont>();
		asset->m_name = name;
		asset->m_group = group;
		asset->m_data = data;

		auto rw = SDL_RWFromMem(asset->m_data.data(), static_cast<int>(asset->m_data.size()));
		if (rw == nullptr) {
			return {};
		}
		asset->m_font = TTF_OpenFontRW(rw, 1, fontSize);
		if (asset->m_font == nullptr) {
			const auto error = TTF_GetError();
			return {};
		}

		return asset;
	}


	SDL_Texture* EAssetFont::MakeText(Engine::Render::EGraphics &context, const std::string& text, const SDL_Color& color)
	{
		auto *surface = TTF_RenderUTF8_Solid(m_font, text.c_str(), color);
		auto *texture = context.CreateTexture(surface);
		SDL_FreeSurface(surface);
		return texture;
	}


	std::string EAssetFont::Name() const
	{
		return m_name;
	}


	std::string EAssetFont::Group() const
	{
		return m_group;
	}

}
