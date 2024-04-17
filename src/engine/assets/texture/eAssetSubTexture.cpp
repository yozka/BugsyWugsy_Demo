//◦ EggEngine ◦
#include "eAssetSubTexture.h"

namespace Engine::Assets
{

	EAssetSubTexture::EAssetSubTexture()
	{
	}


	EAssetSubTexture::~EAssetSubTexture()
	{

	}


	EAssetSprite::UPtr EAssetSubTexture::Create(const std::string& name, const EAssetSprite::Ptr& atlas, const IRect& rect)
	{
		auto sprite = std::make_unique<EAssetSubTexture>();
		sprite->m_name = name;
		sprite->m_rect = rect;
		sprite->m_atlas = atlas;
		return sprite;
	}


	SDL_Texture* EAssetSubTexture::MakeTexture(Engine::Render::EGraphics &context)
	{
		if (m_atlas) {
			return m_atlas->MakeTexture(context);
		}
		return nullptr;
	}


	//Область спрайта в текстуре
	IRect EAssetSubTexture::SourceRect() const
	{
		return m_rect;
	}

	//Размерность самой текстуры
	IPoint EAssetSubTexture::SizeTexture() const
	{
		if (m_atlas) {
			return m_atlas->SizeTexture();
		}
		return {};
	}


	std::string EAssetSubTexture::Name() const
	{
		return m_name;
	}


	std::string EAssetSubTexture::Group() const
	{
		if (m_atlas) {
			return m_atlas->Group();
		}
		return {};
	}

}

