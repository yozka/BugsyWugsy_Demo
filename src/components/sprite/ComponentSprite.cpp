//◦ EggEngine ◦
#include "ComponentSprite.h"
#include "engine/assets/texture/eTextureLoader.h"


using namespace Game::Components;


AComponentSprite::AComponentSprite()
{

}


AComponentSprite::~AComponentSprite()
{

}


void AComponentSprite::Destroy()
{
	m_sprite = {};
	m_comGeometry = {};
}


void AComponentSprite::SetAssets(Engine::Assets::EAssetResources::WeakPtr assets)
{
	m_assets = std::move(assets);
}

void AComponentSprite::SetSprite(const std::string &spriteId)
{
	if (auto assets = m_assets.lock()) {

		if (assets->Contains<Engine::Assets::EAssetSprite>(spriteId)) {
			SetSprite(assets->Find<Engine::Assets::EAssetSprite>(spriteId));
		} else {
			Engine::Assets::ETextureLoader loaderTexture(assets);
			SetSprite(loaderTexture.LoadSprite("level", spriteId));
		}
	}
}

void AComponentSprite::SetSprite(const Engine::Assets::EAssetSprite::Ptr &sprite)
{
	m_sprite = sprite;
}

void AComponentSprite::SetScale(const float value)
{
	m_scale = value;
}

Engine::FRect AComponentSprite::Geometry() const
{
	if (!m_comGeometry) {
		m_comGeometry = GetComponent<Components::AComponentGeometry>();
		if (!m_comGeometry) {
			return {};
		}
	}
	return m_comGeometry->Geometry();
}

void AComponentSprite::Render(const Engine::Render::ESpriteBatch::UPtr &context,
							  const Engine::IPoint& pos,
							  const float scale)
{
	if (!m_sprite) return;
	
	auto texture = m_sprite->MakeTexture(context);
	SDL_Rect source = m_sprite->SourceRect().SDL();
	const float width = source.w * scale * m_scale;
	const float height = source.h * scale * m_scale;
	
	SDL_FRect dest;
	dest.x = pos.x - width / 2;
	dest.y = pos.y - height / 2;
	dest.w = width;
	dest.h = height;
	
	context->RenderCopyF(texture, &source, &dest);
	
}

