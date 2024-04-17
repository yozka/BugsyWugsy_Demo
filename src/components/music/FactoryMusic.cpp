//◦ EggEngine ◦
#include "FactoryMusic.h"
#include "engine/assets/sound/eSoundLoader.h"

using namespace Game::Components;

AFactoryMusic::AFactoryMusic(const Engine::Assets::EAssetResources::Ptr &assets)
	:
		m_assets(assets)
{
	
}


void AFactoryMusic::Create(const Game::AGameObject::UPtr &obj, const Engine::Property &prop)
{
	if (!prop.GetBool("AComponentMusic")) return;
	
	auto music = obj->CreateComponent<Components::AComponentMusic>();
	if (prop.Contains("Music_AutoStart")) {
		music->SetAutoStart(prop.GetBool("Music_AutoStart"));
	}
	if (prop.Contains("Music_Loop")) {
		music->SetLoop(prop.GetBool("Music_Loop"));
	}
	if (prop.Contains("Music_Fade")) {
		music->SetFade(prop.GetFloat("Music_Fade"));
	}
	
	{
		const auto musicId = prop.GetString("Music_1");
		if (m_assets->Contains<Engine::Assets::EAssetMusic>(musicId)) {
			music->SetMusic1(m_assets->Find<Engine::Assets::EAssetMusic>(musicId));
		} else {
			Engine::Assets::ESoundLoader loader(m_assets);
			music->SetMusic1(loader.LoadMusic(prop.GetString("map_group", "level"), musicId));
		}
	}
	
	{
		const auto musicId = prop.GetString("Music_2");
		if (m_assets->Contains<Engine::Assets::EAssetMusic>(musicId)) {
			music->SetMusic2(m_assets->Find<Engine::Assets::EAssetMusic>(musicId));
		} else {
			Engine::Assets::ESoundLoader loader(m_assets);
			music->SetMusic2(loader.LoadMusic(prop.GetString("map_group", "level"), musicId));
		}
	}
}
