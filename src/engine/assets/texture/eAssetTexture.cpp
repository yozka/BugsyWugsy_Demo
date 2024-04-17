//◦ EggEngine ◦
#include "eAssetTexture.h"
#include "engine/CoreSDL.h"

namespace Engine::Assets
{

	EAssetTexture::EAssetTexture()
	{
	}


	EAssetTexture::~EAssetTexture()
	{
		if (m_surface) {
			SDL_FreeSurface(m_surface);
			m_surface = {};
		}
		if (m_texture) {
			SDL_DestroyTexture(m_texture);
			m_texture = {};
		}
	}


	EAssetSprite::UPtr EAssetTexture::Create(const std::string& name, const std::string& group, const std::vector<char>& data)
	{
		//Создание текстуры из буфера
		auto rw = SDL_RWFromConstMem(data.data(), static_cast<int>(data.size()));
		if (rw == nullptr) {
			return {};
		}

		auto surface = IMG_LoadPNG_RW(rw);
		if (surface == nullptr) {
			surface = IMG_LoadTGA_RW(rw);
			if (surface == nullptr) {
				surface = IMG_Load_RW(rw, 0);
				if (surface == nullptr) {
					SDL_FreeRW(rw);
					return {};
				}
			}
		}
		SDL_FreeRW(rw);
		
		auto sprite = std::make_unique<EAssetTexture>();
		sprite->m_surface = surface;
		sprite->m_name = name;
		sprite->m_group = group;
		return sprite;
	}


	SDL_Texture* EAssetTexture::MakeTexture(Engine::Render::EGraphics &context)
	{
		if (!m_texture) {
			m_texture = context.CreateTexture(m_surface);
		}
		return m_texture;
	}


	//Область спрайта в текстуре
	IRect EAssetTexture::SourceRect() const
	{
		if (m_surface) {
			return {0, 0, m_surface->w, m_surface->h};
		}
		return {};
	}
	

	//Размерность самой текстуры
	IPoint EAssetTexture::SizeTexture() const
	{
		if (m_surface) {
			return {m_surface->w, m_surface->h};
		}
		return {};
	}


	std::string EAssetTexture::Name() const
	{
		return m_name;
	}


	std::string EAssetTexture::Group() const
	{
		return m_group;
	}

}
