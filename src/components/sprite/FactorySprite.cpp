//◦ EggEngine ◦
#include "FactorySprite.h"
#include "engine/assets/texture/eTextureLoader.h"

using namespace Game::Components;

AFactorySprite::AFactorySprite(const Engine::Assets::EAssetResources::Ptr &assets)
	:
		m_assets(assets)
{
	
}


void AFactorySprite::Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop)
{
	if (!prop.GetBool("AComponentSprite")) return;
	
	auto sprite = std::make_shared<Components::AComponentSprite>();
	sprite->SetAssets(m_assets);
	if (prop.Contains("Sprite_Scale")) {
		sprite->SetScale(prop.GetFloat("Sprite_Scale"));
	}
	
	const auto spriteId = prop.GetString("Sprite_SpriteID");
	if (m_assets->Contains<Engine::Assets::EAssetSprite>(spriteId)) {
		sprite->SetSprite(m_assets->Find<Engine::Assets::EAssetSprite>(spriteId));
	} else {
		Engine::Assets::ETextureLoader loaderTexture(m_assets);
		sprite->SetSprite(loaderTexture.LoadSprite(prop.GetString("map_group", "level"), spriteId));
	}
	obj->AppendComponent<Components::AComponentRendering>(sprite);
	obj->AppendComponent<Components::AComponentSprite>(sprite);
}
